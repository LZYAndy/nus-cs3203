#ifndef AUTOTESTER_WHILEBANK_H
#define AUTOTESTER_WHILEBANK_H


#include "Bank.h"

class WhileBank {
public:
    /**
     * Insert a while statement into the while_bank.
     * @param statement number of the while statement
     * @param condition of the while statement
     * @return Return true if the while statement is inserted successfully, otherwise false.
     */
    bool insert_while(int statement, std::string condition);

    /**
     * Insert a statement in the stmtLst of the whileStmt.
     * @param whileStmt
     * @param statement
     * @return Return true if the statement is inserted successfully, otherwise false.
     */
    bool insert_stmt_in_while_stmtLst(int whileStmt, int statement);

    /**
     * Return true if the statement is a while statement.
     * @param statement
     * @return Return true if the statement is a while statement, otherwise false.
     */
    bool is_while(int statement);

    /**
     * Return all while statements stored in the while_bank.
     * @return Return all while statements stored in the while_bank.
     */
    std::vector<int> get_while_statements();

    /**
     * Return all statements in the statement list of the input while statement
     * @param statement
     * @return Return all statements in the statement list of the input while statement
     */
    std::vector<int> get_while_stmtLst(int statement);

private:
    Bank<int, std::string> while_bank;
    Bank<int, int> while_stmtLst;
};


#endif //AUTOTESTER_WHILEBANK_H
