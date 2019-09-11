#ifndef AUTOTESTER_MODIFIESBANK_H
#define AUTOTESTER_MODIFIESBANK_H

#include "Bank.h"

using namespace std;

template <class T, class S>
class ModifiesBank: public Bank<T, S>
{
public:
    ModifiesBank();

    /*
     * Insert Modifies relation for a statement into the ModifiesBank
     * Returns false if the relation already exists
     */
    bool insert_modifies(int statement, string variable);

    /*
     * Insert Modifies relation for a procedure into the ModifiesBank
     * Returns false if the relation already exists
     */
    bool insert_modifies(string procedure, string variable);
};


#endif //AUTOTESTER_MODIFIESBANK_H
