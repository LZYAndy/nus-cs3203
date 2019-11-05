#ifndef AFFECTS_BIP_STAR_H
#define AFFECTS_BIP_STAR_H

#include <vector>

#include "AffectsBipCompute.h"
#include "TypeBank.h"

class AffectsBipStarCompute
{
public:
    AffectsBipStarCompute();
    AffectsBipStarCompute(AffectsBipCompute *affects_bip_compute, TypeBank *type_bank);
    /**
     * Check if AffectsBip* relationship is valid between 2 assignment statement.
     * @param stmt1 affected_bip stmt
     * @param stmt2 stmt to be affected_bip
     * @return true if the relationship is true. else false.
     */
    bool is_affects_bip_star(int assignment1, int assignment2);
    /**
     * Get all assignment statements that is affected_bip* by queried assignment statement.
     * @param stmt queried statement
     * @return a vector of assignment statement affected_bip* by queried assignment statement.
     */
    std::vector<int> get_affects_bip_star(int assignment);
    /**
     * Get all assignment statements that is AffectsBip* by queried assignment statement.
     * @param stmt queried statement
     * @return a vector of assignment statement AffectsBip* by queried assignment statement.
     */
    std::vector<int> get_affected_bip_star(int assignment);
    /**
    * Get all AffectsBip* that exists.
    * @return a unordered_map of AffectBip relationship that exists
    */
    std::unordered_map<int, std::vector<int>> get_all_affects_bip_star_relationship();

private:
    AffectsBipCompute *affects_bip_compute;
    TypeBank *type_bank;
    bool is_affects_bip_star_helper(int assignment1, int assignment2, std::unordered_set<std::string> &states);
};
#endif