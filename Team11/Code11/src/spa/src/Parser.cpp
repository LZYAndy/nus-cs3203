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
    ProcedureAnalyser procedure_analyser = ProcedureAnalyser(SIMPLE_prog);

    std::vector<Procedure> list_of_proc = procedure_analyser.analyse();
    for (Procedure p : list_of_proc)
    {
        pkb->insert_procedure(p.get_name(), 1, {2}); // temp to build
    }

    int num_of_proc = list_of_proc.size();

    for (int i = 0; i < num_of_proc; i++)
    {
        Procedure this_procedure = list_of_proc[i];
        StatementListParser statementListParser = StatementListParser(this_procedure.get_body(), last_line_num);
        statementListParser.set_procedure(this_procedure.get_name());
        statementListParser.parse_stmt_list();
        std::vector<Statement> list_of_stmt = statementListParser.get_stmt_list();
        ParserInvoker parser_invoker = ParserInvoker(*pkb, list_of_stmt, this_procedure.get_name());
        parser_invoker.invoke_parser();
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

        // Insert into PKB with the first statements and last statements for the each procedure.
        int first_stmt = list_of_stmt[0].get_prog_line();
        std::vector<int> last_stmts = get_last_statements(list_of_stmt[list_of_stmt.size() - 1]);
        pkb->insert_procedure(this_procedure.get_name(), first_stmt, last_stmts);
    }

    bool de_check = this->pkb->extract_design();
    if (!de_check)
    {
        throw std::runtime_error(error_messages::cyclic_call);
    }

    return 0;
}

std::vector<int> Parser::get_last_statements(Statement statement)
{
    std::vector<int> result;
    if (statement.get_statement_type() != EntityType::IF)
    {
        result.push_back(statement.get_prog_line());
        return result;
    }
    else
    {
        std::vector<Statement> then_sl = statement.get_first_block();
        Statement last_then = then_sl[then_sl.size() - 1];
        result = append_vec(result, get_last_statements(last_then));
        std::vector<Statement> else_sl = statement.get_second_block();
        Statement last_else = else_sl[else_sl.size() - 1];
        result = append_vec(result, get_last_statements(last_else));
        return result;
    }
}

std::vector<int> Parser::append_vec(std::vector<int> src, std::vector<int> to_append)
{
    int leng = to_append.size();
    for(int i = 0;i < leng;i++)
    {
        src.push_back(to_append[i]);
    }
    return src;
}
