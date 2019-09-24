#ifndef AUTOTESTER_PARSERINVOKER_H
#define AUTOTESTER_PARSERINVOKER_H

#include <string>
#include "Statement.h"
#include "AssignParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "ReadParser.h"
#include "IfParser.h"
#include "WhileParser.h"
#include "PKB.h"
#include "pql_dto/Entity.h"

class ParserInvoker
{
private:
    std::vector<Statement> list_of_statement;
    PKB *pkb;
    std::string parent_prog_line;

public:
    // Constructor
    ParserInvoker(PKB &pkbi, std::vector<Statement> stmt_list, std::string parent_line);

    // Invoke Parser
    void invoke_parser();
};

#endif //AUTOTESTER_PARSERINVOKER_H
