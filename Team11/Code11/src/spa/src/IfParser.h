#ifndef AUTOTESTER_IFPARSER_H
#define AUTOTESTER_IFPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "ParserInvoker.h"
#include "StringUtil.h"
#include "ErrorMessages.h"

class IfParser
{
public:
    /**
     * Parse the if statement and insert the necessary relationships and information into PKB.
     * @param pkb The PKB instance.
     * @param statement The if statement.
     * @param parent_prog_line The parent line number to help insert relative relationships.
     */
    IfParser(PKB &pkb, Statement statement, std::string parent_prog_line);
};

#endif //AUTOTESTER_IFPARSER_H
