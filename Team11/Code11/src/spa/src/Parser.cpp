#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"

Parser::Parser()
{
}

Parser::Parser(PKB *pkb)
{
    this->pkb = pkb;
}

int Parser::parse(std::string simple)
{
    SIMPLE_prog = simple;
    int last_line_num = 0;
    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(SIMPLE_prog);

    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();
    for (Procedure p : list_of_proc)
    {
        pkb->insert_procedure(p.get_name());
    }

    int num_of_proc = list_of_proc.size();

    for (int i = 0; i < num_of_proc; i++)
    {
        Procedure this_procedure = list_of_proc[i];
        StatementListParser statementListParser = StatementListParser(this_procedure.get_body(), last_line_num);
        statementListParser.set_procedure(this_procedure.get_name());
        statementListParser.parse_stmt_list();
        std::vector<Statement> list_of_stmt = statementListParser.get_stmt_list();
        ParserInvoker parserInvoker = ParserInvoker(*pkb, list_of_stmt, this_procedure.get_name());
        parserInvoker.invoke_parser();
        Statement last_statement = list_of_stmt[list_of_stmt.size() - 1];
        while (last_statement.get_statement_type() == EntityType::IF || last_statement.get_statement_type() == EntityType::WHILE)
        {
            if (last_statement.get_statement_type() == EntityType::IF)
            {
                std::vector<Statement> else_p = last_statement.get_second_block();
                last_statement = else_p[else_p.size() - 1];
            }
            else
            {
                std::vector<Statement> loop_p = last_statement.get_first_block();
                last_statement = loop_p[loop_p.size() - 1];
            }
        }
        last_line_num = last_statement.get_prog_line() + 1;
    }

    bool de_check = this->pkb->extract_design();
    if (!de_check)
    {
        throw std::runtime_error(error_messages::cyclic_call);
    }

    return 0;
}
