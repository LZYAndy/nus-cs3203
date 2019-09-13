#include "PrintParser.h"

regex print_statement_pattern("^[\\s]*print[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*)$");

PrintParser::PrintParser(PKB pkb, Statement statement, string parent_prog_line)
{
    if (!is_print_stmt_valid(statement.get_statement()))
    {
        throw "Invalid print statement";
    }

    string print_var = get_var(statement.get_statement());

    //Insert var
    pkb.insert_variable(print_var);

    //Insert uses
    pkb.insert_uses(statement.get_prog_line(), print_var);

    //Insert parents
    if (regex_match(parent_prog_line, regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool PrintParser::is_print_stmt_valid(string statement)
{
    if (regex_match(statement, print_statement_pattern))
    {
        return true;
    }
    return false;
}

string PrintParser::get_var(string statement)
{
    smatch match;
    if (regex_search(statement, match, print_statement_pattern))
    {
        return match.str(1);
    }
    return "";
}
