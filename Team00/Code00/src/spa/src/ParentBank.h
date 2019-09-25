#pragma once
#ifndef AUTOTESTER_PARENTBANK_H
#define AUTOTESTER_PARENTBANK_H

#include "Bank.h"

class ParentBank
{
public:
    /**
     * Check if the statement is the Parent of another statement.
     * In other words, Parent(s1,s2).
     * @param stmt1 statement that is the Parent
     * @param stmt2 statement that is the child of the Parent
     * @return true if stmt1 is the Parent of stmt2. In other words, Parent(stmt1, stmt2).
     */
    bool is_parent(int stmt1, int stmt2);
    /**
     * Insert Parent relationship to PKB.
     * @param stmt1 stmt# of statement which is the parent.
     * @param stmt2 stmt# of statement that is the child of the parent statement.
     * @return true if the insert process is successful.
     */
    bool insert_parent(int stmt1, int stmt2);
    /**
     * Get all Parent relationship that exists in ParentBank.
     * @return unordered_map containing all Parent relationship that exists in PKB with
     * the Parent as key and all the children stored in a vector as value.
     */
    std::unordered_map<int, std::vector<int>> get_all_parent_relationship();
    /**
     * Get stmt# of statement that is the Parent of the queried statement.
     * @param stmt# of statement to be queried.
     * @return stmt# that is Parent of the queried statement.
     */
    int get_parent(int stmt);
    /**
     * Get all stmt# of statements which the queried statement is the Parent.
     * @param stmt# of statement to be queried.
     * @return vector of stmt# which the queried statement is the Parent.
     */
    std::vector<int> get_children(int stmt);
    /**
     * Get all stmt# of statements that is a child of Parent.
     * @return vector of stmt# that is a child of Parent.
     */
    std::vector<int> get_all_children();
    /**
     * Get all stmt# of statements that Parent.
     * @return vector of stmt# that Parent.
     */
    std::vector<int> get_all_parent();
    /**
     * Check if there exist at least one Parent relationship stored in PKB.
     * @return true if there is at least one Parent relationship stored in PKB.
     */
    bool does_parent_exist();

private:
    Bank<int, int> parent_bank;
};

#endif //AUTOTESTER_PARENTBANK_H
