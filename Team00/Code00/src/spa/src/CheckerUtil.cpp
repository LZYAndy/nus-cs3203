#include "CheckerUtil.h"

regex valid_name("^[a-zA-Z][a-zA-Z0-9]*$");
regex valid_const("^\\d+$");
regex valid_expr("");

bool CheckerUtil::is_name_valid(string stmt)
{
    if (!regex_match(stmt, valid_name))
    {
        return false;
    }
    return true;
}

bool CheckerUtil::is_const_valid(string stmt)
{
    if (!regex_match(stmt, valid_const))
    {
        return false;
    }
    return true;
}

bool CheckerUtil::is_expr_valid(string stmt)
{
    return false;
}

bool CheckerUtil::is_condition_valid(string stmt)
{
    return false;
}

bool CheckerUtil::is_bracket_balanced(string stmt)
{
    int count = 0;
    for (int i = 0; i<stmt.length(); i++)
    {
        if (stmt.at(i)=='(')
        {
            count++;
        }
        if (stmt.at(i)==')')
        {
            count--;
        }
        if (count<0)
        {
            return false;
        }
    }
    return count==0;
}

