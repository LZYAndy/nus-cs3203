#ifndef AUTOTESTER_PARENTSTARBANK_H
#define AUTOTESTER_PARENTSTARBANK_H

#include "Bank.h"

class ParentStarBank
{

public:
    /**
     * Check if the statement is directly or indirectly the Parent of another statement.
     * In other words, Parent*(s1,s2).
     * @param stmt1 statement that is the Parent.
     * @param stmt2 statement that is the child of the Parent*.
     * @return true if stmt1 is directly or indirectly the Parent of stmt2. In other words, Parent*(stmt1, stmt2).
     */
    bool is_parent_star(int stmt1, int stmt2);
    /**
     * Insert Parent* relationship to ParentStarBank.
     * @param stmt1 stmt# of statement which is the parent.
     * @param stmt2 stmt# of statement that is the child of the parent statement.
     * @return true if the insert process is successful.
     */
    bool insert_parent_star(int stmt1, int stmt2);
    /**
     * Get all stmt# of statements that is the Parent of the queried statement directly or
     * indrectly.
     * @param stmt# of statement to be queried.
     * @return stmt# that is Parent of the queried statement.
     */
    std::vector<int> get_parent_star(int stmt);
    /**
     * Get all stmt# of statements which the queried statement is directly or indirectly 
     * the Parent. 
     * @param stmt# of statement to be queried.
     * @return vector of stmt# which the queried statement is the Parent.
     */
    std::vector<int> get_children_star(int stmt);
    /**
     * Get all Parent* relationship that exists in PKB.
     * @return unordered_map containing all Parent* relationship that exists in PKB with 
     * the Parent as key and all the descendants stored in a vector as value.
     */
    std::unordered_map<int, std::vector<int>> get_all_parent_star_relationship();
    /**
     * Check if there exist at least one Parent* relationship stored in PKB.
     * @return true if there is at least one Parent* relationship stored in PKB.
     */
    bool does_parent_star_exist();
    /**
     * Get all Parent* relationship that exists in PKB.
     * @return unordered_map containing all Parent* relationship that exists in PKB with 
     * the Parent as key and all the descendants stored in a vector as value.
     */
    std::vector<int> get_all_parent_star();
    /**
     * Get all stmt# of statements that is a child of Parent directly or indirectly.
     * @return vector of stmt# that is a child of Parent directly or indirectly.
     */
    std::vector<int> get_all_children_star();

private:
    Bank<int, int> parent_star_bank;
};

#endif //AUTOTESTER_PARENTSTARBANK_H
