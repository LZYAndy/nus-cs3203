#include "StatementListParser.h"

int StatementListParser::next_line_number = 1;

StatementListParser::StatementListParser(std::string raw)
{
    raw_stmt_list = raw;
}

std::vector<Statement> StatementListParser::get_stmt_list()
{
    return stmt_list;
}

void StatementListParser::parse_stmt_list()
{
    std::string source = StringUtil::replace_all_white_spaces(raw_stmt_list);
    
    while (!source.empty())
    {
        source = StringUtil::trim_left(source);
        std::string stmt_syn = source.substr(0,2);
        if (stmt_syn == "if")
        {
            std::string check = source.substr(2);

            // If there is no ( after word "if", then it is still not a if statement
            if (is_beginning_with(check, "("))
            {
                source = parse_if(source);
                source = StringUtil::trim_left(source);
                continue;
            }
        }
        stmt_syn = source.substr(0, 5);
        if (stmt_syn == "while")
        {
            std::string check = source.substr(5);

            // If there is no ( after word "while", then it is still not a while statement
            if (is_beginning_with(check, "("))
            {
                source = parse_while(source);
                source = StringUtil::trim_left(source);
                continue;
            }
        }
        else if (stmt_syn == "print")
        {
            std::string check = source.substr(5);

            // If there is = after word "print", then it is still not a print statement
            if (!is_beginning_with(check, "="))
            {
                source = parse_print(source);
                source = StringUtil::trim_left(source);
                continue;
            }
        }
        stmt_syn = source.substr(0, 4);
        if (stmt_syn == "read")
        {
            std::string check = source.substr(4);

            // If there is = after word "read", then it is still not a read statement
            if (!is_beginning_with(check, "="))
            {
                source = parse_read(source);
                source = StringUtil::trim_left(source);
                continue;
            }
        }
        else if (stmt_syn == "call")
        {
            std::string check = source.substr(4);

            // If there is = after word "call", then it is still not a call statement
            if (!is_beginning_with(check, "="))
            {
                source = parse_call(source);
                source = StringUtil::trim_left(source);
                continue;
            }
        }

        // If the statement does not belong to the statement type above, then it should be an assign statement.
        source = parse_assign(source);
        source = StringUtil::trim_left(source);
    }
}

std::string StatementListParser::parse_while(std::string src)
{
    Statement while_stmt = Statement(EntityType::WHILE, next_line_number, "");
    next_line_number++;

    // Remove "while".
    src = src.substr(5);
    src = StringUtil::trim_left(src);

    // Find the condition.
    int condi_idx = parse_bracket(src, "(", ")");
    std::string condition = src.substr(1, condi_idx - 2);
    src = src.substr(condi_idx);
    src = StringUtil::trim_left(src);

    // Find the loop part.
    int loop_idx = parse_bracket(src, "{", "}");
    std::string first_blk_raw = src.substr(1, loop_idx - 2);
    src = src.substr(loop_idx);
    src = StringUtil::trim_left(src);

    StatementListParser loop_parser = StatementListParser(first_blk_raw);
    loop_parser.parse_stmt_list();
    std::vector<Statement> first_block = loop_parser.get_stmt_list();

    while_stmt.set_condition(condition);
    while_stmt.set_first_block(first_block);

    stmt_list.push_back(while_stmt);
    return src;
}

std::string StatementListParser::parse_print(std::string src)
{
    int idx = find_semicolon(src);
    std::string rest = src.substr(idx);
    std::string print_body = src.substr(0, idx);

    Statement print_stmt = Statement(EntityType::PRINT, next_line_number, print_body);
    next_line_number++;

    stmt_list.push_back(print_stmt);

    return rest;
}

std::string StatementListParser::parse_read(std::string src)
{
    int idx = find_semicolon(src);
    std::string rest = src.substr(idx);
    std::string read_body = src.substr(0, idx);

    Statement read_stmt = Statement(EntityType::READ, next_line_number, read_body);
    next_line_number++;

    stmt_list.push_back(read_stmt);

    return rest;
}

std::string StatementListParser::parse_call(std::string src)
{
    int idx = find_semicolon(src);
    std::string rest = src.substr(idx);
    std::string call_body = src.substr(0, idx);

    Statement call_stmt = Statement(EntityType::CALL, next_line_number, call_body);
    next_line_number++;

    stmt_list.push_back(call_stmt);

    return rest;
}

std::string StatementListParser::parse_assign(std::string src)
{
    int idx = find_semicolon(src);
    std::string rest = src.substr(idx);
    std::string assign_body = src.substr(0, idx);

    Statement assign_stmt = Statement(EntityType::ASSIGN, next_line_number, assign_body);
    next_line_number++;

    stmt_list.push_back(assign_stmt);

    return rest;
}

std::string StatementListParser::parse_if(std::string src)
{
    Statement if_stmt = Statement(EntityType::IF, next_line_number, "");
    next_line_number++;

    // Remove "if".
    src = src.substr(2);
    src = StringUtil::trim_left(src);

    // Find the condition.
    int condi_idx = parse_bracket(src, "(", ")");
    std::string condition = src.substr(1, condi_idx - 2);
    src = src.substr(condi_idx);
    src = StringUtil::trim_left(src);

    // Remove "then" and find the then part.
    src = src.substr(4);
    src = StringUtil::trim_left(src);

    int then_idx = parse_bracket(src, "{", "}");
    std::string first_blk_raw = src.substr(1, then_idx - 2);
    src = src.substr(then_idx);
    src = StringUtil::trim_left(src);

    StatementListParser then_parser = StatementListParser(first_blk_raw);
    then_parser.parse_stmt_list();
    std::vector<Statement> first_block = then_parser.get_stmt_list();

    // Remove "else" and find the else part.
    src = src.substr(4);
    src = StringUtil::trim_left(src);

    int else_idx = parse_bracket(src, "{", "}");
    std::string second_blk_raw = src.substr(1, else_idx - 2);
    src = src.substr(else_idx);
    src = StringUtil::trim_left(src);

    StatementListParser else_parser = StatementListParser(second_blk_raw);
    else_parser.parse_stmt_list();
    std::vector<Statement> second_block = else_parser.get_stmt_list();

    if_stmt.set_condition(condition);
    if_stmt.set_first_block(first_block);
    if_stmt.set_second_block(second_block);

    stmt_list.push_back(if_stmt);

    return src;
}

int StatementListParser::parse_bracket(std::string src, std::string opening, std::string closing)
{
    // First step: remove the opening bracket
    src = src.substr(1);
    int count = 1;
    int index = 1;
    while (count > 0)
    {
        std::string this_pos = src.substr(0, 1);
        if (this_pos == opening)
        {
            count = count + 1;
        }
        else if (this_pos == closing)
        {
            count = count - 1;
        }
        src = src.substr(1);
        index = index + 1;
    }
    return index;
}

int StatementListParser::find_semicolon(std::string src)
{
    int index = 0;
    while (true)
    {
        std::string this_pos = src.substr(0, 1);
        if (this_pos == ";")
        {
            return index + 1;
        }
        index++;
    }
}

bool StatementListParser::is_beginning_with(std::string src, const std::string& match_char)
{
    src = StringUtil::trim_left(src);
    std::string this_char = src.substr(0, 1);
    return this_char == match_char;
}
