#include "CheckerUtil.h"

std::regex all_word("\\w+");
std::regex valid_name("^[a-zA-Z][a-zA-Z0-9]*$");
std::regex valid_const("^\\d+$");
//(_word_)  (_[+-*/%]_(_word_))*  <- Do not remove the space.
std::regex valid_expr("^([\\(\\s]*(\\w*)[\\s\\)]*)(\\s*[+\\-*\\/%]\\s*([\\(\\s]*(\\w+)[\\s\\)]*))*$");
std::regex valid_cond(
        "^\\s*[\\(\\s!]*([a-zA-Z][a-zA-Z0-9]*|[\\d]+)[\\s\\)]*(([+\\-*/%><]|[><=!]=)[\\s]*[\\(\\s!]*([a-zA-Z][a-zA-Z0-9]*|[\\d]+)[\\s\\)]*)*$");

bool CheckerUtil::is_name_valid(std::string stmt)
{
    return std::regex_match(stmt, valid_name);
}

bool CheckerUtil::is_const_valid(std::string stmt)
{
    return std::regex_match(stmt, valid_const);
}

// Note: Statement containing empty spaces only is considered valid for this function.
bool CheckerUtil::is_expr_valid(std::string stmt)
{
    if (!is_bracket_balanced(stmt))
    {
        return false;
    }

    if (!std::regex_match(stmt, valid_expr))
    {
        return false;
    }

    std::smatch match;
    while (std::regex_search(stmt, match, all_word)) // Get all word, checks performed in while.
    {
        std::string current_word = match[0];
        stmt = match.suffix().str(); // Remove current word from statement.
        if (!is_name_valid(current_word) && !is_const_valid(current_word)) // Invalid type.
        {
            return false;
        }
    }

    return true;
}

bool CheckerUtil::is_condition_valid(std::string stmt)
{
    if (!is_bracket_balanced(stmt))
    {
        return false;
    }

    // Single expression e.g. (x + 1)
    if (std::regex_match(stmt, valid_expr))
    {
        return false;
    }

    // Split by && and ||
    std::vector<std::string> sections;
    size_t prev = 0, pos;
    while ((pos = stmt.find_first_of("&|", prev))!=std::string::npos)
    {
        if (pos>prev)
        {
            sections.push_back(stmt.substr(prev, pos-prev));
        }

        prev = pos+1;
    }
    if (prev<stmt.length())
    {
        sections.push_back(stmt.substr(prev, std::string::npos));
    }

    // Check condition
    for (const auto& section: sections)
    {
        if (!std::regex_match(section, valid_cond))
        {
            return false;
        }
    }

    return true;
}

bool CheckerUtil::is_bracket_balanced(std::string stmt)
{
    int count = 0;
    for (char i : stmt)
    {
        if (i=='(')
        {
            count++;
        }
        if (i==')')
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
