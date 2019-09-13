#include "Procedure.h"

string Procedure::get_name()
{
    return proc_name;
}

string Procedure::get_body()
{
    return body_of_proc;
}

Procedure::Procedure(string name, string body)
{
    proc_name = name;
    body_of_proc = body;
}
