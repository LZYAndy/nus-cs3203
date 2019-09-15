#include "StatementListParser.h"

StatementListParser::StatementListParser(string raw, int following_line)
{
    raw_stmt_list = raw;
}

vector<Statement> StatementListParser::get_stmt_list()
{
    return stmt_list;
}

void StatementListParser::parse_stmt_list()
{
    string source = strUti.replace_all_white_spaces(raw_stmt_list);
    
    while (!source.empty())
    {
        source = strUti.trim_left(source);
        string stmt_syn = source.substr(0,2);
        if (stmt_syn.compare("if") == 0)
        {
            source = parse_if(source);
            source = strUti.trim_left(source);
            continue;
        }
        stmt_syn = source.substr(0, 5);
        if (stmt_syn.compare("while") == 0)
        {
            source = parse_while(source);
            source = strUti.trim_left(source);
            continue;
        }
        else if (stmt_syn.compare("print") == 0)
        {
            source = parse_print(source);
            source = strUti.trim_left(source);
            continue;
        }
        stmt_syn = source.substr(0, 4);
        if (stmt_syn.compare("read") == 0)
        {
            source = parse_read(source);
            source = strUti.trim_left(source);
            continue;
        }
        else if (stmt_syn.compare("call") == 0)
        {
            source = parse_call(source);
            source = strUti.trim_left(source);
            continue;
        }
        // If the statement does not belong to the statement type above, then it should be an assign statement.
        source = parse_assign(source);
        source = strUti.trim_left(source);
    }
}

string StatementListParser::parse_while(string src)
{

}

string StatementListParser::parse_print(string src)
{

}

string StatementListParser::parse_read(string src)
{

}

string StatementListParser::parse_call(string src)
{

}

string StatementListParser::parse_assign(string src)
{

}

string StatementListParser::parse_if(string src)
{
    // Remove "if".
    src = src.substr(2);
    src = strUti.trim_left(src);

    // Find the condition.
    int condi_idx = parse_bracket(src, "(", ")");
    string condition = src.substr(1, condi_idx - 2);
    src = src.substr(condi_idx);
    src = strUti.trim_left(src);

    // Remove "then" and find the then part.
    src = src.substr(4);
    src = strUti.trim_left(src);

    int then_idx = parse_bracket(src, "{", "}");
    string first_blk = src.substr(1, then_idx - 2);
    src = src.substr(then_idx);
    src = strUti.trim_left(src);

    // Remove "else" and find the else part.
    src = src.substr(4);
    src = strUti.trim_left(src);

    int else_idx = parse_bracket(src, "{", "}");
    string second_blk = src.substr(1, else_idx - 2);
    src = src.substr(else_idx);
    src = strUti.trim_left(src);

    // TODO: Finish this line once the Statement class updated.
    //Statement if_stmt = Statement(next_line_number, );
    next_line_number++;

    // TODO: Insert statement.

    return src;
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
