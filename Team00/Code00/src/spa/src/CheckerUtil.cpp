#include "CheckerUtil.h"

regex all_word("\\w+");
regex valid_name("^[a-zA-Z][a-zA-Z0-9]*$");
regex valid_const("^\\d+$");
//(_word_)  (_[+-*/%]_(_word_))*  <- Do not remove the space.
regex valid_expr("^([\\(\\s]*(\\w*)[\\s\\)]*)(\\s*[+\\-*\\/%]\\s*([\\(\\s]*(\\w+)[\\s\\)]*))*$");
regex valid_cond(
        "^\\s*[\\(\\s!]*([a-zA-Z][a-zA-Z0-9]*|[\\d]+)[\\s\\)]*(([+\\-*/%><]|[><=!]=)[\\s]*[\\(\\s!]*([a-zA-Z][a-zA-Z0-9]*|[\\d]+)[\\s\\)]*)*$");

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
    if (!is_bracket_balanced(stmt))
    {
        return false;
    }

    // Single var
    regex single_var("^[\\s]*[a-zA-Z0-9][\\s]*$");
    if (regex_match(stmt, single_var))
    {
        return false;
    }

    // Split by && and ||
    vector<string> sections;
    size_t prev = 0, pos;
    while ((pos = stmt.find_first_of("&|", prev))!=string::npos)
    {
        if (pos>prev)
        {
            sections.push_back(stmt.substr(prev, pos-prev));
        }

        prev = pos+1;
    }
    if (prev<stmt.length())
    {
        sections.push_back(stmt.substr(prev, string::npos));
    }

    // Check condition
    for (auto section: sections)
    {
        if (!regex_match(section, valid_cond))
        {
            return false;
        }
    }

    return true;
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
