#include "WhileBank.h"

bool WhileBank::insert_while(int statement, std::string condition) {
    if (statement <= 0) {
        return false;
    }
    else
    {
        while_bank.put(statement, condition);
        return true;
    }
}
