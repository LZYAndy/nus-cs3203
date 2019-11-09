#ifndef AUTOTESTER_NEXTBIPSTAR_H
#define AUTOTESTER_NEXTBIPSTAR_H

#include <stack>
#include <unordered_set>

#include "NextBipBank.h"
#include "TypeBank.h"
#include "NextBank.h"

class NextBipStarCompute
{
public:
    /**
     * Default constructor for NextBipStarCompute
     */
    NextBipStarCompute();
    /**
     * Constructor for NextBipStarCompute.
     * @param bip_bank pointer to NextBipBank
     * @param type_bank pointer to TypeBank
     * @param next_bank pointer to NextBank
     */
    NextBipStarCompute(NextBipBank *bip_bank, TypeBank *type_bank, NextBank *next_bank);
    /**
     * Check if NextBip* exists between two program line.
     * @param previous
     * @param next
     * @return return true if they have NextBip* relationship
     */
    bool is_next_bip_star(int previous, int next);
    /**
     * Get all program lines that are in next position of NextBip.
     * @param previous
     * @return a vector of program lines that fulfill the condition
     */
    std::vector<int> get_next_bip_star(int previous);
     /**
     * Get all program lines that are in previous position of NextBip.
     * @param next
     * @return a vector of program lines that fulfill the condition
     */
    std::vector<int> get_previous_bip_star(int next);
    /**
     * Get all NextBip* relationship exists.
     * @return an unordered_map contains all NextBip* relationship
     */
    std::unordered_map<int, std::vector<int>> get_all_next_bip_star_relationship();
private:
    NextBipBank *bip_bank;
    NextBank *next_bank;
    TypeBank *type_bank;
};
#endif
