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
    /**
     * Insert a procedure into the procTable.
     * @param name
     * @return Return true if the procedure is inserted successfully, otherwise false.
     */
    bool insert_procedure(string name);

    /**
     * Insert a variable into the varTable.
     * @param name
     * @return Return true if the variable is inserted successfully, otherwise false.
     */
    bool insert_variable(string name);

    /**
     * Insert a Uses relationship between the input statement and the input variable into uses_bank.
     * @param statement
     * @param variable
     * @return Return true if the Uses relationship is inserted successfully, otherwise false.
     */
    bool insert_uses(int statement, string variable);

    /**
     * Insert a Uses relationship between the input procedure and the input variable into uses_bank.
     * @param procedure
     * @param variable
     * @return Return true if the Uses relationship is inserted successfully, otherwise false.
     */
    bool insert_uses(string procedure, string variable);

    /**
     * Insert a Modifies relationship between the input statement and the input variable into modifies_bank.
     * @param statement
     * @param variable
     * @return Return true if the Uses relationship is inserted successfully, otherwise false.
     */
    bool insert_modifies(int statement, string variable);

    /**
     * Insert a Modifies relationship between the input procedure and the input variable into modifies_bank.
     * @param procedure
     * @param variable
     * @return Return true if the Uses relationship is inserted successfully, otherwise false.
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

    /**
     * Insert constant into PKB.
     * @param constant
     * @return true if insert is successful.
     */
    bool insert_constant(int constant);

    /**
     * Get all variables in the varTable.
     * @return Return a string unordered_set of variables that are contained in the varTable.
     */
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

    /**
     * Get all procedures in the procTable.
     * @return Return a string unordered_set of procedures that are contained in the procTable.
     */
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

    /**
     * Get all statements that uses the input variable.
     * @param variable
     * @return Return an integer vector of all statement that uses the variable.
     */
    vector<int> get_statements_uses(string variable);

    /**
     * Get all procedures that uses the input variable.
     * @param variable
     * @return Return an integer vector of all procedure that uses the variable.
     */
    vector<string> get_procedures_uses(string variable);

    /**
     * Get all variables used by the input statement.
     * @param statement
     * @return Return a string vector of variables used by the statement.
     */
    vector<string> get_used_by_statement(int statement);

    /**
     * Get all variables used by the input procedure.
     * @param procedure
     * @return Return a string vector of variables used by the procedure.
     */
    vector<string> get_used_by_procedure(string procedure);

    /**
     * Get all statements that modifies the input variable.
     * @param variable
     * @return Return an integer vector of all statement that modifies the variable.
     */
    vector<int> get_statements_modifies(string variable);

    /**
     * Get all procedures that modifies the input variable.
     * @param variable
     * @return Return a string vector of all procedures that modifies the variable.
     */
    vector<string> get_procedures_modifies(string variable);

    /**
     * Get all variables modifies by the input statement.
     * @param statement
     * @return Return a string vector of variables modifies by the statement.
     */
    vector<string> get_modified_by_statement(int statement);

    /**
     * Get all variables modifies by the input procedure.
     * @param procedure
     * @return Return a string vector of variables modifies by the statement.
     */
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

    /**
     * Return true if there is a Uses relationship between the input statement and the input variable.
     * @param statement
     * @param variable
     * @return Return true if there is a Uses relationship between the input statement and the input variable.
     */
    bool is_uses(int statement, string variable);

    /**
     * Return true if there is a Uses relationship between the input procedure and the input variable.
     * @param procedure
     * @param variable
     * @return Return true if there is a Uses relationship between the input procedure and the input variable.
     */
    bool is_uses(string procedure, string variable);

    /**
     * Return true if there is a Modifies relationship between the input statement and the input variable.
     * @param statement
     * @param variable
     * @return Return true if there is a Modifies relationship between the input statement and the input variable.
     */
    bool is_modifies(int statement, string variable);

    /**
     * Return true if there is a Modifies relationship between the input procedure and the input variable.
     * @param procedure
     * @param variable
     * @return Return true if there is a Modifies relationship between the input procedure and the input variable.
     */
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

    /**
     * Get all statements having one or more Modifies relationships.
     * @return Return an integer vector of statements having one or more Modifies relationships.
     */
    vector<int> get_all_modifies_statements();

    /**
     * Get all procedures having one or more Modifies relationships.
     * @return Return a string vector of procedures having one or more Modifies relationships.
     */
    vector<string> get_all_modifies_procedures();

    /**
     * Get all statements having one or more Uses relationships.
     * @return Return an integer vector of statements having one or more Uses relationships.
     */
    vector<int> get_all_uses_statements();

    /**
     * Get all procedures having one or more Uses relationships.
     * @return Return a string vector of procedures having one or more Uses relationships.
     */
    vector<string> get_all_uses_procedures();

    /**
     * Return true if there exists at least one Uses relationship in this program.
     * @return Return true if there exists at least one Uses relationship in this program.
     */
    bool does_uses_exist();

    /**
     * Return true if there exists at least one Modifies relationship in this program.
     * @return Return true if there exists at least one Modifies relationship in this program.
     */
    bool does_modifies_exist();

    /**
     * Get all procedure-variable Modifies relationships.
     * @return Return an unordered_map<string, vector<string>> with procedure name as key and variable(s) as value.
     */
    unordered_map<string, vector<string>> get_all_modifies_procedures_relationship();

    /**
     * Get all statement-variable Modifies relationships.
     * @return Return an unordered_map<int, vector<string>> with statement number as key and variable(s) as value.
     */
    unordered_map<int, vector<string>> get_all_modifies_statements_relationship();

    /**
     * Get all procedure-variable Uses relationships.
     * @return Return an unordered_map<string, vector<string>> with procedure name as key and variable(s) as value.
     */
    unordered_map<string, vector<string>> get_all_uses_procedures_relationship();

    /**
     * Get all statement-variable Uses relationships.
     * @return Return an unordered_map<int, vector<string>> with statement number as key and variable(s) as value.
     */
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
    /**
     * Get all constants in PKB.
     * @return vector of constants
     */
    vector<string> get_all_constants();

private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
    unordered_set<string> varTable;
    unordered_set<string> procTable;
    unordered_set<string> const_table;
    UsesBank uses_bank;
    ModifiesBank modifies_bank;
    TypeBank type_bank;
    int last_statement_num = 0;
};