#pragma once
#ifndef AUTOTESTER_PARENTBANK_H
#define AUTOTESTER_PARENTBANK_H

#include "Bank.h"
#include <algorithm>

class ParentBank : public Bank<int, int>
{
public:
    bool is_parent(int stmt1, int stmt2);
};

#endif //AUTOTESTER_PARENTBANK_H
