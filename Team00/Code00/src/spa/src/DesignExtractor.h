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
    /**
     * Extract Follows* relationships and populate into PKB.
     * This method should only be called after all insertion have been done so that the method 
     * can extract all possible relationships based on the inserts.
     * @return true if the extract and populate process is successful.
     */
    static void extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out);
    /**
     * Extract Parent* relationships and populate into PKB.
     * This method should only be called after all insertion have been done so that the method 
     * can extract all possible relationships based on the inserts.
     * @return true if the extract and populate process is successful.
     */
    static void extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out);

private:
    static void extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, std::vector<int> parents, int child);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
