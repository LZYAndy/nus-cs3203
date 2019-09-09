#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

bool PKB::insert_procedure(string name)
{
    procTable.emplace(name);
    return true;
}

bool PKB::insert_variable(string name)
{
    varTable.emplace(name);
    return true;
}

bool PKB::insert_type(int statement, stmtType type)
{
    typeBank.put(statement, type);
    return true;
}

bool PKB::insert_uses(int statement, string variable)
{
    usesBankForStmt.put(statement, variable);
    return true;
}

bool PKB::insert_uses(string procedure, string variable)
{
    usesBankForProc.put(procedure, variable);
    return true;
}

bool PKB::insert_modifies(int statement, string variable)
{
    modifiesBankForStmt.put(statement, variable);
    return true;
}

bool PKB::insert_modifies(string procedure, string variable)
{
    modifiesBankForProc.put(procedure, variable);
    return true;
}

std::unordered_set<std::string> PKB::get_all_variables() {
    return varTable;
}

std::unordered_set<std::string> PKB::get_all_statement_nums() {
    return procTable;
}

vector<int> PKB::get_all_whiles() {
    return vector<int>();
}

vector<int> PKB::get_all_ifs() {
    return vector<int>();
}

vector<int> PKB::get_all_assigns() {
    return vector<int>();
}

vector<int> PKB::get_all_reads() {
    return vector<int>();
}

vector<int> PKB::get_all_prints() {
    return vector<int>();
}

vector<int> PKB::get_all_calls() {
    return vector<int>();
}

std::unordered_set<std::string> PKB::get_all_procedures() {
    return procTable;
}

stmtType PKB::get_statement_type(int statement) {
    return READ;
}

bool PKB::get_statements_modifies(string variable) {
    return false;
}

bool PKB::get_procedures_modifies(string variable) {
    return false;
}

bool PKB::get_modified_by_statement(int statement) {
    return true;
}

bool PKB::get_modified_by_procedure(string procedure) {
    return true;
}

bool PKB::get_statements_uses(string variable) {
    return true;
}

bool PKB::get_procedures_uses(string variable) {
    return true;
}

bool PKB::get_used_by_statement(int statement) {
    return true;
}

bool PKB::get_used_by_procedure(string procedure) {
    return true;
}

bool PKB::is_stmtvar_use(int statement, string variable) {
    return false;
}

bool PKB::is_procvar_use(string procedure, string variable) {
    return false;
}

bool PKB::is_stmtvar_modifies(int statement, string variable) {
    return false;
}

bool PKB::is_procvar_modifies(string procedure, string varible) {
    return false;
}
