#ifndef AUTOTESTER_AFFECTSBIP_H
#define AUTOTESTER_AFFECTSBIP_H

#include <stack>
#include <unordered_set>

#include "NextBipBank.h"
#include "TypeBank.h"
#include "ModifiesBank.h"
#include "UsesBank.h"
#include "NextBank.h"

class AffectsBipCompute
{
public:
    AffectsBipCompute();
    AffectsBipCompute(NextBipBank *next_bip_bank, ModifiesBank *modifies_bank, UsesBank *uses_bank, TypeBank *type_bank, NextBank *next_bank);
    /**
     * Check if AffectsBip Relationship exists.
     * @return true if there AffectsBip relationship.
     */
    bool does_affects_bip_exist();
    /**
     * Check if AffectsBip relationship is valid between 2 assignment statement.
     * @param stmt1 affected_bip stmt
     * @param stmt2 stmt to be affected_bip
     * @return true if the relationship is true. else false.
     */
    bool is_affects_bip(int stmt1, int stmt2);
    /**
     * Get all assignment statements that is affected_bip by queried assignment statement.
     * @param stmt queried statement
     * @return a vector of assignment statement affected_bip by queried assignment statement.
     */
    std::vector<int> get_assigns_affects_bip(int stmt);
    /**
     * Get all assignment statements that the queried assignment statement affects_bip.
     * @param stmt queried statement
     * @return a vector of assignment statement that the queried assignment statement affects_bip
     */
    std::vector<int> get_assigns_affected_bip_by(int stmt, bool called_from_get_all_relationship);
    /**
     * Get all assignment statement that AffectsBip others.
     * @return a vector of assignment statement that AffectsBip others.
     */
    std::vector<int> get_all_assigns_affects_bip();
    /**
     * Get all assignment statement that AffectsBip others.
     * @return a vector of assignment statements that could be affected_bip
     */
    std::vector<int> get_all_assigns_affected_bip();
    /**
     * Get all AffectsBip that exists.
     * @return a unordered_map of AffectBip relationship that exists
     */
    std::unordered_map<int, std::vector<int>> get_all_affects_bip_relationship();
    /**
     * Clear affects cache
     */
    void clear_cache();
private:
    NextBipBank *next_bip_bank;
    NextBank *next_bank;
    ModifiesBank *modifies_bank;
    UsesBank *uses_bank;
    TypeBank *type_bank;
    Bank<int, int> affects_cache;

    bool can_exist_affects_bip(int stmt1, int stmt2);
    bool modified_by_others(int stmt1, int inter_stmt);
    bool dfs_checking_assigns_affect(int stmt, int target);
};

#endif