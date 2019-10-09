#include "CallParser.h"

regex call_statement_pattern("^[\\s]*call[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*);$");

CallParser::CallParser(PKB &pkb, Statement statement, std::string parent_prog_line)
{
    if (!is_call_stmt_valid(statement.get_statement()))
    {
        throw error_messages::invalid_call_statement;
    }

    if (statement.get_statement_type() != EntityType::CALL)
    {
        throw error_messages::invalid_call_type;
    }

    std::string call_proc = get_proc(statement.get_statement());

    //Insert parents
    if (regex_match(parent_prog_line, regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert call
    pkb.insert_calls(statement.get_procedure(), call_proc);

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool CallParser::is_call_stmt_valid(std::string statement)
{
    return regex_match(statement, call_statement_pattern);
}

std::string CallParser::get_proc(std::string statement)
{
    smatch match;
    if (regex_search(statement, match, call_statement_pattern))
    {
        return match.str(1);
    }
    return "";
}
