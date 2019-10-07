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

private:
    Bank<int, std::string> while_bank;
};


#endif //AUTOTESTER_WHILEBANK_H
