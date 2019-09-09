#ifndef AUTOTESTER_FOLLOWSSTARBANK_H
#define AUTOTESTER_FOLLOWSSTARBANK_H

#include "Bank.h"

class FollowsStarBank: public Bank<int, int>
{
public:
    bool is_follows_star(int stmt1, int stmt2);
};

#endif //AUTOTESTER_FOLLOWSSTARBANK_H
