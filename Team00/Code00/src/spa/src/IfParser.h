#ifndef AUTOTESTER_IFPARSER_H
#define AUTOTESTER_IFPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "ParserInvoker.h"

class IfParser
{
public:
    IfParser(PKB pkb, Statement statement, std::string parent_prog_line);
};

#endif //AUTOTESTER_IFPARSER_H
