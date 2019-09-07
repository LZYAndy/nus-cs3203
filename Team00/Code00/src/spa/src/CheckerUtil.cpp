#include "CheckerUtil.h"

string const_value = "\\d+";
string var_name, proc_name = "[a-zA-Z][a-zA-Z0-9]*";
string expr = "";
string factor =  "(" + var_name + "|" + const_value + ")";

bool parser_checker::is_procedure_name_valid(string stmt)
{
    return false;
}

// (1 > 2)
bool parser_checker::is_condition_valid(string stmt)
{
    return false;
}