#ifndef AUTOTESTER_PRINTPARSER_H
#define AUTOTESTER_PRINTPARSER_H

#include <string>
#include <regex>
#include "PKB.h"

using namespace std;

class PrintParser
{
public:
    PrintParser(PKB pkb, string statement, string parent_prog_line);

private:
    bool is_print_stmt_valid(string statement);

    string get_var(string statement);
};

#endif //AUTOTESTER_PRINTPARSER_H
