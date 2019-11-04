#ifndef COMPUTE_AFFECTS_STAR_H
#define COMPUTE_AFFECTS_STAR_H

#include <vector>
#include <unordered_map>

#include "AffectsCompute.h"

class PKB;

class AffectsStarCompute
{
public:
    /**
     * Check if one assignment statement affects the another assignment directly or indirectly.
     * That is to say Affects(1, 2).
     * @param assignment1 assignment statement to check if affects others
     * @param assignment2 assignment statement that is affected
     * @return true if Affects* relationship holds for the 2 assignment statement.
     */
    bool is_affects_star(PKB& pkb, int assignment1, int assignment2, bool called_by_affects_star);
    /**
     * Get all assignment statement that affects the quried assignment statement directly or indirectly.
     * That is to say Affects*(1, a).
     * @param assignment quried assignment statement
     * @return vector containing all the statement numbers of assignment statement affected by quried assignment.
     */
    std::vector<int> get_affects_star(PKB& pkb, int assignment);
    /**
     * Get all assignment statement that affected the quried assignment statement directly or indirectly.
     * That is to say Affects*(a, 1).
     * @param assignment quried assignment statement
     * @return vector containing all the statement numbers of assignment statement affects quried assignment.
     */
    std::vector<int> get_affected_star(PKB& pkb, int assignment, bool called_from_all_relationship);
    /**
     * Get all Affects* relationship that exists.
     * @return unodered_map that contains all the affects* relationship.
     */
    std::unordered_map<int, std::vector<int>> get_all_affects_star_relationship(PKB &pkb);
    /**
     * Clear affects* cache
     */
    void clear_cache();

private:
    Bank<int, int> affects_star_cache;
    bool is_affects_star_helper(PKB& pkb, int assignment1, int assignment2, std::unordered_set<std::string> &states);
};

#endif