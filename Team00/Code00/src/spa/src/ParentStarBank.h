#ifndef AUTOTESTER_PARENTSTARBANK_H
#define AUTOTESTER_PARENTSTARBANK_H

#include "Bank.h"
#include <algorithm>

class ParentStarBank: public Bank<int, int>
{

public:
    bool is_parents_star(int stmt1, int stmt2);
};

#endif //AUTOTESTER_PARENTSTARBANK_H
