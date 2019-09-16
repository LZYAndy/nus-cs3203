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

TEST_CASE("PKB::get_statements_uses()")
{
    PKB pkb;
    pkb.insert_uses(1, "a");
    pkb.insert_uses(2, "b");
    pkb.insert_uses(7, "a");
    pkb.insert_uses(7, "d");
    pkb.insert_uses(9, "c");

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_uses("nya");
        REQUIRE(result.empty());

        result = pkb.get_statements_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);

        result = pkb.get_statements_uses("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);

        result = pkb.get_statements_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_uses("a");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_procedures_uses()")
{
    PKB pkb;
    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_procedures_uses("nya");
        REQUIRE(result.empty());

        result = pkb.get_procedures_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 procedure")
    {
        result = pkb.get_procedures_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);

        result = pkb.get_procedures_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_procedures_uses("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("PKB::get_used_by_statement()")
{
    PKB pkb;
    pkb.insert_uses(1, "a");
    pkb.insert_uses(2, "b");
    pkb.insert_uses(5, "a");
    pkb.insert_uses(5, "d");
    pkb.insert_uses(100, "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_used_by_statement(3);
        REQUIRE(result.empty());

        result = pkb.get_used_by_statement(233);
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_used_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);

        result = pkb.get_used_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_used_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_used_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("PKB::get_used_by_procedure()")
{
    PKB pkb;
    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_used_by_procedure("nya");
        REQUIRE(result.empty());

        result = pkb.get_used_by_procedure("procx");
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_used_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_used_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_used_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("PKB::is_uses() for stmt")
{
    PKB pkb;
    pkb.insert_uses(1,"a");
    pkb.insert_uses(2,"a");

    SECTION("return true")
    {
        REQUIRE(pkb.is_uses(1, "a"));
        REQUIRE(pkb.is_uses(2, "a"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_uses(3, "a"));
        REQUIRE_FALSE(pkb.is_uses(2, "b"));
    }
}

TEST_CASE("PKB::is_uses() for proc")
{
    PKB pkb;
    pkb.insert_uses("main","a");
    pkb.insert_uses("main","b");

    SECTION("return true")
    {
        REQUIRE(pkb.is_uses("main", "a"));
        REQUIRE(pkb.is_uses("main", "b"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_uses("proc", "a"));
        REQUIRE_FALSE(pkb.is_uses("main", "B"));
    }
}

TEST_CASE("PKB::get_all_uses_procedures()")
{
    PKB pkb;

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.empty());
    }

    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");

    SECTION("return 1 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }

    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.size() == 3);
        std::vector<std::string> expected;
        expected.push_back("main");
        expected.push_back("procX");
        expected.push_back("procY");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_uses_statements()")
{
    PKB pkb;

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.empty());
    }

    pkb.insert_uses(1, "a");
    pkb.insert_uses(1, "b");

    SECTION("return 1 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    pkb.insert_uses(5, "a");
    pkb.insert_uses(6, "c");

    SECTION("return more than 1 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_uses_statements_relationship()")
{
    PKB pkb;

    std::unordered_map<int, std::vector<std::string>> result;
    std::unordered_map<int, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_uses_statements_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_uses(1, "a");
    pkb.insert_uses(1, "b");
    pkb.insert_uses(5, "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5,value2);
        result = pkb.get_all_uses_statements_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_uses_procedures_relationship()")
{
    PKB pkb;

    std::unordered_map<std::string, std::vector<std::string>> result;
    std::unordered_map<std::string, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_uses_procedures_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX",value2);
        result = pkb.get_all_uses_procedures_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}
TEST_CASE("PKB::get_statements_modifies()")
{
    PKB pkb;
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(2, "b");
    pkb.insert_modifies(7, "a");
    pkb.insert_modifies(7, "d");
    pkb.insert_modifies(9, "c");

    std::vector<int> result;
    
    SECTION("return 0 statement")
    {
        result = pkb.get_statements_modifies("nya");
        REQUIRE(result.empty());
        
        result = pkb.get_statements_modifies("A");
        REQUIRE(result.empty());
    }
    
    SECTION("return 1 statement")
    {
        result = pkb.get_statements_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
        
        result = pkb.get_statements_modifies("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);
        
        result = pkb.get_statements_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }
    
    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_modifies("a");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_procedures_modifies()")
{
    PKB pkb;
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");
    
    std::vector<std::string> result;
    
    SECTION("return 0 procedure")
    {
        result = pkb.get_procedures_modifies("nya");
        REQUIRE(result.empty());
        
        result = pkb.get_procedures_modifies("A");
        REQUIRE(result.empty());
    }
    
    SECTION("return 1 procedure")
    {
        result = pkb.get_procedures_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
        
        result = pkb.get_procedures_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }
    
    SECTION("return more than 1 procedure")
    {
        result = pkb.get_procedures_modifies("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("PKB::get_modified_by_statement()")
{
    PKB pkb;
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(2, "b");
    pkb.insert_modifies(5, "a");
    pkb.insert_modifies(5, "d");
    pkb.insert_modifies(100, "c");
    
    std::vector<std::string> result;
    
    SECTION("return 0 variable")
    {
        result = pkb.get_modified_by_statement(3);
        REQUIRE(result.empty());
        
        result = pkb.get_modified_by_statement(233);
        REQUIRE(result.empty());
    }
    
    SECTION("return 1 variable")
    {
        result = pkb.get_modified_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);
        
        result = pkb.get_modified_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);
        
        result = pkb.get_modified_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }
    
    SECTION("return more than 1 variable")
    {
        result = pkb.get_modified_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("PKB::get_modified_by_procedure()")
{
    PKB pkb;
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");
    
    std::vector<std::string> result;
    
    SECTION("return 0 variable")
    {
        result = pkb.get_modified_by_procedure("nya");
        REQUIRE(result.empty());
        
        result = pkb.get_modified_by_procedure("procx");
        REQUIRE(result.empty());
    }
    
    SECTION("return 1 variable")
    {
        result = pkb.get_modified_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);
        
        result = pkb.get_modified_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }
    
    SECTION("return more than 1 variable")
    {
        result = pkb.get_modified_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("PKB::is_modifies() for stmt")
{
    PKB pkb;
    pkb.insert_modifies(1,"a");
    pkb.insert_modifies(2,"a");
    
    SECTION("return true")
    {
        REQUIRE(pkb.is_modifies(1, "a"));
        REQUIRE(pkb.is_modifies(2, "a"));
    }
    
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_modifies(3, "a"));
        REQUIRE_FALSE(pkb.is_modifies(2, "b"));
    }
    }
    
TEST_CASE("PKB::is_modifies() for proc")
{
    PKB pkb;
    pkb.insert_modifies("main","a");
    pkb.insert_modifies("main","b");
    
    SECTION("return true")
    {
        REQUIRE(pkb.is_modifies("main", "a"));
        REQUIRE(pkb.is_modifies("main", "b"));
    }
    
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_modifies("proc", "a"));
        REQUIRE_FALSE(pkb.is_modifies("main", "B"));
    }
}

TEST_CASE("PKB::get_all_modifies_procedures()")
{
    PKB pkb;
    
    std::vector<std::string> result;
    
    SECTION("return 0 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.empty());
    }
    
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    
    SECTION("return 1 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }
    
    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");
    
    SECTION("return more than 1 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.size() == 3);
        std::vector<std::string> expected;
        expected.push_back("main");
        expected.push_back("procX");
        expected.push_back("procY");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_modifies_statements()")
{
    PKB pkb;
    
    std::vector<int> result;
    
    SECTION("return 0 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.empty());
    }
    
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(1, "b");
    
    SECTION("return 1 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }
    
    pkb.insert_modifies(5, "a");
    pkb.insert_modifies(6, "c");
    
    SECTION("return more than 1 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_modifies_statements_relationship()")
{
    PKB pkb;
    
    std::unordered_map<int, std::vector<std::string>> result;
    std::unordered_map<int, std::vector<std::string>> expected;
    
    SECTION("bank without element")
    {
        result = pkb.get_all_modifies_statements_relationship();
        REQUIRE(result.empty());
    }
    
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(1, "b");
    pkb.insert_modifies(5, "b");
    
    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5,value2);
        result = pkb.get_all_modifies_statements_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_modifies_procedures_relationship()")
{
    PKB pkb;
    
    std::unordered_map<std::string, std::vector<std::string>> result;
    std::unordered_map<std::string, std::vector<std::string>> expected;
    
    SECTION("bank without element")
    {
        result = pkb.get_all_modifies_procedures_relationship();
        REQUIRE(result.empty());
    }
    
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "b");
    
    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX",value2);
        result = pkb.get_all_modifies_procedures_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

bool does_uses_exist();
bool does_modifies_exist();
