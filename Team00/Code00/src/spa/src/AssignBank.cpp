#include "AssignBank.h"

void AssignBank::put(int stmt, std::string var, std::string assignment)
{
    var_bank.put(stmt, var);
    assignment_bank.put(stmt, assignment);
    var_assignment_bank.put(var, assignment);
}

std::vector<int> AssignBank::matches(std::string var, std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_reverse(var);
    if (var_stmts.empty())
    {
        return result;
    }
    std::vector<std::string> assignments = var_assignment_bank.get(var);
    if (assignments.empty())
    {
        return result;
    }
    for (std::string assignment : assignments)
    {
        if (assignment.compare(pattern) == 0)
        {
            std::vector<int> assignment_stmts = assignment_bank.get_reverse(assignment);
            for (int i = 0; i < assignment_stmts.size(); ++i)
            {
                int assign_no = assignment_stmts[i];
                for (int j = 0; j < var_stmts.size(); ++j)
                {
                    int var_no = var_stmts[j];
                    if (assign_no == var_no)
                    {
                        result.push_back(assign_no);
                        break;
                    }
                }
            }
        }
    }
    return result;
}

std::vector<int> AssignBank::contains(std::string var, std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_reverse(var);
    if (var_stmts.empty())
    {
        return result;
    }
    std::vector<std::string> assignments = var_assignment_bank.get(var);
    if (assignments.empty())
    {
        return result;
    }
    for (std::string assignment : assignments)
    {
        if (assignment.find(pattern) != std::string::npos) // TODO: will not work for iteration 2 onwards
        {
            std::vector<int> assignment_stmts = assignment_bank.get_reverse(assignment);
            for (int i = 0; i < assignment_stmts.size(); ++i)
            {
                int assign_no = assignment_stmts[i];
                for (int j = 0; j < var_stmts.size(); ++j)
                {
                    int var_no = var_stmts[j];
                    if (assign_no == var_no)
                    {
                        result.push_back(assign_no);
                        break;
                    }
                }
            }
        }
    }
    return result;
}

std::vector<int> AssignBank::all_matches(std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_all_keys();
    if (var_stmts.empty())
    {
        return result;
    }
    std::vector<std::string> assignments = assignment_bank.get_all_values();
    if (assignments.empty())
    {
        return result;
    }
    for (std::string assignment : assignments)
    {
        if (assignment.compare(pattern) == 0)
        {
            std::vector<int> assignment_stmts = assignment_bank.get_reverse(assignment);
            for (int i = 0; i < assignment_stmts.size(); ++i)
            {
                int assign_no = assignment_stmts[i];
                for (int j = 0; j < var_stmts.size(); ++j)
                {
                    int var_no = var_stmts[j];
                    if (assign_no == var_no)
                    {
                        result.push_back(assign_no);
                        break;
                    }
                }
            }
        }
    }
    return result;
}

std::vector<int> AssignBank::all_contains(std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_all_keys();
    if (var_stmts.empty())
    {
        return result;
    }
    std::vector<std::string> assignments = assignment_bank.get_all_values();
    if (assignments.empty())
    {
        return result;
    }
    for (std::string assignment : assignments)
    {
        if (assignment.find(pattern) != std::string::npos) // TODO: will not work for iteration 2 onwards
        {
            std::vector<int> assignment_stmts = assignment_bank.get_reverse(assignment);
            for (int i = 0; i < assignment_stmts.size(); ++i)
            {
                int assign_no = assignment_stmts[i];
                for (int j = 0; j < var_stmts.size(); ++j)
                {
                    int var_no = var_stmts[j];
                    if (assign_no == var_no)
                    {
                        result.push_back(assign_no);
                        break;
                    }
                }
            }
        }
    }
    return result;
}
std::string AssignBank::get_variable_from_statement(int stmt)
{
    std::vector<std::string> result = var_bank.get(stmt);
    if (result.empty())
    {
        return "";
    }
    else
    {
        return result[0];
    }
}
int AssignBank::get_statement_from_variable(std::string var)
{
    std::vector<int> result = var_bank.get_reverse(var);
    if (result.empty())
    {
        return -1;
    }
    else
    {
        return result[0];
    }
}
