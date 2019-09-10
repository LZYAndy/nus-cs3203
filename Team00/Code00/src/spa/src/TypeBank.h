#ifndef AUTOTESTER_TYPEBANK_H
#define AUTOTESTER_TYPEBANK_H

#include "Bank.h"

using namespace std;

enum stmtType
{READ,
 PRINT,
 ASSIGN,
 WHILE,
 IF,
 CALL
};

class TypeBank: public Bank<int, stmtType>
{
public:
    TypeBank();

    /*
     * Insert Type for a statement into the typeBank
     * Returns false if the statement already exists
     */
    bool insert_type(int statement, stmtType variable);
};


#endif //AUTOTESTER_TYPEBANK_H
