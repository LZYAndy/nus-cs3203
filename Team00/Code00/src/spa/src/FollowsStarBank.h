#ifndef AUTOTESTER_FOLLOWSSTARBANK_H
#define AUTOTESTER_FOLLOWSSTARBANK_H

#include "Bank.h"

class FollowsStarBank
{
public:
    /**
     * Check if the statement directly or indirectly Follows another statement.
     * In other words, Follows*(s1,s2).
     * @param stmt1 statement to be Followed.
     * @param stmt2 statement to Follows*,
     * @return true if stmt1 directly or indirectly Follows stmt2. In other words, Follows*(stmt1, stmt2).
     */
    bool is_follows_star(int stmt1, int stmt2);
 
    /**
     * Insert Follows* relationship to PKB.
     * @param stmt1 stmt# of statement followed.
     * @param stmt2 stmt# of statement follows.
     * @return true if the insert process is successful.
     */
    bool insert_follows_star(int stmt1, int stmt2);
   
    /**
     * Get all stmt# of statements that Follows* the queried statement.
     * @param stmt# of statement to be queried.
     * @return vector of stmt# that Follows* the queried statement.
     */
    std::vector<int> get_follows_star(int stmt);
 
   /**
     * Get all stmt# of statements that Followed* the queried statement.
     * @param stmt# of statement to be queried.
     * @return vector of stmt# that Followed* the queried statement.
     */
    std::vector<int> get_followed_star_by(int stmt);
 
    /**
     * Get all Follows* relationship that exists in FollowsStarBank.
     * @return unordered_map containing all Follows relationship that exists in PKB with 
     * the Follows as key and all that directly or indirectly Followed stored in a vector as value.
     */
    std::unordered_map<int, std::vector<int>> get_all_follows_star_relationship();
  
    /**
     * Check if there exist at least one Follows* relationship stored in PKB.
     * @return true if there is at least one Follows* relationship stored in PKB.
     */
    bool does_follows_star_exist();
  
    /**
     * Get all stmt# of statements that Follows directly or indirectly.
     * @return vector of stmt# that Follows directly or indirectly.
     */
    std::vector<int> get_all_follows_star();
  
    /**
     * Get all stmt# of statements that Followed directly or indirectly.
     * @return vector of stmt# that Followed directly or indirectly.
     */
    std::vector<int> get_all_followed_star();

private:
    Bank<int, int> follows_star_bank;
};

#endif //AUTOTESTER_FOLLOWSSTARBANK_H
