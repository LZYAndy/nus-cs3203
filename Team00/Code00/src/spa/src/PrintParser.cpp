#include "PrintParser.h"

std::regex print_statement_pattern("^[\\s]*print[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*)$");

PrintParser::PrintParser(PKB pkb, Statement statement, std::string parent_prog_line)
{
    if (!is_print_stmt_valid(statement.get_statement()))
    {
        throw "Invalid print statement";
    }

    std::string print_var = get_var(statement.get_statement());

    //Insert var
    pkb.insert_variable(print_var);

    //Insert uses
    pkb.insert_uses(statement.get_prog_line(), print_var);

    //Insert parents
    if (std::regex_match(parent_prog_line, std::regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool PrintParser::is_print_stmt_valid(std::string statement)
{
    if (std::regex_match(statement, print_statement_pattern))
    {
        return true;
    }
    return false;
}

std::string PrintParser::get_var(std::string statement)
{
    smatch match;
    if (std::regex_search(statement, match, print_statement_pattern))
    {
        return match.str(1);
    }
    return "";
}
