#pragma once
#ifndef AUTOTESTER_FOLLOWSBANK_H
#define AUTOTESTER_FOLLOWSBANK_H

#include "Bank.h"

class FollowsBank: public Bank<int, int>::Bank
{
public:
    bool is_follows(int stmt1, int stmt2);
};

#endif //AUTOTESTER_FOLLOWSBANK_H
