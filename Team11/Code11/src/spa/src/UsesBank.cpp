#include <algorithm>
#include "UsesBank.h"

bool UsesBank::insert_uses(std::string procedure, std::string variable)
{
    if(variable == "")
    {
        return false;
    }
    else
    {
        proc_bank.put(procedure, variable);
        return true;
    }
}

bool UsesBank::insert_uses(int statement, std::string variable)
{
    if(variable == "")
    {
        return false;
    }
    else
    {
        stmt_bank.put(statement, variable);
        return true;
    }
}

std::vector<int> UsesBank::get_statements_uses(std::string variable)
{
    return stmt_bank.get_reverse(variable);
}

std::vector<std::string> UsesBank::get_procedures_uses(std::string variable)
{
    return proc_bank.get_reverse(variable);
}

std::vector<std::string> UsesBank::get_used_by_procedure(std::string procedure)
{
    return proc_bank.get(procedure);
}

std::vector<std::string> UsesBank::get_used_by_statement(int statement)
{
    return stmt_bank.get(statement);
}

bool UsesBank::is_uses(std::string procedure, std::string variable)
{
    if (proc_bank.get(procedure).size() == 0)
    {
        return false;
    }
    else
    {
        std::vector<std::string> elements = proc_bank.get(procedure);
        std::vector<std::string>::iterator ret;
        ret = std::find(elements.begin(), elements.end(), variable);
        if(ret == elements.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool UsesBank::is_uses(int statement, std::string variable)
{
    if (stmt_bank.get(statement).size() == 0)
    {
        return false;
    }
    else
    {
        std::vector<std::string> elements = stmt_bank.get(statement);
        std::vector<std::string>::iterator ret;
        ret = std::find(elements.begin(), elements.end(), variable);
        if(ret == elements.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

std::vector<int> UsesBank::get_all_uses_statements()
{
    return stmt_bank.get_all_keys();
}

std::vector<std::string> UsesBank::get_all_uses_procedures()
{
    return proc_bank.get_all_keys();
}

std::unordered_map<int, std::vector<std::string>> UsesBank::get_all_uses_statements_relationship()
{
    return stmt_bank.copy();
}

std::unordered_map<std::string, std::vector<std::string>> UsesBank::get_all_uses_procedures_relationship()
{
    return proc_bank.copy();
}

bool UsesBank::does_uses_exist()
{
    return proc_bank.empty() && stmt_bank.empty();
}

bool UsesBank::insert_uses_for_call(std::string caller, std::string callee)
{
    std::vector<std::string> callee_var = this->get_used_by_procedure(callee);
    bool result = false;

    if(callee_var.size() == 0)
    {
        return false;
    }

    for(std::string var: callee_var)
    {
        result = this->insert_uses(caller, var);
        if(!result)
        {
            return false;
        }
    }
    return true;
}
