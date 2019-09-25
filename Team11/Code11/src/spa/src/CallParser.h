#ifndef AUTOTESTER_CALLPARSER_H
#define AUTOTESTER_CALLPARSER_H

#include <regex>

#include "PKB.h"
#include "Statement.h"
#include "ErrorMessages.h"

class CallParser
{
public:
    /**
     * Inserts value into the respective tables (Parent, Type).
     * @param pkb
     * @param statement
     * @param parent_prog_line
     */
    CallParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    /**
     * Checks if call statement is valid.
     * @param statement
     * @return Returns true if statement is valid, false otherwise.
     */
    bool is_call_stmt_valid(std::string statement);

    /**
     * Gets procedure name of a call statement.
     * @param statement
     * @return Returns the variable of a call statement.
     */
    std::string get_proc(std::string statement);
};

#endif //AUTOTESTER_CALLPARSER_H
