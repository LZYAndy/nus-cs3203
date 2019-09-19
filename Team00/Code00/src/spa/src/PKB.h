#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <numeric>

#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "DesignExtractor.h"
#include "ParentBank.h"
#include "ParentStarBank.h"
#include "AssignBank.h"

using namespace std;

class PKB
{
public:
    // Insert APIs
    bool insert_procedure(string name);
    bool insert_variable(string name);
    bool insert_uses(int statement, string variable);
    bool insert_uses(string procedure, string variable);
    /*
    * Insert Modifies relation for a statement into the ModifiesBank
    * Returns false if the relation already exists
    */
    bool insert_modifies(int statement, string variable);
    /*
    * Insert Modifies relation for a procedure into the ModifiesBank
    * Returns false if the relation already exists
    */
    bool insert_modifies(string procedure, string variable);
    /**
     * Insert Follows relationship to PKB.
     * @param stmt1 stmt# of statement followed.
     * @param stmt2 stmt# of statement follows.
     * @return true if the insert process is successful.
     */
    bool insert_follows(int stmt1, int stmt2);
    /**
     * Insert Parent relationship to PKB.
     * @param stmt1 stmt# of statement which is the parent.
     * @param stmt2 stmt# of statement that is the child of the parent statement.
     * @return true if the insert process is successful.
     */
    bool insert_parent(int stmt1, int stmt2);
    /**
     * Insert Assign relationship to PKB.
     * @param stmt1 stmt# of statement.
     * @param var variable name.
     * @param assignment RHS expression to be assigned to the variable.
     * @return true if the insert process is successful.
     */
    bool insert_assign(int stmt, string var, string assignment);
    /**
     * Insert Type relationship to PKB.
     * @param stmt1 stmt# of statement.
     * @param type type of statement.
     * @return true if the insert process is successful.
     */
    bool insert_type(int stmt, EntityType type);

    /**
     * Extract additional relationships and populate into PKB.
     * This method should only be called after all insertion have been done so that the method 
     * can extract all possible relationships based on the inserts.
     * @return true if the extract and populate process is successful.
     */
    bool extract_design();

    unordered_set<std::string> get_all_variables();
    /**
     * Get stmt# of all statements in PKB.
     * @return vector containing all the stmt# of statements.
     */
    vector<int> get_all_statement_nums();
    /**
     * Get stmt# of all WHILE statements in PKB.
     * @return vector containing all the stmt# of WHILE statements.
     */
    vector<int> get_all_whiles();
    /**
     * Get stmt# of all IF statements in PKB.
     * @return vector containing all the stmt# of IF statements.
     */
    vector<int> get_all_ifs();
    /**
     * Get stmt# of all ASSIGN statements in PKB.
     * @return vector containing all the stmt# of ASSIGN statements.
     */
    vector<int> get_all_assigns();
    /**
     * Get stmt# of all READ statements in PKB.
     * @return vector containing all the stmt# of READ statements.
     */
    vector<int> get_all_reads();
    /**
     * Get stmt# of all PRINT statements in PKB.
     * @return vector containing all the stmt# of PRINT statements.
     */
    vector<int> get_all_prints();
    /**
     * Get stmt# of all CALL statements in PKB.
     * @return vector containing all the stmt# of CALL statements.
     */
    vector<int> get_all_calls();
    unordered_set<std::string> get_all_procedures();

    /**
     * Get statement type.
     * @param stmt# of statement to be queried.
     * @return statement type.
     */
    EntityType get_statement_type(int stmt);
    /**
     * Get all stmt# of statements that Follows* the queried statement.
     * @param stmt# of statement to be queried.
     * @return vector of stmt# that Follows* the queried statement.
     */
    vector<int> get_follows_star(int stmt);
    /**
     * Get all stmt# of statements that Followed* the queried statement.
     * @param stmt# of statement to be queried.
     * @return vector of stmt# that Followed* the queried statement.
     */
    vector<int> get_followed_star_by(int stmt);
    /**
     * Get stmt# of statement that Follows the queried statement.
     * @param stmt# of statement to be queried.
     * @return stmt# that Follows the queried statement.
     */
    int get_follows(int stmt);
    /**
     * Get stmt# of statement that Followed the queried statement.
     * @param stmt# of statement to be queried.
     * @return stmt# that Followed the queried statement.
     */
    int get_followed_by(int stmt);
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
    vector<int> get_children(int stmt);
    /**
     * Get all stmt# of statements that is the Parent of the queried statement directly or
     * indrectly.
     * @param stmt# of statement to be queried.
     * @return stmt# that is Parent of the queried statement.
     */
    vector<int> get_parent_star(int stmt);
    /**
     * Get all stmt# of statements which the queried statement is directly or indirectly 
     * the Parent. 
     * @param stmt# of statement to be queried.
     * @return vector of stmt# which the queried statement is the Parent.
     */
    vector<int> get_children_star(int stmt);

    vector<int> get_statements_uses(string variable);
    vector<string> get_procedures_uses(string variable);
    vector<string> get_used_by_statement(int statement);
    vector<string> get_used_by_procedure(string procedure);

    vector<int> get_statements_modifies(string variable);
    vector<string> get_procedures_modifies(string variable);
    vector<string> get_modified_by_statement(int statement);
    vector<string> get_modified_by_procedure(string procedure);

    /**
     * Get all stmt# of ASSIGN statement containing the variable and its RHS expression exact matches the pattern.
     * @param var variable name in the ASSIGN statement.
     * @param pattern the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    vector<int> get_assign_pattern_matches(string var, string pattern);
    /** 
     * Get all stmt# of ASSIGN statement that containing the variable and its RHS expression contains the pattern.
     * @param var variable name in the ASSIGN statement.
     * @param pattern the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    vector<int> get_assign_pattern_contains(string var, string pattern);
    /**
     * get all stmt# of ASSIGN statement that its RHS expression exact matches the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    vector<int> get_all_assign_pattern_matches(string pattern);
    /**
     * Get all stmt# of ASSIGN statement that its RHS expression contains the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    vector<int> get_all_assign_pattern_contains(string pattern);

    /**
     * Check if the statement Follows another statement.
     * In other words, Follows(s1,s2).
     * @param stmt1 statement to be Followed
     * @param stmt2 statement to Follows
     * @return true if stmt1 Follows stmt2. In other words, Follows(stmt1, stmt2).
     */
    bool is_follows(int stmt1, int stmt2);
    /**
     * Check if the statement is the Parent of another statement.
     * In other words, Parent(s1,s2).
     * @param stmt1 statement that is the Parent
     * @param stmt2 statement that is the child of the Parent
     * @return true if stmt1 is the Parent of stmt2. In other words, Parent(stmt1, stmt2).
     */
    bool is_parent(int stmt1, int stmt2);
    /**
     * Check if the statement directly or indirectly Follows another statement.
     * In other words, Follows*(s1,s2).
     * @param stmt1 statement to be Followed.
     * @param stmt2 statement to Follows*,
     * @return true if stmt1 directly or indirectly Follows stmt2. In other words, Follows*(stmt1, stmt2).
     */
    bool is_follows_star(int stmt1, int stmt2);
    /**
     * Check if the statement is directly or indirectly the Parent of another statement.
     * In other words, Parent*(s1,s2).
     * @param stmt1 statement that is the Parent.
     * @param stmt2 statement that is the child of the Parent*.
     * @return true if stmt1 is directly or indirectly the Parent of stmt2. In other words, Parent*(stmt1, stmt2).
     */
    bool is_parent_star(int stmt1, int stmt2);

    bool is_uses(int statement, string variable);
    bool is_uses(string procedure, string variable);
    bool is_modifies(int statement, string variable);
    bool is_modifies(string procedure, string variable);

    /**
     * Check if there exist at least one Follows relationship stored in PKB.
     * @return true if there is at least one Follows relationship stored in PKB.
     */
    bool does_follows_exist();
    /**
     * Check if there exist at least one Follows* relationship stored in PKB.
     * @return true if there is at least one Follows* relationship stored in PKB.
     */
    bool does_follows_star_exist();
    /**
     * Check if there exist at least one Parent relationship stored in PKB.
     * @return true if there is at least one Parent relationship stored in PKB.
     */
    bool does_parent_exist();
    /**
     * Check if there exist at least one Parent* relationship stored in PKB.
     * @return true if there is at least one Parent* relationship stored in PKB.
     */
    bool does_parent_star_exist();

    /**
     * Get all stmt# of statements that Follows.
     * @return vector of stmt# that Follows.
     */
    vector<int> get_all_follows();
    /**
     * Get all stmt# of statements that Followed.
     * @return vector of stmt# that Followed.
     */
    vector<int> get_all_followed();
    /**
     * Get all stmt# of statements that Parent.
     * @return vector of stmt# that Parent.
     */
    vector<int> get_all_parent();
    /**
     * Get all stmt# of statements that is a child of Parent.
     * @return vector of stmt# that is a child of Parent.
     */
    vector<int> get_all_children();

    /**
     * Get all Parent relationship that exists in PKB.
     * @return unordered_map containing all Parent relationship that exists in PKB with 
     * the Parent as key and all the children stored in a vector as value.
     */
    unordered_map<int, std::vector<int>> get_all_parent_relationship();
    /**
     * Get all Follows relationship that exists in PKB.
     * @return unordered_map containing all Follows relationship that exists in PKB with 
     * the Follows as key and all Followed stored in a vector as value.
     */
    unordered_map<int, std::vector<int>> get_all_follows_relationship();
    /**
     * Get all Parent* relationship that exists in PKB.
     * @return unordered_map containing all Parent* relationship that exists in PKB with 
     * the Parent as key and all the descendants stored in a vector as value.
     */
    unordered_map<int, std::vector<int>> get_all_parent_star_relationship();
    /**
     * Get all Follows* relationship that exists in PKB.
     * @return unordered_map containing all Follows relationship that exists in PKB with 
     * the Follows as key and all that directly or indirectly Followed stored in a vector as value.
     */
    unordered_map<int, std::vector<int>> get_all_follows_star_relationship();

    /**
     * Get all stmt# of statements that Parent directly or indirectly.
     * @return vector of stmt# that Parent directly or indirectly.
     */
    vector<int> get_all_parent_star();
    /**
     * Get all stmt# of statements that Follows directly or indirectly.
     * @return vector of stmt# that Follows directly or indirectly.
     */
    vector<int> get_all_follows_star();
    /**
     * Get all stmt# of statements that is a child of Parent directly or indirectly.
     * @return vector of stmt# that is a child of Parent directly or indirectly.
     */
    vector<int> get_all_children_star();
    /**
     * Get all stmt# of statements that Followed directly or indirectly.
     * @return vector of stmt# that Followed directly or indirectly.
     */
    vector<int> get_all_followed_star();

    vector<int> get_all_modifies_statements();
    vector<string> get_all_modifies_procedures();
    vector<int> get_all_uses_statements();
    vector<string> get_all_uses_procedures();

    bool does_uses_exist();
    bool does_modifies_exist();

    unordered_map<string, vector<string>> get_all_modifies_procedures_relationship();
    unordered_map<int, vector<string>> get_all_modifies_statements_relationship();
    unordered_map<string, vector<string>> get_all_uses_procedures_relationship();
    unordered_map<int, vector<string>> get_all_uses_statements_relationship();

    /**
     * Get name of variable modified in ASSIGN statement.
     * @param assign stmt# of ASSIGN statement.
     * @return name of variable modified in ASSIGN statement.
     */
    string assign_to_variable(int assign);
    /**
     * Get all names of variables modified in a list of ASSIGN statement;
     * @param vector of ASSIGN stmt#
     * @return vector of variable names
     */
    vector<string> assigns_to_variables(vector<int> assigns);

private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
    unordered_set<string> varTable;
    unordered_set<string> procTable;
    UsesBank uses_bank;
    ModifiesBank modifies_bank;
    TypeBank type_bank;
    int last_statement_num = 0;
};