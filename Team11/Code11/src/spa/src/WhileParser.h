#ifndef AUTOTESTER_WHILEPARSER_H
#define AUTOTESTER_WHILEPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "ParserInvoker.h"
#include "ErrorMessages.h"

class WhileParser
{
public:
    /**
     * Parse the while statement and insert the necessary relationships and information into PKB.
     * @param pkb The PKB instance
     * @param statement The while statement.
     * @param parent_prog_line The parent line number to help insert relative relationships.
     */
    WhileParser(PKB &pkb, Statement statement, std::string parent_prog_line);
};

#endif //AUTOTESTER_WHILEPARSER_H
