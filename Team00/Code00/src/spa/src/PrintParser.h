#ifndef AUTOTESTER_PRINTPARSER_H
#define AUTOTESTER_PRINTPARSER_H

#include <regex>
#include "PKB.h"
#include "Statement.h"
#include "StringUtil.h"
#include "ErrorMessages.h"

class PrintParser
{
public:
    /**
     * Inserts value into the respective tables (Var, Uses, Parent, Type).
     * @param pkb
     * @param statement
     * @param parent_prog_line
     */
    PrintParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    /**
     * Checks if print statement is valid.
     * @param statement
     * @return Returns true if statement is valid, false otherwise.
     */
    bool is_print_stmt_valid(std::string statement);

    /**
     * Gets variable of a print statement.
     * @param statement
     * @return Returns the variable of a print statement.
     */
    std::string get_var(std::string statement);
};

#endif //AUTOTESTER_PRINTPARSER_H
