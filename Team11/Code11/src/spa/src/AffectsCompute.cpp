#include "AffectsCompute.h"

std::vector<int> AffectsCompute::get_all_assigns_affect(PKB &pkb) {
    return std::vector<int>();
}

std::vector<int> AffectsCompute::get_assigns_affect(int stmt, PKB &pkb) {
    return std::vector<int>();
}

std::unordered_map<int, std::vector<int>> AffectsCompute::get_all_affects_relationship(PKB &pkb) {
    return std::unordered_map<int, std::vector<int>>();
}

std::vector<int> AffectsCompute::get_all_assigns_affected(PKB &pkb) {
    return std::vector<int>();
}

std::vector<int> AffectsCompute::get_assigns_affected_by(int stmt, PKB &pkb) {
    return std::vector<int>();
}

bool AffectsCompute::does_affects_exist(int last_stmt_num, PKB &pkb) {
    for (int i = 1; i <= last_stmt_num; i++)
    {
        if (affects_other_stmts(i, pkb))
        {
            return true;
        }
    }
    return false;
}

bool AffectsCompute::is_affects(int stmt1, int stmt2, PKB &pkb) {
    if (can_exist_affects(stmt1, stmt2, pkb))
    {
        return DFS_checking_is_affects(stmt1, stmt2, pkb);
    }
    return false;
}

bool AffectsCompute::DFS_checking_is_affects(int stmt1, int stmt2, PKB& pkb) {
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

bool AffectsCompute::can_exist_affects(int stmt1, int stmt2, PKB& pkb) {
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

bool AffectsCompute::modified_by_others(int stmt1, int inter_stmt, PKB& pkb) {
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

bool AffectsCompute::affects_other_stmts(int stmt, PKB &pkb) {
    if (pkb.get_statement_type(stmt) != EntityType::ASSIGN)
    {
        return false;
    }
    return DFS_checking_assign_affects(stmt, pkb);
}

bool AffectsCompute::DFS_checking_assign_affects(int stmt, PKB &pkb) {
    std::string mod_var;
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

        if (modified_by_others(stmt, next_stmt, pkb))
        {
            return false;
        }

        if (pkb.get_statement_type(next_stmt) == EntityType::ASSIGN)
        {
            used_vars = pkb.get_used_by_statement(next_stmt);
            for (std::string var: used_vars)
            {
                if (var == mod_var)
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
