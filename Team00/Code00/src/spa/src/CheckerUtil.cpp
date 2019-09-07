#include "CheckerUtil.h"

// Do not auto format the following strings. Spaces are left intentionally for readability.
namespace spa_grammar
{
    string whitespace = "\\s+";
    string const_value = "\\d+";
    string var_name, proc_name = "[a-zA-Z][a-zA-Z0-9]*";

    string spa_factor =  "(" + var_name + "|" + const_value +  ")"; // Add | "(" spa_expr ")" when used.
    string spa_term = "(" + spa_factor + "|" + spa_factor + "[*/%]" + spa_factor + ")";
    string spa_expr = "(" + spa_term + "|" + spa_term + "[+-]" + spa_term + ")";
}

bool parser_checker::is_procedure_name_valid(string stmt)
{
    return false;
}

// (1 > 2)
bool parser_checker::is_condition_valid(string stmt)
{
    return false;
}