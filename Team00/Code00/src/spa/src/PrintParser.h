#ifndef AUTOTESTER_PRINTPARSER_H
#define AUTOTESTER_PRINTPARSER_H

#include <regex>
#include "PKB.h"
#include "Statement.h"

class PrintParser
{
public:
    PrintParser(PKB pkb, Statement statement, std::string parent_prog_line);

private:
    bool is_print_stmt_valid(std::string statement);

    std::string get_var(std::string statement);
};

#endif //AUTOTESTER_PRINTPARSER_H
