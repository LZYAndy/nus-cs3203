#ifndef AUTOTESTER_ASSIGNPARSER_H
#define AUTOTESTER_ASSIGNPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "Statement.h"
#include "StringUtil.h"

class AssignParser
{
public:
    AssignParser(PKB pkb, Statement statement, std::string parent_prog_line);

private:
    std::string get_left(std::string statement);

    std::string get_right(std::string statement);
};

#endif //AUTOTESTER_ASSIGNPARSER_H
