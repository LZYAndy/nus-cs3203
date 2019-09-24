#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"
#include "TNode.h"

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
    ProcedureAnalyser procedureAnalyser = ProcedureAnalyser(SIMPLE_prog);

    std::vector<Procedure> list_of_proc = procedureAnalyser.analyse();

    int num_of_proc = list_of_proc.size();

    for (int i = 0; i < num_of_proc; i++)
    {
        Procedure this_procedure = list_of_proc[i];
        StatementListParser statementListParser = StatementListParser(this_procedure.get_body(), 0);
        statementListParser.parse_stmt_list();
        std::vector<Statement> list_of_stmt = statementListParser.get_stmt_list();
        ParserInvoker parserInvoker = ParserInvoker(*pkb, list_of_stmt, this_procedure.get_name());
        parserInvoker.invoke_parser();
    }

    this->pkb->extract_design();

    return 0;
}
