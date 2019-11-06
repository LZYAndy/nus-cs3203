#include "DesignExtractor.h"

bool DesignExtractor::extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out)
{
    if (!bank_in.does_follows_exists())
    {
        return false;
    }

    std::vector<int> keys = bank_in.get_all_followed();
    for (int key : keys)
    {
        int current = key;
        while (true)
        {
            int value = bank_in.get_follows(current);
            if (value == -1)
            {
                break;
            }
            bank_out.insert_follows_star(key, value);
            current = value;
        }
    }
    return true;
}

bool DesignExtractor::extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank)
{
    if (!bank_in.does_parent_exist())
    {
        return false;
    }
    std::vector<int> keys = bank_in.get_all_parent();
    for (int key : keys)
    {
        extract_further_parents_child(bank_in, bank_out, uses_bank, modifies_bank, std::vector<int>(), key);
    }
    return true;
}

void DesignExtractor::extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank, std::vector<int> parents, int child)
{
    std::vector<int> children = bank_in.get_children(child);
    if (!children.empty())
    {
        parents.push_back(child);
        for (int kid : children)
        {
            extract_further_parents_child(bank_in, bank_out, uses_bank, modifies_bank, parents, kid);
        }
    }
    for (int parent : parents)
    {
        if (parent == child)
        {
            continue;
        }
        bank_out.insert_parent_star(parent, child);
        std::vector<std::string> uses_var = uses_bank.get_used_by_statement(child);
        if (!uses_var.empty())
        {
            for (std::string var : uses_var)
            {
                uses_bank.insert_uses(parent, var);
            }
        }
        std::vector<std::string> modifies_var = modifies_bank.get_modified_by_statement(child);
        if (!modifies_var.empty())
        {
            for (std::string var : modifies_var)
            {
                modifies_bank.insert_modifies(parent, var);
            }
        }
    }
    return;
}

bool DesignExtractor::extract_calls_star(CallsBank &bank_in, CallsStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank, ParentStarBank &parent_star_bank)
{
    // copy callsBank to CallsStarBank
    for (std::pair<std::string, std::vector<std::string>> in : bank_in.get_all_procedures_calls_relationship())
    {
        for (std::string proc_called : in.second)
        {
            bank_out.insert_calls_star(in.first, proc_called);
            uses_bank.insert_uses_for_call(in.first, proc_called);         // insert uses relationship for proc
            modifies_bank.insert_modifies_for_call(in.first, proc_called); // insert modifies relationship for proc
        }
    }
    std::vector<std::string> keys = bank_out.get_all_procedures_calls_star();
    int i = 0;
    while (i < keys.size())
    {
        for (int j = i; j < keys.size(); j++)
        {
            for (std::string proc_call : bank_out.get_procedures_calls_star(keys[j])) // get all proc that calls key (_, key)
            {
                for (std::string proc_called_by_key : bank_out.get_procedures_called_by_star(keys[j]))
                {
                    bool insert_result = bank_out.insert_calls_star(proc_call, proc_called_by_key);
                    if (!insert_result)
                    {
                        return false;
                    }
                    uses_bank.insert_uses_for_call(proc_call, proc_called_by_key);
                    modifies_bank.insert_modifies_for_call(proc_call, proc_called_by_key);
                }
            }
        }
        i++;
    }

    for (auto call_stmt : bank_in.get_all_statements_calls_relationship())
    {
        auto parents = parent_star_bank.get_parent_star(call_stmt.first);
        for (std::string uses_variable : uses_bank.get_used_by_procedure(call_stmt.second[0]))
        {
            uses_bank.insert_uses(call_stmt.first, uses_variable);
            for (auto parent_stmt_num : parents)
            {
                uses_bank.insert_uses(parent_stmt_num, uses_variable);
            }
        }

        for (std::string modifies_variable : modifies_bank.get_modified_by_procedure(call_stmt.second[0]))
        {
            modifies_bank.insert_modifies(call_stmt.first, modifies_variable);
            for (auto parent_stmt_num : parents)
            {
                modifies_bank.insert_modifies(parent_stmt_num, modifies_variable);
            }
        }
    }
    return true;
}
bool DesignExtractor::extract_next_bip(PKB &pkb)
{
    auto all_previous = pkb.get_all_previous();
    auto calls_stmts = pkb.get_all_calls();
    for (auto previous : all_previous)
    {
        if (pkb.get_statement_type(previous) == EntityType::CALL) // check if previous is a call stmt
        {
            extract_next_bip_helper(pkb, previous, pkb.get_statements_next(previous));
        }
        else
        {
            for (auto next : pkb.get_statements_next(previous))
            {
                pkb.insert_next_bip(previous, next);
            }
        }
    }
    return true;
}

void DesignExtractor::extract_next_bip_helper(PKB &pkb, int previous, std::vector<int> next_of_old_previous)
{
    std::string procedure_called = pkb.get_called_by_statement(previous);
    int callee_start_stmt_no = pkb.get_procedure_first_line(procedure_called);
    std::vector<int> callee_end_stmts_no = pkb.get_procedure_last_lines(procedure_called);
    pkb.insert_next_bip(previous, callee_start_stmt_no);
    std::stack<int> to_visit;
    std::unordered_set<int> visited;
    to_visit.push(callee_start_stmt_no);
    while (!to_visit.empty())
    {
        int stmt = to_visit.top();
        to_visit.pop();
        if (visited.find(stmt) != visited.end())
        {
            continue;
        }
        visited.insert(stmt);
        if (pkb.get_statement_type(stmt) == EntityType::CALL) // check if previous is a call stmt
        {
            std::vector<int> after_calls = pkb.get_statements_next(stmt);
            if (after_calls.empty())
            {
                extract_next_bip_helper(pkb, stmt, next_of_old_previous);
            }
            else
            {
                extract_next_bip_helper(pkb, stmt, after_calls);
            }
            auto next_stmts = pkb.get_statements_next(stmt);
            for (int next_stmt : next_stmts)
            {
                to_visit.push(next_stmt);
            }
        }
        else
        {
            auto next_stmts = pkb.get_statements_next(stmt);
            for (int next_stmt : next_stmts)
            {
                to_visit.push(next_stmt);
                pkb.insert_next_bip(stmt, next_stmt);
            }
        }
        std::vector<int> after_calls = pkb.get_statements_next(previous);
        if (after_calls.empty()) // call is at last stmt of procedure
        {
            for (auto after_call : next_of_old_previous)
            {
                for (int end_stmt : callee_end_stmts_no)
                {
                    pkb.insert_next_bip(end_stmt, after_call);
                }
                pkb.insert_call_ingress_egress(previous, after_call);
            }
        }
        else
        {
            for (auto after_call : after_calls)
            {
                for (int end_stmt : callee_end_stmts_no)
                {
                    pkb.insert_next_bip(end_stmt, after_call);
                }
                pkb.insert_call_ingress_egress(previous, after_call);
            }
        }

    }
}