#ifndef AUTOTESTER_READPARSER_H
#define AUTOTESTER_READPARSER_H

#include <regex>
#include "PKB.h"
#include "Statement.h"
#include "ErrorMessages.h"

class ReadParser
{
public:
    ReadParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    bool is_read_stmt_valid(std::string statement);

    std::string get_var(std::string statement);
};

#endif //AUTOTESTER_READPARSER_H
