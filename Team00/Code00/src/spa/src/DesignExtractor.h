#pragma once
#ifndef AUTOTESTER_DESIGNEXTRACTOR_H
#define AUTOTESTER_DESIGNEXTRACTOR_H

#include "Bank.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "ParentBank.h"
#include "ParentStarBank.h"
#include "UsesBank.h"
#include "ModifiesBank.h"

class DesignExtractor
{
public:
    static void extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out);
    static void extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank);

private:
    static void extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank, std::vector<int> parents, int child);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
