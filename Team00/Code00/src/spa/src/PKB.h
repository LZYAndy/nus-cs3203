#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
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
typedef short PROC;

class PKB {
public:
	bool insert_procedure(string name);
	bool insert_variable(string name);
	bool insert_type(int statement, stmtType type);
	bool insert_uses(int statement, string variable);
	bool insert_uses(string procedure, string variable);
    bool insert_modifies(int statement, string variable);
    bool insert_modifies(string procedure, string variable);

    std::unordered_set<std::string> get_all_variables();
    std::unordered_set<std::string> get_all_statement_nums();
    vector<int> get_all_whiles();
    vector<int> get_all_ifs();
    vector<int> get_all_assigns();
    vector<int> get_all_reads();
    vector<int> get_all_prints();
    vector<int> get_all_calls();
    std::unordered_set<std::string> get_all_procedures();
    stmtType get_statement_type(int statement);

    vector<int> get_statements_modifies(string variable);
    vector<string> get_procedures_modifies(string variable);
    vector<string> get_modified_by_statement(int statement);
    vector<string> get_modified_by_procedure(string procedure);

    vector<int> get_statements_uses(string variable);
    vector<string> get_procedures_uses(string variable);
    vector<string> get_used_by_statement(int statement);
    vector<string> get_used_by_procedure(string procedure);

    bool is_stmtvar_use(int statement, string variable);
    bool is_procvar_use(string procedure, string variable);
    bool is_stmtvar_modifies(int statement, string variable);
    bool is_procvar_modifies(string procedure, string variable);

	bool extract_design();
	bool insert_follows(int stmt1, int stmt2);
    bool insert_parent(int stmt1, int stmt2);
    bool insert_assign(int stmt, string var, string assignment);

    vector<int> get_follows_star(int stmt);
    vector<int> get_followed_star_by(int stmt);
    int get_follows(int stmt);
    int get_followed_by(int stmt);
    int get_parent(int stmt);
    vector<int> get_children(int stmt);
    vector<int> get_parent_star(int stmt);
    vector<int> get_children_star(int stmt);
    vector<int> get_pattern_matches(string var, string pattern);
    vector<int> get_pattern_contains(string var, string pattern);
    vector<int> get_all_pattern_matches(string pattern);
    vector<int> get_all_pattern_contains(string pattern);
    vector<int> get_all_follows();
    vector<int> get_all_followed();
    vector<int> get_all_parent();
    vector<int> get_all_children();
    unordered_map<int, std::vector<int>> get_all_parent_relationship();
    unordered_map<int, std::vector<int>> get_all_follows_relationship();
    unordered_map<int, std::vector<int>> get_all_parent_star_relationship();
    unordered_map<int, std::vector<int>> get_all_follows_star_relationship();
    bool does_follows_exist();
    bool does_follows_star_exist();
    bool does_parent_exist();
    bool does_parent_star_exist();
    bool is_follows(int stmt1, int stmt2);
    bool is_parent(int stmt1, int stmt2);
    bool is_follows_star(int stmt1, int stmt2);
    bool is_parent_star(int stmt1, int stmt2);

private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
    std::unordered_set<string> varTable;
    std::unordered_set<string> procTable;
    UsesBank<int, string> usesBankForStmt;
    UsesBank<string, string> usesBankForProc;
    ModifiesBank<int, string> modifiesBankForStmt;
    ModifiesBank<string, string> modifiesBankForProc;
    TypeBank<int, stmtType> typeBank;
};