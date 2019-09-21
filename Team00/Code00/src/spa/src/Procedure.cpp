#include <iostream>
#include "Procedure.h"

std::string Procedure::get_name()
{
    return proc_name;
}

std::string Procedure::get_body()
{
    return body_of_proc;
}

Procedure::Procedure(std::string name, std::string body)
{
    if (CheckerUtil::is_name_valid(name))
    {
        proc_name = name;
    }
    else
    {
        throw std::runtime_error(error_messages::invalid_proc_name);
    }
    body_of_proc = body;
}
