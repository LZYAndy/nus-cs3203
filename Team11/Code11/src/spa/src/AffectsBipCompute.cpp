#include "AffectsBipCompute.h"

bool AffectsBipCompute::does_affects_bip_exist()
{
    // search and return immediately when find one
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    for (int assign1 : assign_stmts)
    {
        for (int assign2 : assign_stmts)
        {
            if (is_affects_bip(assign1, assign2))
            {
                return true;
            }
        }
    }
    return false;
}

bool AffectsBipCompute::is_affects_bip(int stmt1, int stmt2)
{
    if (type_bank->get_statement_type(stmt1) != EntityType::ASSIGN)
    {
        return false;
    }
    if (type_bank->get_statement_type(stmt2) != EntityType::ASSIGN)
    {
        return false;
    }
    std::string modifies_var = modifies_bank->get_modified_by_statement(stmt1).back();
    std::vector<std::string> uses_vars = uses_bank->get_used_by_statement(stmt2);
    if (std::find(uses_vars.begin(), uses_vars.end(), modifies_var) == uses_vars.end())
    {
        return false;
    }

    // search bottom-up
    std::unordered_set<int> visited;
    std::stack<int> to_visit;
    std::stack<int> call_stack;
    for (int next_stmt : next_bip_bank->get_next_bip(stmt1))
    {
        to_visit.push(next_stmt);
    }
    while (!to_visit.empty())
    {
        int stmt = to_visit.top();
        to_visit.pop();
        if (stmt == stmt2)
        {
            return true;
        }
        if (visited.find(stmt) != visited.end())
        {
            continue;
        }
        visited.insert(stmt);
        EntityType stmt_type = type_bank->get_statement_type(stmt);
        if (stmt_type == EntityType::ASSIGN || stmt_type == EntityType::READ)
        {
            bool is_modified = false;
            for (std::string inter_modifies_var : modifies_bank->get_modified_by_statement(stmt))
            {
                if (inter_modifies_var.compare(modifies_var) == 0)
                {
                    is_modified = true;
                    break;
                }
            }
            if (is_modified)
            {
                continue;
            }
        }
        if (stmt_type == EntityType::CALL)
        {
            call_stack.push(next_bip_bank->get_egress(stmt));
        }
        std::vector<int> next_bip_stmts = next_bip_bank->get_next_bip(stmt);
        if (!call_stack.empty())
        {
            if (std::find(next_bip_stmts.begin(), next_bip_stmts.end(), call_stack.top()) != next_bip_stmts.end())
            {
                int next_bip_stmt = call_stack.top();
                call_stack.pop();
                if (next_bip_stmt == stmt2)
                {
                    return true;
                }
                to_visit.push(next_bip_stmt);
                continue;
            }
        }
        for (int next_bip_stmt : next_bip_stmts)
        {
            if (next_bip_stmt == stmt2)
            {
                return true;
            }
            to_visit.push(next_bip_stmt);
        }
    }
    return false;
}

std::vector<int> AffectsBipCompute::get_assigns_affected_bip_by(int stmt)
{
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    std::vector<int> visited;

    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_bip(stmt, assign_stmt))
        {
            visited.push_back(assign_stmt);
        }
    }
    return visited;
}

std::vector<int> AffectsBipCompute::get_assigns_affects_bip(int stmt)
{
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    std::vector<int> visited;
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_bip(assign_stmt, stmt))
        {
            visited.push_back(assign_stmt);
        }
    }
    return visited;
}

std::vector<int> AffectsBipCompute::get_all_assigns_affected_bip()
{
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    std::unordered_set<int> visited;

    for (int assign1 : assign_stmts)
    {
        for (int assign2 : assign_stmts)
        {
            if (visited.find(assign2) != visited.end())
            {
                continue;
            }
            if (is_affects_bip(assign1, assign2))
            {
                visited.emplace(assign2);
            }
        }
    }
    std::vector<int> visited_vector;
    visited_vector.insert(visited_vector.end(), visited.begin(), visited.end());
    return visited_vector;
}

std::vector<int> AffectsBipCompute::get_all_assigns_affects_bip()
{
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    std::unordered_set<int> visited;

    for (int assign1 : assign_stmts)
    {
        for (int assign2 : assign_stmts)
        {
            if (visited.find(assign1) != visited.end())
            {
                continue;
            }
            if (is_affects_bip(assign1, assign2))
            {
                visited.emplace(assign1);
            }
        }
    }
    std::vector<int> visited_vector;
    visited_vector.insert(visited_vector.end(), visited.begin(), visited.end());
    return visited_vector;
}

std::unordered_map<int, std::vector<int>> AffectsBipCompute::get_all_affects_bip_relationship()
{
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    Bank<int, int> affects_bip_bank;
    for (int assign1 : assign_stmts)
    {
        for (int assign2 : assign_stmts)
        {
            if (is_affects_bip(assign1, assign2))
            {
                affects_bip_bank.put(assign1, assign2);
            }
        }
    }
    return affects_bip_bank.copy();
}

AffectsBipCompute::AffectsBipCompute(NextBipBank *next_bip_bank, ModifiesBank *modifies_bank, UsesBank *uses_bank, TypeBank *type_bank)
{
    this->next_bip_bank  = next_bip_bank;
    this->modifies_bank = modifies_bank;
    this->uses_bank = uses_bank;
    this->type_bank = type_bank;
}

AffectsBipCompute::AffectsBipCompute()
{
}
