#include "PrintParser.h"

regex print_statement_pattern("^\\s*print\\s+([a-zA-Z][a-zA-Z0-9]*\\s*)$");

PrintParser::PrintParser(PKB pkb, string statement, int parent_prog_line)
{
    if (!is_print_stmt_valid(statement))
    {
        throw "Invalid read statement";
    }

    //Insert var
    //Insert uses
    //Insert parents
    //Insert type
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
}
