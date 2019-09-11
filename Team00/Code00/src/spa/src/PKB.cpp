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

bool PKB::insert_uses(int statement, string variable)
{
    uses_bank.insert_uses(statement, variable);
    return true;
}

bool PKB::insert_uses(string procedure, string variable)
{
    uses_bank.insert_uses(procedure, variable);
    return true;
}

bool PKB::insert_modifies(int statement, string variable)
{
    modifies_bank.insert_modifies(statement, variable);
    return true;
}

bool PKB::insert_modifies(string procedure, string variable)
{
    modifies_bank.insert_modifies(procedure, variable);
    return true;
}

std::unordered_set<std::string> PKB::get_all_variables() {
    return varTable;
}

std::unordered_set<std::string> PKB::get_all_statement_nums() {
    return procTable;
}

std::unordered_set<std::string> PKB::get_all_procedures() {
    return procTable;
}

vector<int> PKB::get_statements_modifies(string variable) {
    return modifies_bank.get_statements_modifies(variable);
}

vector<string> PKB::get_procedures_modifies(string variable) {
    return modifies_bank.get_procedures_modifies(variable);
}

vector<string> PKB::get_modified_by_statement(int statement) {
    return modifies_bank.get_modified_by_statement(statement);
}

vector<string> PKB::get_modified_by_procedure(string procedure) {
    return modifies_bank.get_modified_by_procedure(procedure);
}

vector<int> PKB::get_statements_uses(string variable) {
    return uses_bank.get_statements_uses(variable);
}

vector<string> PKB::get_procedures_uses(string variable) {
    return uses_bank.get_procedures_uses(variable);
}

vector<string> PKB::get_used_by_statement(int statement) {
    return uses_bank.get_used_by_statement(statement);
}

vector<string> PKB::get_used_by_procedure(string procedure) {
    return uses_bank.get_used_by_procedure(procedure);
}

bool PKB::is_uses(int statement, string variable)
{
    uses_bank.is_uses(statement, variable);
}

bool PKB::is_uses(string procedure, string variable)
{
    uses_bank.is_uses(procedure, variable);
}

bool PKB::is_modifies(int statement, string variable)
{
    return modifies_bank.is_modifies(statement, variable);
}

bool PKB::is_modifies(string procedure, string variable)
{
    return modifies_bank.is_modifies(procedure, variable);
}

bool PKB::insert_follows(int stmt1, int stmt2)
{
    if (stmt1 == stmt2)
    {
        return false;
    }
    if (stmt1 > stmt2)
    {
        return false;
    }
    follows_bank.put(stmt1, stmt2);
    return true;
}

bool PKB::extract_design()
{
    DesignExtractor::extract_follows_star(&follows_bank, &follows_star_bank);
    DesignExtractor::extract_parent_star(&parent_bank, &parent_star_bank);
    return true;
}

bool PKB::insert_parent(int stmt1, int stmt2)
{
    if (stmt1 == stmt2)
    {
        return false;
    }
    if (stmt1 > stmt2)
    {
        return false;
    }
    parent_bank.put(stmt1, stmt2);
    return true;
}

std::vector<int> PKB::get_follows_star(int stmt)
{
    return follows_star_bank.get(stmt);;
}

std::vector<int> PKB::get_followed_star_by(int stmt)
{
    return follows_star_bank.get_reverse(stmt);
}

std::vector<int> PKB::get_parent_star(int stmt)
{
    return parent_star_bank.get(stmt);
}

std::vector<int> PKB::get_children_star(int stmt)
{
    return parent_star_bank.get_reverse(stmt);
}

int PKB::get_follows(int stmt)
{
    std::vector<int> result = follows_bank.get(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

int PKB::get_followed_by(int stmt)
{
    std::vector<int> result = follows_bank.get_reverse(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

int PKB::get_parent(int stmt)
{
    std::vector<int> result = parent_bank.get(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

std::vector<int> PKB::get_children(int stmt)
{
    return parent_bank.get_reverse(stmt);
}

bool PKB::insert_assign(int stmt, string var, string assignment)
{
    assign_bank.put(stmt, var, assignment);
    return true;
}

vector<int> PKB::get_pattern_matches(string var, string pattern)
{
    return assign_bank.matches(var, pattern);
}

vector<int> PKB::get_pattern_contains(string var, string pattern)
{
    return assign_bank.contains(var, pattern);
}

vector<int> PKB::get_all_pattern_matches(string pattern)
{
    return assign_bank.all_matches(pattern);
}

vector<int> PKB::get_all_pattern_contains(string pattern)
{
    return assign_bank.all_contains(pattern);
}

unordered_map<int, std::vector<int>> PKB::get_all_parent_relationship()
{
    return parent_bank.copy();
}

unordered_map<int, std::vector<int>> PKB::get_all_follows_relationship()
{
    return follows_bank.copy();
}

unordered_map<int, std::vector<int>> PKB::get_all_parent_star_relationship()
{
    return parent_star_bank.copy();
}

unordered_map<int, std::vector<int>> PKB::get_all_follows_star_relationship()
{
    return follows_star_bank.copy();
}

bool PKB::does_follows_exist()
{
    return follows_bank.empty();
}

bool PKB::does_follows_star_exist()
{
    return follows_star_bank.empty();
}

bool PKB::does_parent_exist()
{
    return parent_bank.empty();
}

bool PKB::does_parent_star_exist()
{
    return parent_star_bank.empty();
}

vector<int> PKB::get_all_follows()
{
    return follows_bank.get_all_keys();
}

vector<int> PKB::get_all_followed()
{
    return follows_bank.get_all_values();
}

vector<int> PKB::get_all_parent()
{
    return parent_bank.get_all_keys();
}

vector<int> PKB::get_all_children()
{
    return parent_bank.get_all_values();
}

bool PKB::is_follows(int stmt1, int stmt2)
{
    return follows_bank.is_follows(stmt1, stmt2);
}
bool PKB::is_parent(int stmt1, int stmt2)
{
    return parent_bank.is_parent(stmt1, stmt2);
}
bool PKB::is_follows_star(int stmt1, int stmt2)
{
    return follows_star_bank.is_follows_star(stmt1, stmt2);
}
bool PKB::is_parent_star(int stmt1, int stmt2)
{
    return parent_star_bank.is_parents_star(stmt1, stmt2);
}

vector<int> PKB::get_all_follows_star()
{
    return follows_star_bank.get_all_keys();
}

vector<int> PKB::get_all_followed_star()
{
    return follows_star_bank.get_all_values();
}

vector<int> PKB::get_all_parent_star()
{
    return parent_star_bank.get_all_keys();
}

vector<int> PKB::get_all_children_star()
{
    return parent_star_bank.get_all_values();
}


