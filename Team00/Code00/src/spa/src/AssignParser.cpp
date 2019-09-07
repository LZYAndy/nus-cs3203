#include "AssignParser.h"

regex assign_pattern("^\\s*([a-zA-Z][a-zA-Z0-9]+)\\s*=\\s*(.+)\\s*$");

AssignParser::AssignParser(PKB pkb, string statement, int parent_prog_line)
{
    if (!regex_match(statement, assign_pattern))
    {
        throw "Invalid assignment statement";
    }

    string left = get_left(statement); // Valid var
    string right = get_right(statement);

    // Insert var
    // Insert modifies
    // Insert assigns
    // Insert parents
    // Insert uses (if var is found at rhs)
    // Insert type

}

string AssignParser::get_left(string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(1);
    }
}

string AssignParser::get_right(string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(2);
    }
}

string AssignParser::get_var(string sub_statement)
{
    return std::string();
}
