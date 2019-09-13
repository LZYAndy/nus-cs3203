#include "ReadParser.h"

regex read_statement_pattern("^[\\s]*read[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*)$");

ReadParser::ReadParser(PKB pkb, Statement statement, string parent_prog_line)
{
    if (!is_read_stmt_valid(statement.get_statement()))
    {
        throw "Invalid read statement";
    }

    string read_var = get_var(statement.get_statement());

    //Insert var
    pkb.insert_variable(read_var);

    //Insert modifies
    pkb.insert_modifies(statement.get_prog_line(), read_var);
    if (regex_match(parent_prog_line, regex("^[a-zA-Z][a-zA-Z0-9]+$")))
    {
        pkb.insert_modifies(parent_prog_line, read_var);
    }

    //Insert parents
    if (regex_match(parent_prog_line, regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool ReadParser::is_read_stmt_valid(string statement)
{
    if (regex_match(statement, read_statement_pattern))
    {
        return true;
    }
    return false;
}

string ReadParser::get_var(string statement)
{
    smatch match;
    if (regex_search(statement, match, read_statement_pattern))
    {
        return match.str(1);
    }
    return "";
}
