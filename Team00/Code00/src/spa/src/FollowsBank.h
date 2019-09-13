#pragma once
#ifndef AUTOTESTER_FOLLOWSBANK_H
#define AUTOTESTER_FOLLOWSBANK_H

#include "Bank.h"
#include <algorithm>

class FollowsBank: public Bank<int, int>
{
public:
    bool is_follows(int stmt1, int stmt2);
};

#endif //AUTOTESTER_FOLLOWSBANK_H
