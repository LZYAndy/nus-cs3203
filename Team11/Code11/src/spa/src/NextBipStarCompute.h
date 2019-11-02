#ifndef AUTOTESTER_NEXTBIPSTAR_H
#define AUTOTESTER_NEXTBIPSTAR_H

#include <stack>
#include <unordered_set>

#include "NextBipBank.h"
#include "TypeBank.h"

class NextBipStarCompute
{
public:
    NextBipStarCompute(NextBipBank &bip_bank, TypeBank &type_bank);
    bool is_next_bip_star(int previous, int next);
    std::vector<int> get_next_bip_star(int previous);
    std::vector<int> get_previous_bip_star(int next);
    std::unordered_map<int, std::vector<int>> get_all_next_bip_star_relationship();
private:
    NextBipBank *bip_bank;
    TypeBank *type_bank;
};
#endif
