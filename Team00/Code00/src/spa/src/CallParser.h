#ifndef AUTOTESTER_CALLPARSER_H
#define AUTOTESTER_CALLPARSER_H

#include <regex>

#include "PKB.h"
#include "Statement.h"
#include "ErrorMessages.h"

class CallParser
{
public:
    CallParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    bool is_call_stmt_valid(std::string statement);

    std::string get_proc(std::string statement);
};

#endif //AUTOTESTER_CALLPARSER_H
