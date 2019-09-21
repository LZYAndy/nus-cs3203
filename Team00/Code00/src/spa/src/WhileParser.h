#ifndef AUTOTESTER_WHILEPARSER_H
#define AUTOTESTER_WHILEPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "ParserInvoker.h"

class WhileParser
{
public:
    WhileParser(PKB &pkb, Statement statement, std::string parent_prog_line);
};

#endif //AUTOTESTER_WHILEPARSER_H
