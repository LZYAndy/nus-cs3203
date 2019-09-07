#include "AssignParser.h"

regex assign_pattern("");

AssignParser::AssignParser(PKB pkb, string statement, int parent_prog_line)
{
    if (!regex_match(statement, assign_pattern)){
        throw "Invalid assignment statement";
    }

    string left = get_left(statement);
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
    return std::string();
}

string AssignParser::get_right(string statement)
{
    return std::string();
}

string AssignParser::get_var(string sub_statement)
{
    return std::string();
}
