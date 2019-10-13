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

bool DesignExtractor::extract_calls_star(CallsBank &bank_in, CallsStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank)
{
    // copy callsBank to CallsStarBank
    for (std::pair<std::string, std::vector<std::string>> in: bank_in.get_all_procedures_calls_relationship())
    {
        for (std::string proc_called: in.second)
        {
            bank_out.insert_calls_star(in.first, proc_called);
            uses_bank.insert_uses_for_call(in.first, proc_called); // insert uses relationship for proc
            modifies_bank.insert_modifies_for_call(in.first, proc_called); // insert modifies relationship for proc
        }
    }
    std::vector<std::string> keys  = bank_out.get_all_procedures_calls_star();
    int i = 0;
    while (i < keys.size())
    {
        for (int j = i; j < keys.size(); j++)
        {
            for (std::string proc_call : bank_out.get_procedures_calls_star(keys[j])) // get all proc that calls key (_, key)
            {  
                for (std::string proc_called_by_key : bank_out.get_procedures_called_by_star(keys[j]))
                {
                    std::cout << proc_call << proc_called_by_key << "\n";
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
        for (std::string uses_variable : uses_bank.get_used_by_procedure(call_stmt.second[0]))
        {
            uses_bank.insert_uses(call_stmt.first, uses_variable);
        }
        
        for (std::string modifies_variable : modifies_bank.get_modified_by_procedure(call_stmt.second[0]))
        {
            modifies_bank.insert_modifies(call_stmt.first, modifies_variable);
        }
    }
    return true;
}
