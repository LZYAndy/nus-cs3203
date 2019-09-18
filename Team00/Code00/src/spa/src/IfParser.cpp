#include "IfParser.h"

IfParser::IfParser(PKB pkb, Statement statement, std::string parent_prog_line)
{

    std::string condition = statement.get_condition();
    std::vector<Statement> then_part = statement.get_first_block();
    std::vector<Statement> else_part = statement.get_second_block();

    if (!CheckerUtil::is_condition_valid(condition))
    {
        throw "Invalid if statement";
    }

    std::vector<std::string> all_variables = AssignParser::get_all_var(condition);
    int num_of_control_var = all_variables.size();
    for (int i = 0;i < num_of_control_var;i++)
    {
        pkb.insert_uses(statement.get_prog_line(), all_variables[i]);
    }

    int num_of_stmt_then = then_part.size();
    int num_of_stmt_else = else_part.size();

    if (CheckerUtil::is_const_valid(parent_prog_line))
    {
        pkb.insert_parent(std::stoi(parent_prog_line), statement.get_prog_line());
    }

    // Update parent relationship for if statement

    for (int i = 0;i < num_of_stmt_then;i++)
    {
        Statement this_stmt = then_part[i];
        pkb.insert_parent(statement.get_prog_line(), this_stmt.get_prog_line());
    }

    for (int i = 0;i < num_of_stmt_else;i++)
    {
        Statement this_stmt = else_part[i];
        pkb.insert_parent(statement.get_prog_line(), this_stmt.get_prog_line());
    }

    ParserInvoker thenInvoker = ParserInvoker(pkb, then_part, std::to_string(statement.get_prog_line()));
    thenInvoker.invoke_parser();

    ParserInvoker elseInvoker = ParserInvoker(pkb, else_part, std::to_string(statement.get_prog_line()));
    elseInvoker.invoke_parser();
}
