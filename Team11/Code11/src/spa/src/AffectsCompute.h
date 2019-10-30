#ifndef AUTOTESTER_AFFECTSCOMPUTE_H
#define AUTOTESTER_AFFECTSCOMPUTE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "NextBank.h"
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"
class AffectsCompute {
public:
    std::vector<int> get_all_assigns_affect(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);   //e.g. Affects(a, _)
    std::vector<int> get_assigns_affect(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);  //e.g. Affects(a, 2)
    std::unordered_map<int, std::vector<int>> get_all_affects_relationship(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);   //e.g. Affects(a1, a2), a1 can equal to a2
    std::vector<int> get_all_assigns_affected(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);   //e.g. Affects(_, a)
    std::vector<int> get_assigns_affected_by(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);   //e.g. Affects(1, a)
    bool does_affects_exist(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool is_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);

private:
    bool can_exist_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool modified_by_others(int stmt1, int inter_stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool affects_other_stmts(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool affected_by_other_stmts(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool dfs_checking_is_affects(int stmt1, int stmt2, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool dfs_checking_all_assign_affects(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool dfs_checking_all_assigns_affected(int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool dfs_checking_assigns_affect(int stmt, int target, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    bool dfs_checking_assigns_affected_by(int target, int stmt, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
};


#endif //AUTOTESTER_AFFECTSCOMPUTE_H
