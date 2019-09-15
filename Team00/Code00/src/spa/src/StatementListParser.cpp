#include "StatementListParser.h"

StatementListParser::StatementListParser(string raw)
{
    raw_stmt_list = raw;
}

vector<Statement> StatementListParser::get_stmt_list()
{
    return stmt_list;
}

void StatementListParser::parse_stmt_list()
{
    string source = raw_stmt_list;

    while (!source.empty())
    {
        source = strMod.trim_left(source);
        string stmt_syn = source.substr(0,2);
        if (stmt_syn.compare("if") == 0)
        {

        }

    }


}

string StatementListParser::parse_if(string src)
{
    // Remove "if".
    src = src.substr(2);
    src = strMod.trim_left(src);

    // Find the condition.
    int condi_idx = parse_bracket(src, "(", ")");
    string condition = src.substr(1, condi_idx - 2);
    src = src.substr(condi_idx);
    src = strMod.trim_left(src);


}

int StatementListParser::parse_bracket(string src, string opening, string closing)
{
    // First step: remove the opening bracket
    src = src.substr(1);
    int count = 1;
    int index = 1;
    while (count > 0)
    {
        string this_pos = src.substr(0, 1);
        if (this_pos.compare(opening) == 0)
        {
            count = count + 1;
        }
        else if (this_pos.compare(closing) == 0)
        {
            count = count - 1;
        }
        src = src.substr(1);
        index = index + 1;
    }
    return index;
}
