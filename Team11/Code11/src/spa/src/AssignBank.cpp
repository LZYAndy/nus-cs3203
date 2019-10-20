#include "AssignBank.h"

bool AssignBank::insert_assign(int stmt, std::string var, std::string assignment)
{
    if (stmt <= 0 )
    {
        return false;
    }
    if (var_bank.get(stmt).size() == 1)
    {
        return false;
    }
    if (assignment_bank.get(stmt).size() == 1)
    {
        return false;
    }
    var_bank.put(stmt, var);
    assignment_bank.put(stmt, assignment);
    return true;
}

std::vector<int> AssignBank::matches(std::string var, std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_reverse(var);
    if (var_stmts.empty())
    {
        return result;
    }

    for (int stmt : var_stmts)
    {
        std::vector<std::string> assignments = assignment_bank.get(stmt);
        if (assignments.empty())
        {
            continue;
        }
        std::string assignment = assignments[0];
        if (assignment.compare(pattern) == 0)
        {
            result.push_back(stmt);
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
    for (int stmt : var_stmts)
    {
        std::vector<std::string> assignments = assignment_bank.get(stmt);
        if (assignments.empty())
        {
            continue;
        }
        std::string assignment = assignments[0];
        // TODO: will not work for iteration 2 onwards
        // Iteration 1 hack: pad front and end with space to not match other variable
        std::string padded_pattern = " " + pattern + " ";
        std::string padded_assignment = " " + assignment + " ";
        if (padded_assignment.find(padded_pattern) != std::string::npos)
        {
            result.push_back(stmt);
        }
    }
    return result;
}

std::string AssignBank::replace_operator(std::string &str)
{
    std::regex r("[()+\\-*/%]{1}");
    str = std::regex_replace(str, r, " ");
    return str;
}

std::vector<int> AssignBank::all_matches(std::string pattern)
{
    std::vector<int> result;
    std::vector<int> var_stmts = var_bank.get_all_keys();
    if (var_stmts.empty())
    {
        return result;
    }
    for (int stmt : var_stmts)
    {
        std::vector<std::string> assignments = assignment_bank.get(stmt);
        if (assignments.empty())
        {
            continue;
        }
        std::string assignment = assignments[0];
        if (assignment.compare(pattern) == 0)
        {
            result.push_back(stmt);
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
    for (int stmt : var_stmts)
    {
        std::vector<std::string> assignments = assignment_bank.get(stmt);
        if (assignments.empty())
        {
            continue;
        }
        std::string assignment = assignments[0];
        // TODO: will not work for iteration 2 onwards
        // Iteration 1 hack: pad front and end with space to not match other variable
        std::string padded_pattern = " " + pattern + " ";
        std::string padded_assignment = " " + assignment + " ";
        if (padded_assignment.find(padded_pattern) != std::string::npos)
        {
            result.push_back(stmt);
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
