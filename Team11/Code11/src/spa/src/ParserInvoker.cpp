#include "ParserInvoker.h"

ParserInvoker::ParserInvoker(PKB &pkb, std::vector<Statement> stmt_list, std::string parent_line)
{
    this->pkb = &pkb;
    list_of_statement = stmt_list;
    parent_prog_line = parent_line;
}

void ParserInvoker::invoke_parser()
{
    // This method will go through the vector and invoke the repective parser.
    int leng = list_of_statement.size();

    int last_stmt_num = 0;

    for (int i = 0; i < leng; i++)
    {
        Statement this_statement = list_of_statement[i];
        pkb->insert_type(this_statement.get_prog_line(), this_statement.get_statement_type());
        int next_statement_num = 0;
        if (i != leng - 1)
        {
            next_statement_num = list_of_statement[i + 1].get_prog_line();
        }
        if (i != 0)
        {
            pkb->insert_follows(last_stmt_num, this_statement.get_prog_line());
        }
        if (this_statement.get_statement_type() == EntityType::ASSIGN)
        {
            if (next_statement_num != 0)
            {
                pkb->insert_next(this_statement.get_prog_line(), next_statement_num);
            }
            AssignParser assignParser = AssignParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() ==  EntityType::PRINT)
        {
            if (next_statement_num != 0)
            {
                pkb->insert_next(this_statement.get_prog_line(), next_statement_num);
            }
            PrintParser printParser = PrintParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::READ)
        {
            if (next_statement_num != 0)
            {
                pkb->insert_next(this_statement.get_prog_line(), next_statement_num);
            }
            ReadParser readParser = ReadParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::CALL)
        {
            if (next_statement_num != 0)
            {
                pkb->insert_next(this_statement.get_prog_line(), next_statement_num);
            }
            CallParser callParser = CallParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::IF)
        {
            std::vector<Statement> then_part = this_statement.get_first_block();
            std::vector<Statement> else_part = this_statement.get_second_block();
            int first_stmt_then = then_part[0].get_prog_line();
            int last_stmt_then = then_part[then_part.size() - 1].get_prog_line();
            int first_stmt_else = else_part[0].get_prog_line();
            int last_stmt_else = else_part[else_part.size() - 1].get_prog_line();
            pkb->insert_next(this_statement.get_prog_line(), first_stmt_then);
            pkb->insert_next(this_statement.get_prog_line(), first_stmt_else);
            if (next_statement_num != 0)
            {
                pkb->insert_next(last_stmt_then, next_statement_num);
                pkb->insert_next(last_stmt_else, next_statement_num);
            }
            IfParser ifParser = IfParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::WHILE)
        {
            if (next_statement_num != 0)
            {
                pkb->insert_next(this_statement.get_prog_line(), next_statement_num);
            }
            std::vector<Statement> loop_part = this_statement.get_first_block();
            int first_stmt_loop = loop_part[0].get_prog_line();
            int last_stmt_loop = loop_part[loop_part.size() - 1].get_prog_line();
            pkb->insert_next(this_statement.get_prog_line(), first_stmt_loop);
            pkb->insert_next(last_stmt_loop, this_statement.get_prog_line());
            WhileParser whileParser = WhileParser(*pkb, this_statement, parent_prog_line);
        }

        last_stmt_num = this_statement.get_prog_line();
    }
}
