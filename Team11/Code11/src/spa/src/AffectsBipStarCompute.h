#ifndef AFFECTS_BIP_STAR_H
#define AFFECTS_BIP_STAR_H

#include <vector>

#include "AffectsBipCompute.h"
#include "TypeBank.h"

class AffectsBipStarCompute
{
public:
    AffectsBipStarCompute(AffectsBipCompute *affects_bip_compute, TypeBank *type_bank);
    bool is_affects_bip_star(int assignment1, int assignment2);
    std::vector<int> get_affects_bip_star(int assignment);
    std::vector<int> get_affected_bip_star(int assignment);
    std::unordered_map<int, std::vector<int>> get_all_affects_bip_star_relationship();

private:
    AffectsBipCompute *affects_bip_compute;
    TypeBank *type_bank;
    bool is_affects_bip_star_helper(int assignment1, int assignment2, std::unordered_set<std::string> &states);
};
#endif