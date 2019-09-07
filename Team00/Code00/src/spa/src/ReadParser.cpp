#include "ReadParser.h"

regex read_statement_pattern("^\\s*read\\s+([a-zA-Z][a-zA-Z0-9]*\\s*)$");

ReadParser::ReadParser(PKB pkb, string statement, int parent_prog_line)
{
    if (!is_read_valid(statement))
    {
        throw "Invalid read statement";
    }

    //Insert var
    //Insert modifies
    //Insert parents
    //Insert type
}

bool ReadParser::is_read_valid(string statement)
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
}
