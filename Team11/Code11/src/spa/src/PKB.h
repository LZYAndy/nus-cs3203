#pragma once
#ifndef AUTOTESTER_PKB_H
#define AUTOTESTER_PKB_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <numeric>

#include "DesignExtractor.h"
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "ParentBank.h"
#include "ParentStarBank.h"
#include "AssignBank.h"
#include "NextBank.h"
#include "WhileBank.h"
#include "CallsBank.h"
#include "CallsStarBank.h"
#include "IfBank.h"
#include "NextBipBank.h"
#include "AffectsCompute.h"
#include "AffectsStarCompute.h"
#include "NextStarCompute.h"

using namespace std;

class DesignExtractor;
class PKB
{
public:
    // Insert APIs
    /**
     * Insert a procedure into the proc_table.
     * @param name
     * @return Return true if the procedure is inserted successfully, otherwise false.
     */
    bool insert_procedure(string name);

    /**
     * Insert a variable into the var_table.
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
     * Insert Uses relationships of callee procedure to caller procedure
     * @param caller caller procedure
     * @param callee callee procedure
     * @return Return true if the relationships are inserted successfully, otherwise false
     */
    bool insert_uses_for_call(string caller, string callee);

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
     * Insert Modifies relationships of callee procedure to caller procedure
     * @param caller caller procedure
     * @param callee callee procedure
     * @return Return true if the relationships are inserted successfully, otherwise false
     */
    bool insert_modifies_for_call(string caller, string callee);

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
    bool insert_constant(string constant);

    /**
     * Insert Calls relationship into PKB.
     * @param stmt call statement number
     * @param caller caller procedure that Calls
     * @param callee callee procedure that Called
     * @return true if insert is successful.
     */
    bool insert_calls(int stmt, string caller, string callee);
    /**
     * Insert if relationship into PKB.
     * @param stmt stmt# of statement
     * @param control_vars control variables
     * @return true if insert is successful.
     */
    bool insert_if(int stmt, vector<string> control_vars);

    /**
     * Get all variables in the var_table.
     * @return Return a string unordered_set of variables that are contained in the var_table.
     */
    unordered_set<string> get_all_variables();

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
     * Get all procedures in the proc_table.
     * @return Return a string unordered_set of procedures that are contained in the proc_table.
     */
    unordered_set<string> get_all_procedures();

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
    unordered_map<int, vector<int>> get_all_parent_relationship();
    /**
     * Get all Follows relationship that exists in PKB.
     * @return unordered_map containing all Follows relationship that exists in PKB with
     * the Follows as key and all Followed stored in a vector as value.
     */
    unordered_map<int, vector<int>> get_all_follows_relationship();
    /**
     * Get all Parent* relationship that exists in PKB.
     * @return unordered_map containing all Parent* relationship that exists in PKB with
     * the Parent as key and all the descendants stored in a vector as value.
     */
    unordered_map<int, vector<int>> get_all_parent_star_relationship();
    /**
     * Get all Follows* relationship that exists in PKB.
     * @return unordered_map containing all Follows relationship that exists in PKB with
     * the Follows as key and all that directly or indirectly Followed stored in a vector as value.
     */
    unordered_map<int, vector<int>> get_all_follows_star_relationship();

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
    
    /**
     * Get all stmt# of IF statement that control expression contains the variable.
     * @param variable.
     * @return vector of stmt# that IF statements that fulfill the requirements.
     */
    vector<int> get_all_if_pattern_contains(string variable);

    /**
     * Get all if statements and their control variable pairing in PKB.
     * @return unordered_map of stmt# and vector of control variables
     */
    unordered_map<int, vector<string>> get_all_if_and_control_variables_map();

    /**
     * Check if there exist at least one Calls relationship in PKB.
     * @return true if there is at least one Calls relationship in PKB.
     */
    bool does_calls_exist();
    /**
     * Check if the procedure calls another procedure.
     * In other words, Calls(proc1,proc2).
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls
     * @return true if proc1 Calls proc2. In other words, Calls(proc1, proc2).
     */
    bool is_calls(string proc1, string proc2);
    /**
     * Get all procedures that have been Calls.
     * @return vector of procedure name that have been Calls.
     */
    vector<string> get_all_procedures_calls();
    /**
     * Get all procedures that have been Called.
     * @return vector of procedure name that have been Called.
     */
    vector<string> get_all_procedures_called();
    /**
     * Get all procedures that the queried procedure Calls.
     * @param proc queried procedure
     * @return vector of procedure name that the queried procedure Calls.
     */
    vector<string> get_procedures_calls(string proc);
    /**
     * Get all procedures that Called by the queried procedure.
     * @param proc queried procedure
     * @return vector of procedure name that Called by the queried procedure.
     */
    vector<string> get_procedures_called_by(string proc);
    /**
     * Get all Calls relationship that exists in PKB.
     * @return unordered_map containing all Calls relationship that exists in PKB with
     * the Calls as key and all Called stored in a vector as value.
     */
    unordered_map<string, vector<string>> get_all_procedures_calls_relationship();
    /**
     * Get all Calls statements and its callee pairing that exists in PKB.
     * @return unordered_map containing all Calls statements and its callee pairing that exists in PKB. 
     */
    unordered_map<int, vector<string>> get_all_statements_calls_relationship();

    /**
     * Insert Next relationship between statement1 and statement2.
     * @param stmt1
     * @param stmt2
     * @return Return true if the relationship is inserted successfully, otherwise false.
     */
    bool insert_next(int stmt1, int stmt2);

    /**
     * If there is a Next relationship between statement1 and statement2.
     * @param stmt1
     * @param stmt2
     * @return Return true if there is a Next relationship between these two statements, otherwise false.
     */
    bool is_next(int stmt1, int stmt2);

    /**
     * If there exists at least one Next relationship in the program.
     * @return Return true if there exists at least one Next relationship, otherwise false.
     */
    bool does_next_exist();

    /**
     * Get all statements that are the Previous statement of the input statement
     * @param statement
     * @return Return a vector of statements which are the previous statement of the input statement.
     */
    vector<int> get_statements_previous(int statement);

    /**
     * Get all statements that are the Next statement of the input statement
     * @param statement
     * @return Return a vector of statements which are the next statement of the input statement.
     */
    vector<int> get_statements_next(int statement);

    /**
     * Get all statements which are the in previous position in their Next relationships.
     * @return Return all which are the in previous position in their Next relationships.
     */
    vector<int> get_all_previous();

    /**
     * Get all statements which are the in next position in their Next relationships.
     * @return Return all which are the in next position in their Next relationships.
     */
    vector<int> get_all_next();

    /**
     * Insert a while statement into the while_bank.
     * @param statement number of the while statement
     * @param control_var of the while statement
     * @return Return true if the while statement is inserted successfully, otherwise false.
     */
    bool insert_while(int statement, vector<string> control_var);

    /**
     * Insert a statement in the stmtLst of the whileStmt.
     * @param whileStmt
     * @param statement
     * @return Return true if the statement is inserted successfully, otherwise false.
     */
    bool insert_stmt_in_while_stmtLst(int whileStmt, int statement);

    /**
     * Return true if the statement is a while statement.
     * @param statement
     * @return Return true if the statement is a while statement, otherwise false.
     */
    bool is_while(int statement);

    /**
     * Return all statements in the statement list of the input while statement
     * @param statement
     * @return Return all statements in the statement list of the input while statement
     */
    vector<int> get_while_stmtLst(int statement);

    /**
     * Return all while statements using input control_var as control variable
     * @param control_var
     * @return Return all while statements using input control_var as control variable
     */
    vector<int> get_while_with_control_var(string control_var);

    /**
     * Return all pairs of while statement numbers and their corresponding control variables
     * @return Return all pairs of while statement numbers and their corresponding control variables
     */
    unordered_map<int, vector<string>> get_all_whilestmt_and_control_var();

    /**
     * Get all next relationships
     * @return Return all next relationships in the program
     */
    unordered_map<int, vector<int>> get_all_next_relationship();

    /**
     * Get all reversed next relationships
     * @return Return all reversed next relationships in the program
     */
    std::unordered_map<int, std::vector<int>> get_all_previous_relationship();

    /**
     * Check if there exist at least one Calls* relationship in PKB.
     * @return true if there is at least one Calls* relationship in PKB.
     */
    bool does_calls_star_exist();
    /**
     * Check if the procedure calls* another procedure.
     * In other words, Calls*(proc1,proc2).
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls*
     * @return true if proc1 Calls* proc2. In other words, Calls*(proc1, proc2).
     */
    bool is_calls_star(string proc1, string proc2);
    /**
     * Get all procedures that have been Calls directly or indirectly.
     * @return vector of procedure name that have been Calls directly or indirectly.
     */
    vector<string> get_all_procedures_calls_star();
    /**
     * Get all procedures that have been Called directly or indirectly.
     * @return vector of procedure name that have been Called directly or indirectly.
     */
    vector<string> get_all_procedures_called_star();
    /**
     * Get all procedures that the queried procedure Calls directly or indirectly.
     * @param proc queried procedure
     * @return vector of procedure name that the queried procedure Calls directly or indirectly.
     */
    vector<string> get_procedures_calls_star(string proc);
    /**
     * Get all procedures that Called by the queried procedure directly or indirectly.
     * @param proc queried procedure
     * @return vector of procedure name that Called by the queried procedure directly or indirectly.
     */
    vector<string> get_procedures_called_by_star(string proc);
    /**
     * Get all Calls* relationship that exists in CallsStarBank.
     * @return unordered_map containing all Calls* relationship that exists in CallsStarBank with
     * the Calls as key and all Called stored in a vector as value.
     */
    unordered_map<string, vector<string>> get_all_procedures_calls_star_relationship();
    /**
     * Get all statements affecting other statements i.e. get all a in Affects(a, _)
     * @return Return all statements affecting other statements
     */
    vector<int> get_all_assigns_affect();
    /**
     * Get all statements affecting the input statement
     * @param stmt
     * @return Return all statements affecting the input statement
     */
    vector<int> get_assigns_affect(int stmt);
    /**
     * Get all Affects relationships in the program
     * @return Return all Affects relationships in the program
     */
    unordered_map<int, vector<int>> get_all_affects_relationship();
    /**
     * Get all statements affected by other statements i.e. get all a in Affects(_, a)
     * @return Return all statements affected by other statements
     */
    vector<int> get_all_assigns_affected();
    /**
     * Get all statements affected by the input statement
     * @param stmt
     * @return Return all statements affected by the input statement
     */
    vector<int> get_assigns_affected_by(int stmt);
    /**
     * If there exists at least one Affects relationship in the program
     * @return Return true if there is at least one Affects relationship, otherwise false
     */
    bool does_affects_exist();
    /**
     * Check if there is an Affects relationship between statement1 and statement 2
     * @param stmt1
     * @param stmt2
     * @return Return true if there is an Affects relationship between them, otherwise false
     */
    bool is_affects(int stmt1, int stmt2);
    /**
     * Get all statement numbers that are in the previous position
     * in the Next* relationship with the input statement.
     * @param stmt
     * @return a vector of statement numbers that are in the previous position
     * in the Next* relationship with the input statement.
     */
    vector<int> get_statements_previous_star(int stmt);   //e.g. Next*(n, 2)
    /**
     * Get all statement numbers that are in the next position
     * in the Next* relationship with the input statement.
     * @param stmt
     * @return a vector of statement numbers that are in the next position
     * in the Next* relationship with the input statement.
     */
    vector<int> get_statements_next_star(int stmt);  //e.g. Next*(1, n)
    /**
     * Check if stmt1 and stmt2 have a Next* relationship
     * @param stmt1
     * @param stmt2
     * @return return true if they have a Next* relationship
     */
    bool is_next_star(int stmt1, int stmt2); //e.g. Next*(1, 2)
    /**
     * Get all Next* relationship of this program
     * @return an unordered_map containing all Next* relationship in the program with statement number as key and
     * a vector of statement numbers which means they are in the next position in the Next* relationship with the key.
     */
    unordered_map<int, vector<int>> get_all_next_star_relationship();  //e.g. Next*(n1, n2)
    /**
     * Get callee of call statement
     * @param stmt caller statement number
     * @return procedure called.
     */
    string get_called_by_statement(int stmt);
    
    /**
     * Insert NextBip relationship between statement1 and statement2.
     * @param prev_prog
     * @param next_prog
     * @return Return true if the relationship is inserted successfully, otherwise false.
     */
    bool insert_next_bip(int prev_prog, int next_prog);
    /**
     * Insert Ingress & Egress prog line for Call statement
     * @param ingress_prog
     * @param egress_prog
     * @return Return true if the Ingress & Egress is inserted successfully, otherwise false.
     */
    bool insert_call_ingress_egress(int ingress_prog, int egress_prog);
    /**
     * If there is a NextBip relationship between statement1 and statement2.
     * @param prev_prog
     * @param next_prog
     * @return Return true if there is a NextBip relationship between these two statements, otherwise false.
     */
    bool is_next_bip(int prev_prog, int next_prog);
    /**
     * If there exists at least one NextBip relationship in the program.
     * @return Return true if there exists at least one NextBip relationship, otherwise false.
     */
    bool does_next_bip_exists();
    /**
     * Get all statements that are the NextBip statement of the input statement
     * @param prog_line
     * @return Return a vector of statements which are the NextBip statement of the input statement.
     */
    vector<int>  get_next_bip(int prog_line);
    /**
     * Get all statements that are the Previous statement of the input statement
     * @param prog_line
     * @return Return a vector of statements which are the previous statement of the input statement.
     */
    vector<int>  get_previous_bip(int prog_line);
    /**
     * Get all statements which are the in next position in their NextBip relationships.
     * @return Return all which are the in next position in their NextBip relationships.
     */
    vector<int>  get_all_next_bip();
    /**
     * Get all statements which are the in previous position in their NextBip relationships.
     * @return Return all which are the in previous position in their NextBip relationships.
     */
    vector<int>  get_all_previous_bip();
    /**
     * Get all NextBip relationships
     * @return Return all NextBip relationships in the program
     */
    unordered_map<int, vector<int>> get_all_next_bip_relationship();
    /**
    * Check if one assignment statement affects the another assignment directly or indirectly.
    * That is to say Affects(1, 2).
    * @param assignment1 assignment statement to check if affects others
    * @param assignment2 assignment statement that is affected
    * @return true if Affects* relationship holds for the 2 assignment statement.
    */
    bool is_affects_star(int assignment1, int assignment2);
    /**
     * Get all assignment statement that affects the quried assignment statement directly or indirectly.
     * That is to say Affects*(1, a).
     * @param assignment quried assignment statement
     * @return vector containing all the statement numbers of assignment statement affected by quried assignment.
     */
    vector<int> get_affects_star(int assignment);
    /**
     * Get all assignment statement that affected the quried assignment statement directly or indirectly.
     * That is to say Affects*(a, 1).
     * @param assignment quried assignment statement
     * @return vector containing all the statement numbers of assignment statement affects quried assignment.
     */
    vector<int> get_affected_star(int assignment);
    /**
     * Get all Affects* relationship that exists.
     * @return unodered_map that contains all the affects* relationship.
     */
    unordered_map<int, vector<int>> get_all_affects_star_relationship();

private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
    unordered_set<string> var_table;
    unordered_set<string> proc_table;
    unordered_set<string> const_table;
    UsesBank uses_bank;
    ModifiesBank modifies_bank;
    TypeBank type_bank;
    NextBank next_bank;
    WhileBank while_bank;
    CallsBank calls_bank;
    CallsStarBank calls_star_bank;
    IfBank if_bank;
    NextBipBank next_bip_bank;
    AffectsStarCompute affects_star_compute;
    int last_statement_num = 0;
};

#endif