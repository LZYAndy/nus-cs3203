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
    AffectsBipCompute(NextBipBank &next_bip_bank, ModifiesBank &modifies_bank, UsesBank &uses_bank, TypeBank &type_bank);
    bool does_affects_bip_exist();
    bool is_affects_bip(int stmt1, int stmt2);
    std::vector<int> get_assigns_affects_bip(int stmt);
    std::vector<int> get_assigns_affected_bip_by(int stmt);
    std::vector<int> get_all_assigns_affects_bip();
    std::vector<int> get_all_assigns_affected_bip();
    std::unordered_map<int, std::vector<int>> get_all_affects_bip_relationship();
private:
    NextBipBank *next_bip_bank;
    ModifiesBank *modifies_bank;
    UsesBank *uses_bank;
    TypeBank *type_bank;
};

#endif