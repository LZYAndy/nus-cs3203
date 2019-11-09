#pragma once

#include "StatementListParser.h"
#include "ParserInvoker.h"
#include "StringUtil.h"
#include "ProcedureAnalyser.h"

class Parser
{
public:

    /**
     * Constructor of Parser with an instance of pkb
     * @param pkb the pkb instance
     */
    Parser(PKB *pkb);

    /**
     * Constructor of Parser without an instance of pkb.
     */
    Parser();

    /**
     * Parse the whole SIMPLE program and populate the necessary relationships and information into PKB
     * @param SIMPLE_prog the source SIMPLE program
     * @return 0
     */
    int parse(std::string SIMPLE_prog);

    /**
     * This method will return a vector containing all the last statements in the procedure.
     * @param statement The statement that is the last statement in the statement list
     * @return a vector of last statements.
     */
    std::vector<int> get_last_statements(Statement statement);

    /**
     * This method is to append the vector to_append to the back of vector src and returns src.
     * @param src The source vector.
     * @param to_append The vector to append at the back.
     * @return the source vector.
     */
    std::vector<int> append_vec(std::vector<int> src, std::vector<int> to_append);

    /**
     * Find all the call statements and check whether the procedure been called exist or not.
     * @return true if there is no invalid calls.
     */
    bool check_calls_exist();

    /**
     * Check whether the procedure called exists or not.
     * @param call_stmt The call statement.
     * @return true if the call statement is valid, false otherwise.
     */
    bool check_proc_exist(std::string call_stmt);

    /**
     * Check through the statement list and find out all the call statements.
     * @param stmt_list The statement list we need to check.
     * @return true if there is no invalid calls, false otherwise.
     */
    bool check_through_stmt_list(std::vector<Statement> stmt_list);

private:
    PKB *pkb;
    std::string SIMPLE_prog;
    std::vector<Procedure> list_of_proc;
};
