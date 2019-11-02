#ifndef AUTOTESTER_AFFECTSBIP_H
#define AUTOTESTER_AFFECTSBIP_H

#include <stack>
#include <unordered_set>

#include "NextBipBank.h"
#include "TypeBank.h"
#include "ModifiesBank.h"
#include "UsesBank.h"

class AffectsBipCompute
{
public:
    AffectsBipCompute();
    AffectsBipCompute(NextBipBank *next_bip_bank, ModifiesBank *modifies_bank, UsesBank *uses_bank, TypeBank *type_bank);
    /**
     * Check if Affects Relationship exists.
     * @return true if there Affects relationship.
     */
    bool does_affects_bip_exist();
    /**
     * Check if Affects relationship is valid between 2 assignment statement.
     * @param stmt1 affected stmt
     * @param stmt2 stmt to be affected
     * @return true if the relationship is true. else false.
     */
    bool is_affects_bip(int stmt1, int stmt2);
    /**
     * Get all assignment statements that is affected by queried assignment statement.
     * @param stmt quried statement
     * @return a vector of assignment statement affected by queried assignment statement.
     */
    std::vector<int> get_assigns_affects_bip(int stmt);
    /**
     * Get all assignment statements that the queried assignment statement affects.
     * @param stmt quried statement
     * @return a vector of assignment statement that the queried assignment statement affects
     */
    std::vector<int> get_assigns_affected_bip_by(int stmt);
    /**
     * Get all assignment statement that affect others.
     * @return a vector of assignment statement that affect others.
     */
    std::vector<int> get_all_assigns_affects_bip();
    /**
     * Get all assignment statement that affect others.
     * @return a vector of assignment statements that could be affected
     */
    std::vector<int> get_all_assigns_affected_bip();
    /**
     * Get all AffectsBip that exists.
     * @return a unordered_map of AffectBip relationshi that exists
     */
    std::unordered_map<int, std::vector<int>> get_all_affects_bip_relationship();
private:
    NextBipBank *next_bip_bank;
    ModifiesBank *modifies_bank;
    UsesBank *uses_bank;
    TypeBank *type_bank;
};

#endif