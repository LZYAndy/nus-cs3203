#pragma once

#include "StatementListParser.h"
#include "ParserInvoker.h"
#include "ProcedureAnalyser.h"

class Parser
{
public:
    // Constructor
    Parser(PKB *pkb);
    Parser();
    int parse(std::string SIMPLE_prog);

private:
    PKB *pkb;
    std::string SIMPLE_prog;
};
