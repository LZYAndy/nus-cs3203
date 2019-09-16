#pragma once

#include "PKB.h"
#include "StatementListParser.h"
#include "Procedure.h"
#include "ParserInvoker.h"
#include "Procedure.h"
#include "ProcedureAnalyser.h"

class Parser
{
private:
    PKB pkb;
    std::string SIMPLE_prog;

public:
    // Constructor
    Parser(std::string simple);

    int Parse();
};
