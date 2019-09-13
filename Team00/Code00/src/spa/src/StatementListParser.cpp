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
    StringModification strMod;

    while (!source.empty())
    {
        source = strMod.trim_left(source);
        string stmt_syn = source.substr(0,2);
        if (stmt_syn.compare("if") == 0)
        {
            
        }

    }


}
