#include "PKB.h"

using namespace std;

bool PKB::insert_procedure(string name)
{
    auto result = proc_table.emplace(name);
    return result.second;
}

bool PKB::insert_variable(string name)
{
    auto result =  var_table.emplace(name);
    return result.second;
}

bool PKB::insert_uses(int statement, string variable)
{
    return uses_bank.insert_uses(statement, variable);
}

bool PKB::insert_uses(string procedure, string variable)
{
    return uses_bank.insert_uses(procedure, variable);
}

bool PKB::insert_modifies(int statement, string variable)
{
    return modifies_bank.insert_modifies(statement, variable);
}

bool PKB::insert_modifies(string procedure, string variable)
{
    return modifies_bank.insert_modifies(procedure, variable);
}

unordered_set<string> PKB::get_all_variables()
{
    return var_table;
}

vector<int> PKB::get_all_statement_nums()
{
    if (last_statement_num <= 0)
    {
        return vector<int>();
    }
    vector<int> statement_nums(last_statement_num);
    iota(statement_nums.begin(), statement_nums.end(), 1);
    return statement_nums;
}

unordered_set<string> PKB::get_all_procedures()
{
    return proc_table;
}

vector<int> PKB::get_statements_modifies(string variable)
{
    return modifies_bank.get_statements_modifies(variable);
}

vector<string> PKB::get_procedures_modifies(string variable)
{
    return modifies_bank.get_procedures_modifies(variable);
}

vector<string> PKB::get_modified_by_statement(int statement)
{
    return modifies_bank.get_modified_by_statement(statement);
}

vector<string> PKB::get_modified_by_procedure(string procedure)
{
    return modifies_bank.get_modified_by_procedure(procedure);
}

vector<int> PKB::get_statements_uses(string variable)
{
    return uses_bank.get_statements_uses(variable);
}

vector<string> PKB::get_procedures_uses(string variable)
{
    return uses_bank.get_procedures_uses(variable);
}

vector<string> PKB::get_used_by_statement(int statement)
{
    return uses_bank.get_used_by_statement(statement);
}

vector<string> PKB::get_used_by_procedure(string procedure)
{
    return uses_bank.get_used_by_procedure(procedure);
}

bool PKB::is_uses(int statement, string variable)
{
    return uses_bank.is_uses(statement, variable);
}

bool PKB::is_uses(string procedure, string variable)
{
    return uses_bank.is_uses(procedure, variable);
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
    return follows_bank.insert_follows(stmt1, stmt2);
}

bool PKB::extract_design()
{
    bool result_follows = DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
    bool result_parent = DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank );
    return result_parent && result_follows;
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
    return parent_bank.insert_parent(stmt1, stmt2);
}

vector<int> PKB::get_follows_star(int stmt)
{
    return follows_star_bank.get_follows_star(stmt);
}

vector<int> PKB::get_followed_star_by(int stmt)
{
    return follows_star_bank.get_followed_star_by(stmt);
}

vector<int> PKB::get_parent_star(int stmt)
{
    return parent_star_bank.get_parent_star(stmt);
}

vector<int> PKB::get_children_star(int stmt)
{
    return parent_star_bank.get_children_star(stmt);
}

int PKB::get_follows(int stmt)
{
    return follows_bank.get_follows(stmt);
}

int PKB::get_followed_by(int stmt)
{
    return follows_bank.get_followed_by(stmt);
}

int PKB::get_parent(int stmt)
{
    return parent_bank.get_parent(stmt);
}

vector<int> PKB::get_children(int stmt)
{
    return parent_bank.get_children(stmt);
}

bool PKB::insert_assign(int stmt, string var, string assignment)
{
    return assign_bank.insert_assign(stmt, var, assignment);
}

vector<int> PKB::get_assign_pattern_matches(string var, string pattern)
{
    return assign_bank.matches(var, pattern);
}

vector<int> PKB::get_assign_pattern_contains(string var, string pattern)
{
    return assign_bank.contains(var, pattern);
}

vector<int> PKB::get_all_assign_pattern_matches(string pattern)
{
    return assign_bank.all_matches(pattern);
}

vector<int> PKB::get_all_assign_pattern_contains(string pattern)
{
    return assign_bank.all_contains(pattern);
}

unordered_map<int, vector<int>> PKB::get_all_parent_relationship()
{
    return parent_bank.get_all_parent_relationship();
}

unordered_map<int, vector<int>> PKB::get_all_follows_relationship()
{
    return follows_bank.get_all_follows_relationship();
}

unordered_map<int, vector<int>> PKB::get_all_parent_star_relationship()
{
    return parent_star_bank.get_all_parent_star_relationship();
}

unordered_map<int, vector<int>> PKB::get_all_follows_star_relationship()
{
    return follows_star_bank.get_all_follows_star_relationship();
}

bool PKB::does_follows_exist()
{
    return follows_bank.does_follows_exists();
}

bool PKB::does_follows_star_exist()
{
    return follows_star_bank.does_follows_star_exist();
}

bool PKB::does_parent_exist()
{
    return parent_bank.does_parent_exist();
}

bool PKB::does_parent_star_exist()
{
    return parent_star_bank.does_parent_star_exist();
}

vector<int> PKB::get_all_follows()
{
    return follows_bank.get_all_follows();
}

vector<int> PKB::get_all_followed()
{
    return follows_bank.get_all_followed();
}

vector<int> PKB::get_all_parent()
{
    return parent_bank.get_all_parent();
}

vector<int> PKB::get_all_children()
{
    return parent_bank.get_all_children();
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
    return parent_star_bank.is_parent_star(stmt1, stmt2);
}

EntityType PKB::get_statement_type(int stmt)
{
    return type_bank.get_statement_type(stmt);
}

vector<int> PKB::get_all_follows_star()
{
    return follows_star_bank.get_all_follows_star();
}

vector<int> PKB::get_all_followed_star()
{
    return follows_star_bank.get_all_followed_star();
}

vector<int> PKB::get_all_parent_star()
{
    return parent_star_bank.get_all_parent_star();
}

vector<int> PKB::get_all_children_star()
{
    return parent_star_bank.get_all_children_star();
}

vector<string> PKB::get_all_modifies_procedures()
{
    return modifies_bank.get_all_modifies_procedures();
}

vector<int> PKB::get_all_modifies_statements()
{
    return modifies_bank.get_all_modifies_statements();
}
vector<string> PKB::get_all_uses_procedures()
{
    return uses_bank.get_all_uses_procedures();
}

vector<int> PKB::get_all_uses_statements()
{
    return uses_bank.get_all_uses_statements();
}

unordered_map<string, vector<string>> PKB::get_all_modifies_procedures_relationship()
{
    return modifies_bank.get_all_modifies_procedures_relationship();
}

unordered_map<int, vector<string>> PKB::get_all_modifies_statements_relationship()
{
    return modifies_bank.get_all_modifies_statements_relationship();
}

unordered_map<string, vector<string>> PKB::get_all_uses_procedures_relationship()
{
    return uses_bank.get_all_uses_procedures_relationship();
}

unordered_map<int, vector<string>> PKB::get_all_uses_statements_relationship()
{
    return uses_bank.get_all_uses_statements_relationship();
}

string PKB::assign_to_variable(int assign)
{
    return assign_bank.get_variable_from_statement(assign);
}

vector<string> PKB::assigns_to_variables(vector<int> assigns)
{
    unordered_set<string> temp;
    vector<string> results;
    for (int assign : assigns)
    {
        string result = assign_bank.get_variable_from_statement(assign);
        if (result != "")
        {
            temp.emplace(result);
        }
    }
    results.insert(results.end(), temp.begin(), temp.end());
    return results;
}
bool PKB::insert_type(int stmt, EntityType type)
{
    bool resp = type_bank.insert_type(stmt, type);

    if (last_statement_num < stmt)
    {
        last_statement_num = stmt;
    }
    return resp;
}

vector<int> PKB::get_all_whiles()
{
    return type_bank.get_all_of_type(EntityType::WHILE);
}

vector<int> PKB::get_all_ifs()
{
    return type_bank.get_all_of_type(EntityType::IF);
}

vector<int> PKB::get_all_assigns()
{
    return type_bank.get_all_of_type(EntityType::ASSIGN);
}

vector<int> PKB::get_all_reads()
{
    return type_bank.get_all_of_type(EntityType::READ);
}

vector<int> PKB::get_all_prints()
{
    return type_bank.get_all_of_type(EntityType::PRINT);
}

vector<int> PKB::get_all_calls()
{
    return type_bank.get_all_of_type(EntityType::CALL);
}

bool PKB::does_uses_exist()
{
    return !uses_bank.does_uses_exist();
}

bool PKB::does_modifies_exist()
{
    return !modifies_bank.does_modifies_exist();
}

bool PKB::insert_constant(string constant)
{
    auto result = const_table.emplace(constant);
    return result.second;
}

vector<string> PKB::get_all_constants()
{
    vector<string> result;
    result.insert(result.end(), const_table.begin(), const_table.end());
    return result;
}

bool PKB::insert_next(int stmt1, int stmt2) {
    return next_bank.insert_next(stmt1, stmt2);
}

bool PKB::is_next(int stmt1, int stmt2) {
    return next_bank.is_next(stmt1, stmt2);
}

bool PKB::does_next_exists() {
    return next_bank.does_next_exists();
}

std::vector<int> PKB::get_statements_previous(int statement) {
    return next_bank.get_statements_previous(statement);
}

std::vector<int> PKB::get_statements_next(int statement) {
    return next_bank.get_statements_next(statement);
}

std::vector<int> PKB::get_all_previous() {
    return next_bank.get_all_previous();
}

std::vector<int> PKB::get_all_next() {
    return next_bank.get_all_next();
}

bool PKB::insert_while(int statement, std::string condition) {
    return while_bank.insert_while(statement, condition);
}

bool PKB::is_while(int statement) {
    return while_bank.is_while(statement);
}

std::vector<int> PKB::get_while_stmtLst(int statement) {
    return while_bank.get_while_stmtLst(statement);
}

bool PKB::insert_stmt_in_while_stmtLst(int whileStmt, int statement) {
    return while_bank.insert_stmt_in_while_stmtLst(whileStmt, statement);
}

bool PKB::insert_calls(string proc1, string proc2)
{
    return calls_bank.insert_calls(proc1, proc2);
}

bool PKB::does_calls_exist()
{
    return calls_bank.does_calls_exist();
}

bool PKB::is_calls(string proc1, string proc2)
{
    return calls_bank.is_calls(proc1, proc2);
}

vector<string> PKB::get_all_procedures_calls()
{
    return calls_bank.get_all_procedures_calls();
}

vector<string> PKB::get_all_procedures_called()
{
    return calls_bank.get_all_procedures_called();
}

vector<string> PKB::get_procedures_calls(string proc)
{
    return calls_bank.get_procedures_calls(proc);
}

vector<string> PKB::get_procedures_called_by(string proc)
{
    return calls_bank.get_procedures_called_by(proc);
}

unordered_map<string, vector<string>> PKB::get_all_procedures_calls_relationship()
{
    return calls_bank.get_all_procedures_calls_relationship();
}

bool PKB::insert_if(int stmt, vector<string> control_vars)
{
    return if_bank.insert_if(stmt, control_vars);
}

vector<int> PKB::get_all_if_pattern_contains(string variable)
{
    return if_bank.all_contains(variable);
}

unordered_map<int, vector<string>> PKB::get_all_if_and_control_variables_map()
{
    return if_bank.get_all_if_and_control_variables_map();
}

std::unordered_map<int, std::vector<int>> PKB::get_all_next_relationship() {
    return next_bank.get_all_next_relationship();
}
