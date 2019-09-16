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
    proc_name = name;
    body_of_proc = body;
}
