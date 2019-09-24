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
    bool insert_follows(int stmt1, int stmt2);
    bool insert_parent(int stmt1, int stmt2);
    bool insert_assign(int stmt, string var, string assignment);
    bool insert_type(int stmt, EntityType type);
    /**
     * Insert constant into PKB.
     * @param constant
     * @return true if insert is successful.
     */
    bool insert_constant(int constant);
    bool extract_design();

    /**
     * Get all variables in the varTable.
     * @return Return a string unordered_set of variables that are contained in the varTable.
     */
    unordered_set<std::string> get_all_variables();
    vector<int> get_all_statement_nums();
    vector<int> get_all_whiles();
    vector<int> get_all_ifs();
    vector<int> get_all_assigns();
    vector<int> get_all_reads();
    vector<int> get_all_prints();
    vector<int> get_all_calls();

    /**
     * Get all procedures in the procTable.
     * @return Return a string unordered_set of procedures that are contained in the procTable.
     */
    unordered_set<std::string> get_all_procedures();

    EntityType get_statement_type(int stmt);
    vector<int> get_follows_star(int stmt);
    vector<int> get_followed_star_by(int stmt);
    int get_follows(int stmt);
    int get_followed_by(int stmt);
    int get_parent(int stmt);
    vector<int> get_children(int stmt);
    vector<int> get_parent_star(int stmt);
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

    vector<int> get_assign_pattern_matches(string var, string pattern);
    vector<int> get_assign_pattern_contains(string var, string pattern);
    vector<int> get_all_assign_pattern_matches(string pattern);
    vector<int> get_all_assign_pattern_contains(string pattern);

    bool is_follows(int stmt1, int stmt2);
    bool is_parent(int stmt1, int stmt2);
    bool is_follows_star(int stmt1, int stmt2);
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

    bool does_follows_exist();
    bool does_follows_star_exist();
    bool does_parent_exist();
    bool does_parent_star_exist();

    vector<int> get_all_follows();
    vector<int> get_all_followed();
    vector<int> get_all_parent();
    vector<int> get_all_children();

    unordered_map<int, std::vector<int>> get_all_parent_relationship();
    unordered_map<int, std::vector<int>> get_all_follows_relationship();
    unordered_map<int, std::vector<int>> get_all_parent_star_relationship();
    unordered_map<int, std::vector<int>> get_all_follows_star_relationship();

    vector<int> get_all_parent_star();
    vector<int> get_all_follows_star();
    vector<int> get_all_children_star();
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

    string assign_to_variable(int assign);
    vector<string> assigns_to_variables(vector<int> assigns);
    /**
     * Get all constants in PKB.
     * @return vector of constants
     */
    vector<int> get_all_constants();

private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
    unordered_set<string> varTable;
    unordered_set<string> procTable;
    unordered_set<int> const_table;
    UsesBank uses_bank;
    ModifiesBank modifies_bank;
    TypeBank type_bank;
    int last_statement_num = 0;
};