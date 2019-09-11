#ifndef AUTOTESTER_USESBANK_H
#define AUTOTESTER_USESBANK_H

#include "Bank.h"

using namespace std;

template <class T, class S>
class UsesBank: public Bank<T, S>
{
public:
    UsesBank();

    /*
     * Insert Uses relation for a statement into the UsesBank
     * Returns false if the relation already exists
     */
    bool insert_uses(int statement, string variable);

    /*
     * Insert Uses relation for a procedure into the UsesBank
     * Returns false if the relation already exists
     */
    bool insert_uses(string procedure, string variable);
};


#endif //AUTOTESTER_USESBANK_H
