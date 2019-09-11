#ifndef AUTOTESTER_TYPEBANK_H
#define AUTOTESTER_TYPEBANK_H

#include "Bank.h"

using namespace std;

template<class T, class S>
class TypeBank: public Bank<T, S>
{
public:
    TypeBank();

    /*
     * Insert Type for a statement into the typeBank
     * Returns false if the statement already exists
     */
};


#endif //AUTOTESTER_TYPEBANK_H
