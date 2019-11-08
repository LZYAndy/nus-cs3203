#include "PKB.h"

using namespace std;
PKB::PKB()
{
    next_bip_star_compute = NextBipStarCompute(&next_bip_bank, &type_bank, &next_bank);
    affects_bip_compute = AffectsBipCompute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank, &next_bank);
    affects_bip_star_compute = AffectsBipStarCompute(&affects_bip_compute, &type_bank);
}

bool PKB::insert_procedure(string name, int first_prog, vector<int> last_progs)
{
    return proc_bank.insert_procedure(name, first_prog, last_progs);
}

bool PKB::insert_variable(string name)
{
    auto result = var_table.emplace(name);
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
    unordered_set<string> result;
    for(string procedure : proc_bank.get_all_procedures())
    {
        result.insert(procedure);
    }
    return result;
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
    DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
    DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
    bool result_calls = DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank);
    if (!result_calls)
    {
        return false;
    }
    DesignExtractor::extract_next_bip(*this);
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

bool PKB::insert_next(int stmt1, int stmt2)
{
    return next_bank.insert_next(stmt1, stmt2);
}

bool PKB::is_next(int stmt1, int stmt2)
{
    return next_bank.is_next(stmt1, stmt2);
}

bool PKB::does_next_exist()
{
    return next_bank.does_next_exist();
}

vector<int> PKB::get_statements_previous(int statement)
{
    return next_bank.get_statements_previous(statement);
}

vector<int> PKB::get_statements_next(int statement)
{
    return next_bank.get_statements_next(statement);
}

vector<int> PKB::get_all_previous()
{
    return next_bank.get_all_previous();
}

vector<int> PKB::get_all_next()
{
    return next_bank.get_all_next();
}

bool PKB::insert_while(int statement, vector<string> control_var)
{
    return while_bank.insert_while(statement, control_var);
}

bool PKB::is_while(int statement)
{
    return while_bank.is_while(statement);
}

vector<int> PKB::get_while_stmtLst(int statement)
{
    return while_bank.get_while_stmtLst(statement);
}

bool PKB::insert_stmt_in_while_stmtLst(int whileStmt, int statement)
{
    return while_bank.insert_stmt_in_while_stmtLst(whileStmt, statement);
}

bool PKB::insert_calls(int stmt, string caller, string callee)
{
    return calls_bank.insert_calls(stmt, caller, callee);
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

unordered_map<int, vector<int>> PKB::get_all_next_relationship()
{
    return next_bank.get_all_next_relationship();
}

vector<int> PKB::get_while_with_control_var(string control_var)
{
    return while_bank.get_while_with_control_var(control_var);
}

unordered_map<int, vector<string>> PKB::get_all_whilestmt_and_control_var()
{
    return while_bank.get_all_whilestmt_and_control_var();
}

bool PKB::does_calls_star_exist()
{
    return calls_star_bank.does_calls_star_exist();
}

bool PKB::is_calls_star(string proc1, string proc2)
{
    return calls_star_bank.is_calls_star(proc1, proc2);
}

vector<string> PKB::get_all_procedures_calls_star()
{
    return calls_star_bank.get_all_procedures_calls_star();
}

vector<string> PKB::get_all_procedures_called_star()
{
    return calls_star_bank.get_all_procedures_called_star();
}

vector<string> PKB::get_procedures_calls_star(string proc)
{
    return calls_star_bank.get_procedures_calls_star(proc);
}

vector<string> PKB::get_procedures_called_by_star(string proc)
{
    return calls_star_bank.get_procedures_called_by_star(proc);
}

unordered_map<string, vector<string>> PKB::get_all_procedures_calls_star_relationship()
{
    return calls_star_bank.get_all_procedures_calls_star_relationship();
}

bool PKB::insert_uses_for_call(string caller, string callee)
{
    return uses_bank.insert_uses_for_call(caller, callee);
}

bool PKB::insert_modifies_for_call(string caller, string callee)
{
    return modifies_bank.insert_modifies_for_call(caller, callee);
}

unordered_map<int, vector<string>> PKB::get_all_statements_calls_relationship()
{
    return calls_bank.get_all_statements_calls_relationship();
}

vector<int> PKB::get_all_assigns_affect()
{
    return affects_compute.get_all_assigns_affect(last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

vector<int> PKB::get_assigns_affect(int stmt)
{
    return affects_compute.get_assigns_affect(stmt, last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

unordered_map<int, vector<int>> PKB::get_all_affects_relationship()
{
    return affects_compute.get_all_affects_relationship(last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

vector<int> PKB::get_all_assigns_affected()
{
    return affects_compute.get_all_assigns_affected(last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

vector<int> PKB::get_assigns_affected_by(int stmt)
{
    return affects_compute.get_assigns_affected_by(stmt, last_statement_num, next_bank, modifies_bank, uses_bank, type_bank, false);
}

bool PKB::does_affects_exist()
{
    return affects_compute.does_affects_exist(last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

bool PKB::is_affects(int stmt1, int stmt2)
{
    return affects_compute.is_affects(stmt1, stmt2, last_statement_num, next_bank, modifies_bank, uses_bank, type_bank);
}

vector<int> PKB::get_statements_previous_star(int stmt)
{
    return next_star_compute.get_statements_previous_star(stmt, last_statement_num, next_bank);
}

vector<int> PKB::get_statements_next_star(int stmt)
{
    return next_star_compute.get_statements_next_star(stmt, last_statement_num, next_bank);
}

bool PKB::is_next_star(int stmt1, int stmt2)
{
    return next_star_compute.is_next_star(stmt1, stmt2, last_statement_num, next_bank);
}

unordered_map<int, vector<int>> PKB::get_all_next_star_relationship()
{
    return next_star_compute.get_all_next_star_relationship(last_statement_num, next_bank);
}

unordered_map<int, vector<int>> PKB::get_all_previous_relationship()
{
    return next_bank.get_all_previous_relationship();
}

string PKB::get_called_by_statement(int stmt)
{
    return calls_bank.get_called_by_statement(stmt);
}

bool PKB::insert_next_bip(int prev_prog, int next_prog)
{
    return next_bip_bank.insert_next_bip(prev_prog, next_prog);
}

bool PKB::is_next_bip(int prev_prog, int next_prog)
{
    return next_bip_bank.is_next_bip(prev_prog, next_prog);
}

bool PKB::insert_call_ingress_egress(int ingress_prog, int egress_prog)
{
    return next_bip_bank.insert_call_ingress_egress(ingress_prog, egress_prog);
}

bool PKB::does_next_bip_exists()
{
    return next_bip_bank.does_next_bip_exists();
}

vector<int> PKB::get_next_bip(int prog_line)
{
    return next_bip_bank.get_next_bip(prog_line);
}

vector<int> PKB::get_previous_bip(int prog_line)
{
    return next_bip_bank.get_previous_bip(prog_line);
}

vector<int> PKB::get_all_next_bip()
{
    return next_bip_bank.get_all_next_bip();
}

vector<int> PKB::get_all_previous_bip()
{
    return next_bip_bank.get_all_previous_bip();
}

unordered_map<int, vector<int>> PKB::get_all_next_bip_relationship()
{
    return next_bip_bank.get_all_next_bip_relationship();
}
bool PKB::is_affects_star(int assignment1, int assignment2)
{
    return affects_star_compute.is_affects_star(*this, assignment1, assignment2, false);
}

vector<int> PKB::get_affected_star(int assignment)
{
    return affects_star_compute.get_affected_star(*this, assignment, false);
}

vector<int> PKB::get_affects_star(int assignment)
{
    return affects_star_compute.get_affects_star(*this, assignment);
}

unordered_map<int, vector<int>> PKB::get_all_affects_star_relationship()
{
    return affects_star_compute.get_all_affects_star_relationship(*this);
}

void PKB::clear_cache() {
    affects_compute.clear_cache();
    next_star_compute.clear_cache();
    affects_star_compute.clear_cache();
}
bool PKB::is_next_bip_star(int previous, int next)
{
    return next_bip_star_compute.is_next_bip_star(previous, next);
}

vector<int> PKB::get_next_bip_star(int previous)
{
    return next_bip_star_compute.get_next_bip_star(previous);
}

vector<int> PKB::get_previous_bip_star(int next)
{
    return next_bip_star_compute.get_previous_bip_star(next);
}

unordered_map<int, vector<int>> PKB::get_all_next_bip_star_relationship()
{
    return next_bip_star_compute.get_all_next_bip_star_relationship();
}

bool PKB::does_affects_bip_exist()
{
    return affects_bip_compute.does_affects_bip_exist();
}

bool PKB::is_affects_bip(int stmt1, int stmt2)
{
    return affects_bip_compute.is_affects_bip(stmt1, stmt2);
}

vector<int> PKB::get_assigns_affects_bip(int stmt)
{
    return affects_bip_compute.get_assigns_affects_bip(stmt);
}
vector<int> PKB::get_assigns_affected_bip_by(int stmt)
{
    return affects_bip_compute.get_assigns_affected_bip_by(stmt, false);
}

vector<int> PKB::get_all_assigns_affects_bip()
{
    return affects_bip_compute.get_all_assigns_affects_bip();
}

vector<int> PKB::get_all_assigns_affected_bip()
{
    return affects_bip_compute.get_all_assigns_affected_bip();
}

unordered_map<int, vector<int>> PKB::get_all_affects_bip_relationship()
{
    return affects_bip_compute.get_all_affects_bip_relationship();
}

bool PKB::is_affects_bip_star(int assignment1, int assignment2)
{
    return affects_bip_star_compute.is_affects_bip_star(assignment1, assignment2);
}

vector<int> PKB::get_affects_bip_star(int assignment)
{
    return affects_bip_star_compute.get_affects_bip_star(assignment);
}

vector<int> PKB::get_affected_bip_star(int assignment)
{
    return affects_bip_star_compute.get_affected_bip_star(assignment);
}

unordered_map<int, vector<int>> PKB::get_all_affects_bip_star_relationship()
{
    return affects_bip_star_compute.get_all_affects_bip_star_relationship();
}

int PKB::get_procedure_first_line(string procedure)
{
    return proc_bank.get_procedure_first_line(procedure);
}

vector<int> PKB::get_procedure_last_lines(string procedure)
{
    return proc_bank.get_procedure_last_lines(procedure);
}
