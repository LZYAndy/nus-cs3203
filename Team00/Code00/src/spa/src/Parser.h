#pragma once

#include "StatementListParser.h"
#include "ParserInvoker.h"
#include "ProcedureAnalyser.h"

class Parser
{
private:
    PKB *pkb;
    std::string SIMPLE_prog;

public:
    // Constructor
    Parser(PKB *pkb);

    int Parse(std::string SIMPLE_prog);
};
