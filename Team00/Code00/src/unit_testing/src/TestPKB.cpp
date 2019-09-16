#include "catch.hpp"
#include "PKB.h"

TEST_CASE("PKB::get_all_variables()")
{
    PKB pkb;
    unordered_set<string> varTable;

    SECTION("0 variable")
    {
        varTable = pkb.get_all_variables();
        REQUIRE(varTable.size() == 0);
    }

    pkb.insert_variable("x");
    pkb.insert_variable("y");
    pkb.insert_variable("y");

    SECTION("more than 0 variable")
    {
        varTable = pkb.get_all_variables();
        REQUIRE(varTable.size() == 2);
        REQUIRE(varTable.count("x") == 1);
        REQUIRE(varTable.count("y") == 1);
    }
}

TEST_CASE("PKB::get_all_procedures()")
{
    PKB pkb;
    unordered_set<std::string> procTable;

    SECTION("0 procedure")
    {
        procTable = pkb.get_all_procedures();
        REQUIRE(procTable.size() == 0);
    }

    pkb.insert_procedure("main");
    pkb.insert_procedure("procX");
    pkb.insert_procedure("procX");

    SECTION("more than 0 procedure")
    {
        procTable = pkb.get_all_procedures();
        REQUIRE(procTable.size() == 2);
        REQUIRE(procTable.count("main") == 1);
        REQUIRE(procTable.count("procX") == 1);
    }
}

EntityType get_statement_type(int stmt);

vector<int> get_statements_uses(string variable);
vector<string> get_procedures_uses(string variable);
vector<string> get_used_by_statement(int statement);
vector<string> get_used_by_procedure(string procedure);

vector<int> get_statements_modifies(string variable);
vector<string> get_procedures_modifies(string variable);
vector<string> get_modified_by_statement(int statement);
vector<string> get_modified_by_procedure(string procedure);

bool is_uses(int statement, string variable);
bool is_uses(string procedure, string variable);
bool is_modifies(int statement, string variable);
bool is_modifies(string procedure, string variable);

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
