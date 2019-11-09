#include "AffectsBipCompute.h"

AffectsBipCompute::AffectsBipCompute(NextBipBank *next_bip_bank, ModifiesBank *modifies_bank, UsesBank *uses_bank, TypeBank *type_bank, NextBank *next_bank)
{
    this->next_bip_bank = next_bip_bank;
    this->modifies_bank = modifies_bank;
    this->uses_bank = uses_bank;
    this->type_bank = type_bank;
    this->next_bank = next_bank;
}

AffectsBipCompute::AffectsBipCompute()
{
}

std::vector<int> AffectsBipCompute::get_all_assigns_affects_bip()
{
    if (!affects_cache.empty())
    {
        return affects_cache.get_all_keys();
    }
    else
    {
        get_all_affects_bip_relationship();
        return affects_cache.get_all_keys();
    }
}

std::vector<int> AffectsBipCompute::get_assigns_affects_bip(int stmt)
{
    if (!affects_cache.empty())
    {
        return affects_cache.get_reverse(stmt);
    }
    else
    {
        get_all_affects_bip_relationship();
        return affects_cache.get_reverse(stmt);
    }
}

std::unordered_map<int, std::vector<int>> AffectsBipCompute::get_all_affects_bip_relationship()
{
    if (affects_cache.empty())
    {
        std::unordered_map<int, std::vector<int>> result;
        std::vector<int> affected;
        std::vector<int> all_assigns = type_bank->get_all_of_type(EntityType::ASSIGN);

        for (int assign_stmt : all_assigns)
        {
            affected = get_assigns_affected_bip_by(assign_stmt, true);
            if (!affected.empty())
            {
                result.emplace(assign_stmt, affected);
            }
        }

        for(auto& itr: result)
        {
            int affect_stmt = itr.first;
            for(int i: itr.second)
            {
                affects_cache.put(affect_stmt, i);
            }
        }
        return result;
    }
    else
    {
        return affects_cache.copy();
    }
}

std::vector<int> AffectsBipCompute::get_all_assigns_affected_bip()
{
    if (!affects_cache.empty())
    {
        return affects_cache.get_all_values();
    }
    else
    {
        get_all_affects_bip_relationship();
        return affects_cache.get_all_values();
    }
}

std::vector<int> AffectsBipCompute::get_assigns_affected_bip_by(int stmt, bool called_from_get_all_relationship)
{
    std::vector<int> all_assigns = type_bank->get_all_of_type(EntityType::ASSIGN);
    if (called_from_get_all_relationship)
    {
        if (affects_cache.empty())
        {
            std::vector<int> result;

            for (int assign_stmt : all_assigns)
            {
                if (!can_exist_affects_bip(stmt, assign_stmt))
                {
                    continue;
                }

                if (dfs_checking_assigns_affect(stmt, assign_stmt))
                {
                    result.push_back(assign_stmt);
                }
            }
            return result;
        }
        else
        {
            return affects_cache.get(stmt);
        }
    }
    else
    {
        if (!affects_cache.empty())
        {
            return affects_cache.get(stmt);
        }
        else
        {
            get_all_affects_bip_relationship();
            return affects_cache.get(stmt);
        }
    }
}

bool AffectsBipCompute::is_affects_bip(int stmt1, int stmt2)
{
    if (!affects_cache.empty())
    {
        std::vector<int> affected = affects_cache.get(stmt1);
        if (find(affected.begin(), affected.end(), stmt2) != affected.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        get_all_affects_bip_relationship();
        std::vector<int> affected = affects_cache.get(stmt1);
        if (find(affected.begin(), affected.end(), stmt2) != affected.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool AffectsBipCompute::can_exist_affects_bip(int stmt1, int stmt2)
{
    if (type_bank->get_statement_type(stmt1) != EntityType::ASSIGN || type_bank->get_statement_type(stmt2) != EntityType::ASSIGN)
    {
        return false;
    }

    std::vector<std::string> modified_vars = modifies_bank->get_modified_by_statement(stmt1);
    std::vector<std::string> used_vars = uses_bank->get_used_by_statement(stmt2);
    for (std::string m_var : modified_vars)
    {
        for (std::string u_var : used_vars)
        {
            if (m_var == u_var)
            {
                return true;
            }
        }
    }
    return false;
}

bool AffectsBipCompute::modified_by_others(int stmt1, int inter_stmt)
{
    EntityType type = type_bank->get_statement_type(inter_stmt);
    if (type == EntityType::ASSIGN || type == EntityType::READ)
    {
        std::vector<std::string> stmt1_modified_vars = modifies_bank->get_modified_by_statement(stmt1);
        std::vector<std::string> inter_modified_vars = modifies_bank->get_modified_by_statement(inter_stmt);
        for (std::string m_var1 : stmt1_modified_vars)
        {
            for (std::string m_var2 : inter_modified_vars)
            {
                if (m_var1 == m_var2)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool AffectsBipCompute::dfs_checking_assigns_affect(int stmt, int target)
{
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = next_bip_bank->get_next_bip(stmt);
    std::vector<int> call_stack;

    while(!next_stmts.empty())
    {
        int next_stmt = next_stmts.back();
        next_stmts.pop_back();

        if (next_stmt == target)
        {
            return true;
        }

        if (visited.find(next_stmt) != visited.end())
        {
            if (!call_stack.empty())
            {
                int after_call = call_stack.back();
                next_stmts.push_back(after_call);
                call_stack.pop_back();
                if (after_call == target)
                {
                    return true;
                }
            }
            continue;
        }
        else
        {
            visited.emplace(next_stmt);
        }

        if(modified_by_others(stmt, next_stmt))
        {
            continue;
        }

        if (type_bank->get_statement_type(next_stmt) == EntityType::CALL)
        {
            std::vector<int> possible_prog_lines = next_bip_bank->get_egress(next_stmt);
            std::vector<int> normal_next_stmts = next_bank->get_statements_next(next_stmt);
            if (!normal_next_stmts.empty())
            {
                int normal_next_stmt = normal_next_stmts[0];
                for (int possible_prog_line : possible_prog_lines)
                {
                    if (possible_prog_line == normal_next_stmt)
                    {
                        call_stack.push_back(normal_next_stmt);
                    }
                }
            }
            if (!possible_prog_lines.empty())
            {
                if (possible_prog_lines.front() == -1)
                {
                    call_stack.push_back(-1);
                }
            }

        }
        std::vector<int> next_possible_stmts = next_bip_bank->get_next_bip(next_stmt);
        if (!call_stack.empty())
        {
            // check if next stmt is return to procedure
            if (std::find(next_possible_stmts.begin(), next_possible_stmts.end(), call_stack.back()) != next_possible_stmts.end())
            {
                int return_statement = call_stack.back();
                call_stack.pop_back();
                if (return_statement == target)
                {
                    return true;
                }
                next_stmts.push_back(return_statement);
                for (int next_possible_stmt : next_possible_stmts) // only add next statement if is not a return statement
                {
                    if (next_bip_bank->get_ingress(next_possible_stmt).empty())
                    {
                        if (next_possible_stmt == target)
                        {
                            return true;
                        }
                        next_stmts.push_back(next_possible_stmt);
                    }
                }
                continue;
            }
            if (call_stack.back() == -1)
            {
                std::vector<int> possible_exits;
                for (int next_possible_stmt : next_possible_stmts)
                {
                    if (next_bip_bank->get_ingress(next_possible_stmt).empty())
                    {
                        if (next_stmt == target)
                        {
                            return true;
                        }
                        possible_exits.push_back(next_possible_stmt);
                    }
                }
                if (!possible_exits.empty())
                {
                    for (int possible_exit : possible_exits)
                    {
                        next_stmts.push_back(possible_exit);
                    }
                }
                continue;
            }
        }

        for(int after_stmt: next_bip_bank->get_next_bip(next_stmt))
        {
            if (after_stmt == target)
            {
                return true;
            }
            next_stmts.push_back(after_stmt);
        }
    }
    return false;
}

void AffectsBipCompute::clear_cache()
{
    affects_cache.clear_banks();
}
