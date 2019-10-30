#ifndef AUTOTESTER_AFFECTSCOMPUTE_H
#define AUTOTESTER_AFFECTSCOMPUTE_H

#include <vector>
#include <unordered_map>
#include "PKB.h"

class AffectsCompute {
public:
    std::vector<int> get_all_assigns_affect(int last_stmt_num, PKB& pkb);   //e.g. Affects(a, _)
    std::vector<int> get_assigns_affect(int stmt, int last_stmt_num, PKB& pkb);  //e.g. Affects(a, 2)
    std::unordered_map<int, std::vector<int>> get_all_affects_relationship(int last_stmt_num, PKB& pkb);   //e.g. Affects(a1, a2), a1 can equal to a2
    std::vector<int> get_all_assigns_affected(int last_stmt_num, PKB& pkb);   //e.g. Affects(_, a)
    std::vector<int> get_assigns_affected_by(int stmt, int last_stmt_num, PKB& pkb);   //e.g. Affects(1, a)
    bool does_affects_exist(int last_stmt_num, PKB& pkb);
    bool is_affects(int stmt1, int stmt2, PKB& pkb);

private:
    bool can_exist_affects(int stmt1, int stmt2, PKB& pkb);
    bool modified_by_others(int stmt1, int inter_stmt, PKB& pkb);
    bool affects_other_stmts(int stmt, PKB& pkb);
    bool affected_by_other_stmts(int stmt, PKB& pkb);
    bool dfs_checking_is_affects(int stmt1, int stmt2, PKB& pkb);
    bool dfs_checking_all_assign_affects(int stmt, PKB& pkb);
    bool dfs_checking_all_assigns_affected(int stmt, PKB& pkb);
    bool dfs_checking_assigns_affect(int stmt, int target, PKB& pkb);
    bool dfs_checking_assigns_affected_by(int target, int stmt, PKB& pkb);
};


#endif //AUTOTESTER_AFFECTSCOMPUTE_H
