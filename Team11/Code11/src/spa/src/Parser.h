#pragma once

#include "StatementListParser.h"
#include "ParserInvoker.h"
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

private:
    PKB *pkb;
    std::string SIMPLE_prog;
};
