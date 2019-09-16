#include "ParserInvoker.h"

ParserInvoker::ParserInvoker(PKB pkb, std::vector<Statement> stmtlist, std::string parent_line)
{
    pkb = pkbi;
    list_of_statement = stmtlist;
    parent_prog_line = parent_line;
}

void ParserInvoker::invoke_parser()
{
    // This method will go through the vector and invoke the repective parser.
    int leng = list_of_statement.size();

    for (int i = 0;i < leng;i++)
    {
        Statement this_statement = list_of_statement[i];
        if (this_statement.get_statement_type() == EntityType::ASSIGN)
        {
            AssignParser assignParser = AssignParser(pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() ==  EntityType::PRINT)
        {
            PrintParser printParser = PrintParser(pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == EntityType::READ)
        {
            ReadParser readParser = ReadParser(pkb, this_statement, parent_prog_line);
        }
        else if (this_statement.get_statement_type() == CallParser)
        {
            CallParser callParser = CallParser(pkb, this_statement, parent_prog_line);
        }
        // TODO: Implement the rest when ifparser and whileparser are ready.
    }
}
