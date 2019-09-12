#include "AssignParser.h"

regex assign_pattern("^\\s*([a-zA-Z][a-zA-Z0-9]+)\\s*=\\s*(.+)\\s*$");
regex all_word("\\w+");

AssignParser::AssignParser(PKB pkb, string statement, int parent_prog_line)
{
    if (!regex_match(statement, assign_pattern))
    {
        throw "Invalid assignment statement";
    }

    string left = get_left(statement); // Valid var
    string right = get_right(statement);
    vector<string> all_var = get_all_var(right);

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
