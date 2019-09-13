#ifndef AUTOTESTER_READPARSER_H
#define AUTOTESTER_READPARSER_H

#include <string>
#include <regex>
#include "PKB.h"
#include "Statement.h"

using namespace std;

class ReadParser
{
public:
    ReadParser(PKB pkb, Statement statement, string parent_prog_line);

private:
    bool is_read_stmt_valid(string statement);

    string get_var(string statement);
};

#endif //AUTOTESTER_READPARSER_H
