#include "ParserInvoker.h"

ParserInvoker::ParserInvoker(PKB &pkb, std::vector<Statement> stmtlist, std::string parent_line)
{
    this->pkb = &pkb;
    list_of_statement = stmtlist;
    parent_prog_line = parent_line;
}

void ParserInvoker::invoke_parser()
{
    // This method will go through the vector and invoke the repective parser.
    int leng = list_of_statement.size();

    int last_stmt_num = 0;

    for (int i = 0;i < leng;i++)
    {
        Statement this_statement = list_of_statement[i];
        pkb->insert_type(this_statement.get_prog_line(), this_statement.get_statement_type());
        if (i != 0)
        {
            pkb->insert_follows(last_stmt_num, this_statement.get_prog_line());
        }
        if (this_statement.get_statement_type() == EntityType::ASSIGN)
        {
            AssignParser assignParser = AssignParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() ==  EntityType::PRINT)
        {
            PrintParser printParser = PrintParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::READ)
        {
            ReadParser readParser = ReadParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::CALL)
        {
            CallParser callParser = CallParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::IF)
        {
            IfParser ifParser = IfParser(*pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::WHILE)
        {
            WhileParser whileParser = WhileParser(*pkb, this_statement, parent_prog_line);
        }

        last_stmt_num = this_statement.get_prog_line();
    }
}
