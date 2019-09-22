#ifndef AUTOTESTER_READPARSER_H
#define AUTOTESTER_READPARSER_H

#include <regex>
#include "PKB.h"
#include "Statement.h"
#include "ErrorMessages.h"

class ReadParser
{
public:
    /**
     * Inserts value into the respective tables (Var, Modifies, Parent, Type).
     * @param pkb
     * @param statement
     * @param parent_prog_line
     */
    ReadParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    /**
     * Checks if read statement is valid.
     * @param statement
     * @return Returns true if statement is valid, false otherwise.
     */
    bool is_read_stmt_valid(std::string statement);

    /**
     * Gets variable of a read statement.
     * @param statement
     * @return Returns the variable of a read statement.
     */
    std::string get_var(std::string statement);
};

#endif //AUTOTESTER_READPARSER_H
