#include "AssignParser.h"

std::regex assign_pattern("^\\s*([a-zA-Z][a-zA-Z0-9]+)\\s*=\\s*(.+)\\s*$");

AssignParser::AssignParser(PKB pkb, Statement statement, std::string parent_prog_line)
{
    if (!regex_match(statement.get_statement(), assign_pattern))
    {
        throw "Invalid assignment statement";
    }

    std::string left = get_left(statement.get_statement()); // Valid var
    std::string right = get_right(statement.get_statement());
    vector<std::string> all_var = get_all_var(right);

    // Insert var
    pkb.insert_variable(left);
    for (const auto& var: all_var)
    {
        pkb.insert_variable(var);
    }

    // Insert modifies
    pkb.insert_modifies(statement.get_prog_line(), left);
    if (CheckerUtil::is_name_valid(parent_prog_line))
    {
        pkb.insert_modifies(parent_prog_line, left);
    }

    // Insert assigns
    pkb.insert_assign(statement.get_prog_line(), left, right);

    // Insert parents
    if (std::regex_match(parent_prog_line, std::regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    // Insert uses (if var is found at rhs)
    for (auto var: all_var)
    {
        pkb.insert_uses(statement.get_prog_line(), var);
    }

    // Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

std::string AssignParser::get_left(std::string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(1);
    }
    return "";
}

std::string AssignParser::get_right(std::string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(2);
    }
    return "";
}

vector<std::string> AssignParser::get_all_var(std::string sub_statement)
{
    std::smatch match;
    std::vector<std::string> all_var;

    while (regex_search(sub_statement, match, all_word))
    {
        std::string current_word = match[0];
        sub_statement = match.suffix().str();
        if (CheckerUtil::is_name_valid(match[0]))
        {
            all_var.push_back(match[0]);
        }
    }

    return all_var;
}
