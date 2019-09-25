#pragma once
#ifndef AUTOTESTER_FOLLOWSBANK_H
#define AUTOTESTER_FOLLOWSBANK_H

#include "Bank.h"

class FollowsBank
{
public:
    /**
     * Check if the statement Follows another statement.
     * In other words, Follows(s1,s2).
     * @param stmt1 statement to be Followed
     * @param stmt2 statement to Follows
     * @return true if stmt1 Follows stmt2. In other words, Follows(stmt1, stmt2).
     */
    bool is_follows(int stmt1, int stmt2);

    /**
     * Insert Follows relationship into FollowsBank.
     * @param stmt1 stmt# of statement followed.
     * @param stmt2 stmt# of statement follows.
     * @return true if the insert process is successful.
     */
    bool insert_follows(int stmt1, int stmt2);

    /**
     * Check if there exist at least one Follows relationship stored in FollowsBank.
     * @return true if there is at least one Follows relationship store in FollowsBank.
     */
    bool does_follows_exists();

    /**
     * Get all Follows relationship that exists in FollowsBank.
     * @return unordered_map containing all Follows relationship that exists in FollowsBank with
     * the Follows as key and all Followed stored in a vector as value.
     */
    std::unordered_map<int, std::vector<int>> get_all_follows_relationship();

    /**
     * Get all stmt# of statements that Follows.
     * @return vector of stmt# that Follows.
     */
    std::vector<int> get_all_follows();

    /**
    * Get all stmt# of statements that Followed.
    * @return vector of stmt# that Followed.
    */
    std::vector<int> get_all_followed();

    /**
     * Get stmt# of statement that Followed the queried statement.
     * @param stmt# of statement to be queried.
     * @return stmt# that Followed the queried statement.
     */
    int get_followed_by(int stmt);

    /**
     * Get stmt# of statement that Follows the queried statement.
     * @param stmt# of statement to be queried.
     * @return stmt# that Follows the queried statement.
     */
    int get_follows(int stmt);

private:
    Bank<int, int> follows_bank;
};

#endif //AUTOTESTER_FOLLOWSBANK_H
