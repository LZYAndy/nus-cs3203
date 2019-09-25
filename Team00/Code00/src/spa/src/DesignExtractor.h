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
    /**
     * Extract Follows* relationships and populate into PKB.
     * This method should only be called after all insertion have been done so that the method 
     * can extract all possible relationships based on the inserts.
     * @param &bank_in reference to FollowsBank.
     * @param &bank_out reference to FollowsStarBank.
     * @return true if extraction and insertion process is successful. return false if there is nothing to extract and insert.
     */
    static bool extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out);
    /**
     * Extract Parent* relationships and populate into PKB.
     * This method also populate new Uses and Modifies relationship created during the extraction process of Parent* relationship into the PKB.
     * This method should only be called after all insertion have been done so that the method 
     * can extract all possible relationships based on the inserts.
     * @param &bank_in reference to ParentBank.
     * @param &bank_out reference to ParentStarBank.
     * @param &uses_bank reference to UsesBank.
     * @param &modifies_bank reference to ModifiesBank.
     * @return true if extraction and insertion process is successful. return false if there is nothing to extract and insert.
     */
    static bool extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank);

private:
    static void extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, 
                                              UsesBank &uses_bank, ModifiesBank &modifies_bank, std::vector<int> parents, int child);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
