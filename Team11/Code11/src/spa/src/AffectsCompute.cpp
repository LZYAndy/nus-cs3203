#include "AffectsCompute.h"

std::vector<int> AffectsCompute::get_all_assigns_affect(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<int> result;
    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (affects_other_stmts(i, next_bank, modifies_bank, uses_bank, type_bank))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_assigns_affect(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<int> result;

    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (!can_exist_affects(i, stmt, next_bank, modifies_bank, uses_bank, type_bank))
        {
            continue;
        }

        if (dfs_checking_assigns_affect(i, stmt, next_bank, modifies_bank, uses_bank, type_bank))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::unordered_map<int, std::vector<int>> AffectsCompute::get_all_affects_relationship(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::unordered_map<int, std::vector<int>> result;
    std::vector<int> affected;
    for (int i = 1; i <= last_stmt_num; i++)
    {
        affected = get_assigns_affected_by(i, last_stmt_num, next_bank, modifies_bank, uses_bank, type_bank);
        if (!affected.empty())
        {
            result.emplace(i, affected);
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_all_assigns_affected(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<int> result;
    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (affected_by_other_stmts(i, next_bank, modifies_bank, uses_bank, type_bank))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_assigns_affected_by(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<int> result;

    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (!can_exist_affects(stmt, i, next_bank, modifies_bank, uses_bank, type_bank))
        {
            continue;
        }

        if (dfs_checking_assigns_affect(stmt, i, next_bank, modifies_bank, uses_bank, type_bank))
        {
            result.push_back(i);
        }
    }
    return result;
}

bool AffectsCompute::does_affects_exist(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<int> assign_stmts = type_bank.get_all_of_type(EntityType::ASSIGN);

    for (int i: assign_stmts)
    {
        if (affects_other_stmts(i, next_bank, modifies_bank, uses_bank, type_bank))
        {
            return true;
        }
    }
    return false;
}

bool AffectsCompute::is_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    if (can_exist_affects(stmt1, stmt2, next_bank, modifies_bank, uses_bank, type_bank))
    {
        return dfs_checking_is_affects(stmt1, stmt2, next_bank, modifies_bank, uses_bank, type_bank);
    }
    return false;
}

bool AffectsCompute::can_exist_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    if (type_bank.get_statement_type(stmt1) != EntityType::ASSIGN || type_bank.get_statement_type(stmt2) != EntityType::ASSIGN)
    {
        return false;
    }

    std::vector<std::string> modified_vars = modifies_bank.get_modified_by_statement(stmt1);
    std::vector<std::string> used_vars = uses_bank.get_used_by_statement(stmt2);
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

bool AffectsCompute::modified_by_others(int stmt1, int inter_stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    EntityType type = type_bank.get_statement_type(inter_stmt);
    if (type == EntityType::ASSIGN || type == EntityType::CALL || type == EntityType::READ)
    {
        std::vector<std::string> stmt1_modified_vars = modifies_bank.get_modified_by_statement(stmt1);
        std::vector<std::string> inter_modified_vars = modifies_bank.get_modified_by_statement(inter_stmt);
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

bool AffectsCompute::affects_other_stmts(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    if (type_bank.get_statement_type(stmt) != EntityType::ASSIGN)
    {
        return false;
    }
    return dfs_checking_all_assign_affects(stmt, next_bank, modifies_bank, uses_bank, type_bank);
}

bool AffectsCompute::affected_by_other_stmts(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    if (type_bank.get_statement_type(stmt) != EntityType::ASSIGN)
    {
        return false;
    }
    return dfs_checking_all_assigns_affected(stmt, next_bank, modifies_bank, uses_bank, type_bank);
}

bool AffectsCompute::dfs_checking_is_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = next_bank.get_statements_next(stmt1);

    while(!next_stmts.empty())
    {
        int next_stmt = next_stmts.back();
        next_stmts.pop_back();

        if (visited.find(next_stmt) != visited.end())
        {
            continue;
        }
        else
        {
            visited.emplace(next_stmt);
        }

        if (next_stmt == stmt2)
        {
            return true;
        }

        if (modified_by_others(stmt1, next_stmt, next_bank, modifies_bank, uses_bank, type_bank))
        {
            continue;
        }

        for(int stmt: next_bank.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_all_assign_affects(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::string mod_var = modifies_bank.get_modified_by_statement(stmt)[0];
    std::unordered_set<int> visited;
    std::vector<std::string> used_vars;
    std::vector<int> next_stmts = next_bank.get_statements_next(stmt);

    while(!next_stmts.empty())
    {
        int next_stmt = next_stmts.back();
        next_stmts.pop_back();

        if (visited.find(next_stmt) != visited.end())
        {
            continue;
        }
        else
        {
            visited.emplace(next_stmt);
        }

        if (type_bank.get_statement_type(next_stmt) == EntityType::READ || type_bank.get_statement_type(next_stmt) == EntityType::CALL)
        {
            std::vector<std::string> inter_modified_vars = modifies_bank.get_modified_by_statement(next_stmt);
            for (std::string m_var : inter_modified_vars)
            {
                if (mod_var == m_var)
                {
                    continue;
                }
            }
        }

        if (type_bank.get_statement_type(next_stmt) == EntityType::ASSIGN)
        {
            used_vars = uses_bank.get_used_by_statement(next_stmt);
            for (std::string var: used_vars)
            {
                if (var == mod_var)
                {
                    return true;
                }
            }
        }

        for(int stmt: next_bank.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_all_assigns_affected(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::vector<std::string> used_vars = uses_bank.get_used_by_statement(stmt);
    std::unordered_set<int> visited;
    std::vector<std::string> mod_var;
    std::vector<int> previous_stmts = next_bank.get_statements_previous(stmt);

    while(!previous_stmts.empty())
    {
        int previous_stmt = previous_stmts.back();
        previous_stmts.pop_back();

        if (visited.find(previous_stmt) != visited.end())
        {
            continue;
        }
        else
        {
            visited.emplace(previous_stmt);
        }

        if (type_bank.get_statement_type(previous_stmt) == EntityType::READ || type_bank.get_statement_type(previous_stmt) == EntityType::CALL)
        {
            std::vector<std::string> inter_modified_vars = modifies_bank.get_modified_by_statement(previous_stmt);
            for (std::string u_var : used_vars)
            {
                for (std::string m_var : inter_modified_vars)
                {
                    if (u_var == m_var)
                    {
                        continue;
                    }
                }
            }
        }

        if (type_bank.get_statement_type(previous_stmt) == EntityType::ASSIGN)
        {
            mod_var = modifies_bank.get_modified_by_statement(previous_stmt);
            for (std::string var: used_vars)
            {
                if (var == mod_var[0])
                {
                    return true;
                }
            }
        }

        for(int stmt: next_bank.get_statements_previous(previous_stmt))
        {
            previous_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_assigns_affect(int stmt, int target, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank)
{
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = next_bank.get_statements_next(stmt);

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
            continue;
        }
        else
        {
            visited.emplace(next_stmt);
        }

        if(modified_by_others(stmt, next_stmt, next_bank, modifies_bank, uses_bank, type_bank))
        {
            continue;
        }

        for(int stmt: next_bank.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}
