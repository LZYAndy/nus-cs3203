#include "PrintParser.h"

std::regex print_statement_pattern("^[\\s]*print[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*);$");

PrintParser::PrintParser(PKB &pkb, Statement statement, std::string parent_prog_line)
{
    if (!is_print_stmt_valid(statement.get_statement()))
    {
        throw error_messages::invalid_print_statement;
    }

    if (statement.get_statement_type() != EntityType::PRINT)
    {
        throw error_messages::invalid_print_type;
    }

    std::string print_var = StringUtil::trim(get_var(statement.get_statement()), " \n\t\r\f\v");

    //Insert var
    pkb.insert_variable(print_var);

    //Insert uses
    pkb.insert_uses(statement.get_prog_line(), print_var);
    pkb.insert_uses(statement.get_procedure(), print_var);
    if (std::regex_match(parent_prog_line, std::regex("^[a-zA-Z][a-zA-Z0-9]+$")))
    {
        pkb.insert_uses(parent_prog_line, print_var);
    }

    //Insert parents
    if (std::regex_match(parent_prog_line, std::regex("^\\s*[0-9]+\\s*$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool PrintParser::is_print_stmt_valid(std::string statement)
{
    return std::regex_match(statement, print_statement_pattern);
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
