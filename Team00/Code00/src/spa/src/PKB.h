#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"

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

    bool get_statements_modifies(string variable);
    bool get_procedures_modifies(string variable);
    bool get_modified_by_statement(int statement);
    bool get_modified_by_procedure(string procedure);

    bool get_statements_uses(string variable);
    bool get_procedures_uses(string variable);
    bool get_used_by_statement(int statement);
    bool get_used_by_procedure(string procedure);

    bool is_stmtvar_use(int statement, string variable);
    bool is_procvar_use(string procedure, string variable);
    bool is_stmtvar_modifies(int statement, string variable);
    bool is_procvar_modifies(string procedure, string varible);

private:
    static std::unordered_set<std::string> varTable;
    static std::unordered_set<std::string> procTable;
    static UsesBank<int, string> usesBankForStmt;
    static UsesBank<string, vector<string>> usesBankForProc;
    static ModifiesBank<int, vector<string>> modifiesBankForStmt;
    static ModifiesBank<string, vector<string>> modifiesBankForProc;
    static TypeBank<int, stmtType> typeBank;
};