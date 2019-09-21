#ifndef AUTOTESTER_ASSIGNPARSER_H
#define AUTOTESTER_ASSIGNPARSER_H

#include "PKB.h"
#include "CheckerUtil.h"
#include "Statement.h"
#include "StringUtil.h"
#include "ErrorMessages.h"

class AssignParser
{
public:
    /**
     * Inserts value into the respective tables (Var, Modifies, Assigns, Parent, Uses, Type).
     * @param pkb
     * @param statement
     * @param parent_prog_line
     */
    AssignParser(PKB &pkb, Statement statement, std::string parent_prog_line);

private:
    /**
     * Obtain the left hand side of an assign statement.
     * @param statement
     * @return Returns the left hand side in string.
     */
    std::string get_left(std::string statement);

    /**
     * Obtain the right hand side of an assign statement.
     * @param statement
     * @return Returns the right hand side in string.
     */
    std::string get_right(std::string statement);
};

#endif //AUTOTESTER_ASSIGNPARSER_H
