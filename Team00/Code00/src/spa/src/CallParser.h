#ifndef AUTOTESTER_CALLPARSER_H
#define AUTOTESTER_CALLPARSER_H

#include <string>
#include <regex>
#include "PKB.h"
#include "Statement.h"

using namespace std;

class CallParser
{
public:
    CallParser(PKB pkb, Statement statement, string parent_prog_line);

private:
    bool is_call_stmt_valid(string statement);

    string get_proc(string statement);
};

#endif //AUTOTESTER_CALLPARSER_H
