#include "AssignParser.h"
#include "CheckerUtil.h"
#include "Statement.h"

regex assign_pattern("^\\s*([a-zA-Z][a-zA-Z0-9]+)\\s*=\\s*(.+)\\s*$");
regex all_word("\\w+");

AssignParser::AssignParser(PKB pkb, Statement statement, string parent_prog_line)
{
    if (!regex_match(statement.get_statement(), assign_pattern))
    {
        throw "Invalid assignment statement";
    }

    string left = get_left(statement.get_statement()); // Valid var
    string right = get_right(statement.get_statement());
    vector<string> all_var = get_all_var(right);

    // Insert var
    pkb.insert_variable(left);
    for (auto var: all_var)
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

string AssignParser::get_left(string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(1);
    }
    return "";
}

string AssignParser::get_right(string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(2);
    }
    return "";
}

vector<string> AssignParser::get_all_var(string sub_statement)
{
    std::smatch match;
    std::vector<std::string> all_var;

    while (regex_search(sub_statement, match, all_word))
    {
        string current_word = match[0];
        sub_statement = match.suffix().str();
        if (CheckerUtil::is_name_valid(match[0]))
        {
            all_var.push_back(match[0]);
        }
    }

    return all_var;
}
