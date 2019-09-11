#include "CheckerUtil.h"

regex all_word("\\w+");
regex valid_name("^[a-zA-Z][a-zA-Z0-9]*$");
regex valid_const("^\\d+$");
//(_word_)  (_[+-*/%]_(_word_))*  <- Do not remove the space.
regex valid_expr("^([\\(\\s]*(\\w*)[\\s\\)]*)(\\s*[+\\-*\\/%]\\s*([\\(\\s]*(\\w+)[\\s\\)]*))*$");

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

// Note: Statement containing empty spaces only is considered valid for this function.
bool CheckerUtil::is_expr_valid(string stmt)
{
    if (!is_bracket_balanced(stmt))
    {
        return false;
    }

    if (!regex_match(stmt, valid_expr))
    {
        return false;
    }

    smatch match;
    while (regex_search(stmt, match, all_word)) // Get all word, checks performed in while.
    {
        string current_word = match[0];
        stmt = match.suffix().str(); // Remove current word from statement.
        if (!is_name_valid(current_word) && !is_const_valid(current_word)) // Invalid type.
        {
            return false;
        }
    }

    return true;
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

