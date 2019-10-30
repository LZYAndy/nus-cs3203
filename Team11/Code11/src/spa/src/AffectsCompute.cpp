#include "AffectsCompute.h"

std::vector<int> AffectsCompute::get_all_assigns_affect(int last_stmt_num, PKB &pkb)
{
    std::vector<int> result;
    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (affects_other_stmts(i, pkb))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_assigns_affect(int stmt, int last_stmt_num, PKB &pkb)
{
    std::vector<int> result;

    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (!can_exist_affects(i, stmt, pkb))
        {
            continue;
        }

        if (dfs_checking_assigns_affect(i, stmt, pkb))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::unordered_map<int, std::vector<int>> AffectsCompute::get_all_affects_relationship(int last_stmt_num, PKB &pkb)
{
    std::unordered_map<int, std::vector<int>> result;
    std::vector<int> affected;
    for (int i = 1; i <= last_stmt_num; i++)
    {
        affected = get_assigns_affected_by(i, last_stmt_num, pkb);
        if (!affected.empty())
        {
            result.emplace(i, get_assigns_affected_by(i, last_stmt_num, pkb));
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_all_assigns_affected(int last_stmt_num, PKB &pkb)
{
    std::vector<int> result;
    for (int i = 1; i<= last_stmt_num; i++)
    {
        if (affected_by_other_stmts(i, pkb))
        {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> AffectsCompute::get_assigns_affected_by(int stmt, int last_stmt_num, PKB &pkb)
{
    std::vector<int> result;

    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (!can_exist_affects(stmt, i, pkb))
        {
            continue;
        }

        if (dfs_checking_assigns_affected_by(stmt, i, pkb))
        {
            result.push_back(i);
        }
    }
    return result;
}

bool AffectsCompute::does_affects_exist(int last_stmt_num, PKB &pkb)
{
    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (affects_other_stmts(i, pkb))
        {
            return true;
        }
    }
    return false;
}

bool AffectsCompute::is_affects(int stmt1, int stmt2, PKB &pkb)
{
    if (can_exist_affects(stmt1, stmt2, pkb))
    {
        return dfs_checking_is_affects(stmt1, stmt2, pkb);
    }
    return false;
}

bool AffectsCompute::can_exist_affects(int stmt1, int stmt2, PKB& pkb)
{
    if (pkb.get_statement_type(stmt1) != EntityType::ASSIGN || pkb.get_statement_type(stmt2) != EntityType::ASSIGN)
    {
        return false;
    }

    std::vector<std::string> modified_vars = pkb.get_modified_by_statement(stmt1);
    std::vector<std::string> used_vars = pkb.get_used_by_statement(stmt2);
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

bool AffectsCompute::modified_by_others(int stmt1, int inter_stmt, PKB& pkb)
{
    EntityType type = pkb.get_statement_type(inter_stmt);
    if (type == EntityType::ASSIGN || type == EntityType::CALL || type == EntityType::READ)
    {
        std::vector<std::string> stmt1_modified_var = pkb.get_modified_by_statement(stmt1);
        std::vector<std::string> inter_modified_var = pkb.get_modified_by_statement(inter_stmt);
        for (std::string m_var1 : stmt1_modified_var)
        {
            for (std::string m_var2 : inter_modified_var)
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

bool AffectsCompute::affects_other_stmts(int stmt, PKB &pkb)
{
    if (pkb.get_statement_type(stmt) != EntityType::ASSIGN)
    {
        return false;
    }
    return dfs_checking_all_assign_affects(stmt, pkb);
}

bool AffectsCompute::affected_by_other_stmts(int stmt, PKB &pkb)
{
    if (pkb.get_statement_type(stmt) != EntityType::ASSIGN)
    {
        return false;
    }
    return dfs_checking_all_assigns_affected(stmt, pkb);
}

bool AffectsCompute::dfs_checking_is_affects(int stmt1, int stmt2, PKB& pkb)
{
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = pkb.get_statements_next(stmt1);

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

        if (modified_by_others(stmt1, next_stmt, pkb))
        {
            return false;
        }

        for(int stmt: pkb.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_all_assign_affects(int stmt, PKB &pkb)
{
    std::vector<std::string> mod_var = pkb.get_modified_by_statement(stmt);
    std::unordered_set<int> visited;
    std::vector<std::string> used_vars;
    std::vector<int> next_stmts = pkb.get_statements_next(stmt);

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

        if (pkb.get_statement_type(next_stmt) == EntityType::READ || pkb.get_statement_type(next_stmt) == EntityType::CALL)
        {
            std::vector<std::string> inter_modified_var = pkb.get_modified_by_statement(next_stmt);
            for (std::string m_var1 : mod_var)
            {
                for (std::string m_var2 : inter_modified_var)
                {
                    if (m_var1 == m_var2)
                    {
                        continue;
                    }
                }
            }
        }

        if (pkb.get_statement_type(next_stmt) == EntityType::ASSIGN)
        {
            used_vars = pkb.get_used_by_statement(next_stmt);
            for (std::string var: used_vars)
            {
                if (var == mod_var[0])
                {
                    return true;
                }
            }
        }

        for(int stmt: pkb.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_all_assigns_affected(int stmt, PKB &pkb)
{
    std::vector<std::string> used_vars = pkb.get_used_by_statement(stmt);
    std::unordered_set<int> visited;
    std::vector<std::string> mod_var;
    std::vector<int> previous_stmts = pkb.get_statements_previous(stmt);

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

        if (pkb.get_statement_type(previous_stmt) == EntityType::READ || pkb.get_statement_type(previous_stmt) == EntityType::CALL)
        {
            std::vector<std::string> inter_modified_var = pkb.get_modified_by_statement(previous_stmt);
            for (std::string m_var1 : mod_var)
            {
                for (std::string m_var2 : inter_modified_var)
                {
                    if (m_var1 == m_var2)
                    {
                        continue;
                    }
                }
            }
        }

        if (pkb.get_statement_type(previous_stmt) == EntityType::ASSIGN)
        {
            mod_var = pkb.get_used_by_statement(previous_stmt);
            for (std::string var: used_vars)
            {
                if (var == mod_var[0])
                {
                    return true;
                }
            }
        }

        for(int stmt: pkb.get_statements_previous(previous_stmt))
        {
            previous_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_assigns_affect(int stmt, int target, PKB &pkb)
{
    std::vector<std::string> mod_var = pkb.get_modified_by_statement(stmt);
    std::vector<std::string> used_vars = pkb.get_used_by_statement(target);
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = pkb.get_statements_next(stmt);

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

        if(modified_by_others(stmt, next_stmt, pkb))
        {
            continue;
        }

        for(int stmt: pkb.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}

bool AffectsCompute::dfs_checking_assigns_affected_by(int target, int stmt, PKB& pkb) {
    std::vector<std::string> mod_var = pkb.get_modified_by_statement(target);
    std::vector<std::string> used_vars = pkb.get_used_by_statement(stmt);
    std::unordered_set<int> visited;
    std::vector<int> next_stmts = pkb.get_statements_next(target);

    while(!next_stmts.empty())
    {
        int next_stmt = next_stmts.back();
        next_stmts.pop_back();

        if (next_stmt == stmt)
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

        if(modified_by_others(target, next_stmt, pkb))
        {
            continue;
        }

        for(int stmt: pkb.get_statements_next(next_stmt))
        {
            next_stmts.push_back(stmt);
        }
    }
    return false;
}
