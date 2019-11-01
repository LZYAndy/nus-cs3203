#ifndef AUTOTESTER_NEXTBIPSTAR_H
#define AUTOTESTER_NEXTBIPSTAR_H

#include <stack>
#include <unordered_set>

#include "NextBipBank.h"
#include "TypeBank.h"

class NextBipStarCompute
{
public:
    bool is_next_bip_star(NextBipBank &bip_bank, int previous, int next, TypeBank &type_bank);
    std::vector<int> get_next_bip_star(NextBipBank &bip_bank, int previous,  TypeBank &type_bank);
    std::vector<int> get_previous_bip_star(NextBipBank &bip_bank, int nex,  TypeBank &type_bank);
    std::vector<int> get_all_next_bip_star(NextBipBank &bip_bank);
    std::vector<int> get_all_previous_bip_star(NextBipBank &bip_bank);
    std::unordered_map<int, std::vector<int>> get_all_next_bip_star_relationship(NextBipBank &bip_bank, TypeBank &type_bank);
};
#endif
