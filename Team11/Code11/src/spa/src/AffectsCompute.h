#ifndef AUTOTESTER_AFFECTSCOMPUTE_H
#define AUTOTESTER_AFFECTSCOMPUTE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "NextBank.h"
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"
class AffectsCompute
{
public:
    /**
     * Get all statements affecting other statements i.e. get all a in Affects(a, _)
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return all statements affecting other statements
     */
    std::vector<int> get_all_assigns_affect(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * Get all statements affecting the input statement
     * @param stmt
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return all statements affecting the input statement
     */
    std::vector<int> get_assigns_affect(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * Get all Affects relationships in the program
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return all Affects relationships in the program
     */
    std::unordered_map<int, std::vector<int>> get_all_affects_relationship(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * Get all statements affected by other statements i.e. get all a in Affects(_, a)
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return all statements affected by other statements
     */
    std::vector<int> get_all_assigns_affected(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * Get all statements affected by the input statement
     * @param stmt
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return all statements affected by the input statement
     */
    std::vector<int> get_assigns_affected_by(int stmt, int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * If there exists at least one Affects relationship in the program
     * @param last_stmt_num
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return true if there is at least one Affects relationship, otherwise false
     */
    bool does_affects_exist(int last_stmt_num, NextBank next_bank, ModifiesBank modifies_bank, UsesBank uses_bank, TypeBank type_bank);
    /**
     * Check if there is an Affects relationship between statement1 and statement 2
     * @param stmt1
     * @param stmt2
     * @param next_bank
     * @param modifies_bank
     * @param uses_bank
     * @param type_bank
     * @return Return true if there is an Affects relationship between them, otherwise false
     */
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
