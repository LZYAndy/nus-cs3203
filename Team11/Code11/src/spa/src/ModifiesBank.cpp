#include <algorithm>
#include "ModifiesBank.h"

bool ModifiesBank::insert_modifies(int statement, std::string variable)
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

bool ModifiesBank::insert_modifies(std::string procedure, std::string variable)
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

std::vector<int> ModifiesBank::get_statements_modifies(std::string variable)
{
    return stmt_bank.get_reverse(variable);
}

std::vector<std::string> ModifiesBank::get_procedures_modifies(std::string variable)
{
    return proc_bank.get_reverse(variable);
}

std::vector<std::string> ModifiesBank::get_modified_by_procedure(std::string procedure)
{
    return proc_bank.get(procedure);
}

std::vector<std::string> ModifiesBank::get_modified_by_statement(int statement)
{
    return stmt_bank.get(statement);
}

bool ModifiesBank::is_modifies(int statement, std::string variable)
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

bool ModifiesBank::is_modifies(std::string procedure, std::string variable)
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

std::vector<std::string> ModifiesBank::get_all_modifies_procedures()
{
    return proc_bank.get_all_keys();
}

std::vector<int> ModifiesBank::get_all_modifies_statements()
{
    return stmt_bank.get_all_keys();
}

std::unordered_map<std::string, std::vector<std::string>> ModifiesBank::get_all_modifies_procedures_relationship()
{
    return proc_bank.copy();
}

std::unordered_map<int, std::vector<std::string>> ModifiesBank::get_all_modifies_statements_relationship()
{
    return stmt_bank.copy();
}

bool ModifiesBank::does_modifies_exist()
{
    return proc_bank.empty() && stmt_bank.empty();
}

bool ModifiesBank::insert_modifies_for_call(std::string caller, std::string callee) {
    std::vector<std::string> callee_var = this->get_modified_by_procedure(callee);
    bool result = false;

    if(callee_var.size() == 0)
    {
        return false;
    }

    for(std::string var: callee_var)
    {
        result = this->insert_modifies(caller, var);
        if(!result)
        {
            return false;
        }
    }
    return true;
}
