#include <string>
#include "ModifiesBank.h"

void ModifiesBank::insert_modifies(int statement, std::string variable)
{
    stmt_bank.put(statement, variable);
}

void ModifiesBank::insert_modifies(std::string procedure, std::string variable)
{
    proc_bank.put(procedure, variable);
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
        std::vector<std::string> tempBank = stmt_bank.get(statement);
        std::vector<int> myVector;
        for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it)
        {
            int index = std::distance(myVector.begin(), it);
            if (tempBank[index].compare(variable) == 0)
            {
                return true;
            }
        }
        return false;
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
        std::vector<std::string> tempBank = proc_bank.get(procedure);
        std::vector<int> myVector;
        for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it)
        {
            int index = std::distance(myVector.begin(), it);
            if (tempBank[index].compare(variable) == 0)
            {
                return true;
            }
        }
        return false;
    }
}

