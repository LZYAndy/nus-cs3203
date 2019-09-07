#pragma once
#ifndef AUTOTESTER_DESIGNEXTRACTOR_H
#define AUTOTESTER_DESIGNEXTRACTOR_H

#include "Bank.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "ParentBank.h"
#include "ParentStarBank.h"

class DesignExtractor
{
public:
    static void extract_follows_star(FollowsBank* bank_in, FollowsStarBank* bank_out);
    static void extract_parent_star(ParentBank* bank_in, ParentStarBank* bank_out);

private:
    static void extract_star(Bank<int,int>* bank_in, Bank<int,int>* bank_out);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
