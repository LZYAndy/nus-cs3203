#include "catch.hpp"
#include "ModifiesBank.h"

TEST_CASE("ModifiesBank::get_statements_modifies()")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies(1, "a");
    modifies_bank.insert_modifies(2, "b");
    modifies_bank.insert_modifies(7, "a");
    modifies_bank.insert_modifies(7, "d");
    modifies_bank.insert_modifies(9, "c");

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = modifies_bank.get_statements_modifies("nya");
        REQUIRE(result.empty());

        result = modifies_bank.get_statements_modifies("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = modifies_bank.get_statements_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);

        result = modifies_bank.get_statements_modifies("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);

        result = modifies_bank.get_statements_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }

    SECTION("return more than 1 statement")
    {
        result = modifies_bank.get_statements_modifies("a");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }

}

TEST_CASE("ModifiesBank::get_procedures_modifies()")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies("main", "a");
    modifies_bank.insert_modifies("main", "b");
    modifies_bank.insert_modifies("procX", "a");
    modifies_bank.insert_modifies("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = modifies_bank.get_procedures_modifies("nya");
        REQUIRE(result.empty());

        result = modifies_bank.get_procedures_modifies("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 procedure")
    {
        result = modifies_bank.get_procedures_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);

        result = modifies_bank.get_procedures_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }

    SECTION("return more than 1 procedure")
    {
        result = modifies_bank.get_procedures_modifies("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("ModifiesBank::get_modified_by_statement()")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies(1, "a");
    modifies_bank.insert_modifies(2, "b");
    modifies_bank.insert_modifies(5, "a");
    modifies_bank.insert_modifies(5, "d");
    modifies_bank.insert_modifies(100, "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = modifies_bank.get_modified_by_statement(3);
        REQUIRE(result.empty());

        result = modifies_bank.get_modified_by_statement(233);
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = modifies_bank.get_modified_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);

        result = modifies_bank.get_modified_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = modifies_bank.get_modified_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = modifies_bank.get_modified_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("ModifiesBank::get_modified_by_procedure()")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies("main", "a");
    modifies_bank.insert_modifies("main", "b");
    modifies_bank.insert_modifies("procX", "a");
    modifies_bank.insert_modifies("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = modifies_bank.get_modified_by_procedure("nya");
        REQUIRE(result.empty());

        result = modifies_bank.get_modified_by_procedure("procx");
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = modifies_bank.get_modified_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = modifies_bank.get_modified_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = modifies_bank.get_modified_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("ModifiesBank::is_modifies() for stmt")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies(1,"a");
    modifies_bank.insert_modifies(2,"a");

    SECTION("return true")
    {
        REQUIRE(modifies_bank.is_modifies(1, "a"));
        REQUIRE(modifies_bank.is_modifies(2, "a"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(modifies_bank.is_modifies(3, "a"));
        REQUIRE_FALSE(modifies_bank.is_modifies(2, "b"));
    }
}

TEST_CASE("ModifiesBank::is_modifies() for proc")
{
    ModifiesBank modifies_bank;
    modifies_bank.insert_modifies("main","a");
    modifies_bank.insert_modifies("main","b");

    SECTION("return true")
    {
        REQUIRE(modifies_bank.is_modifies("main", "a"));
        REQUIRE(modifies_bank.is_modifies("main", "b"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(modifies_bank.is_modifies("proc", "a"));
        REQUIRE_FALSE(modifies_bank.is_modifies("main", "B"));
    }
}

TEST_CASE("ModifiesBank::get_all_modifies_procedures()")
{
    ModifiesBank modifies_bank;

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = modifies_bank.get_all_modifies_procedures();
        REQUIRE(result.empty());
    }

    modifies_bank.insert_modifies("main", "a");
    modifies_bank.insert_modifies("main", "b");

    SECTION("return 1 procedure")
    {
        result = modifies_bank.get_all_modifies_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }

    modifies_bank.insert_modifies("procX", "a");
    modifies_bank.insert_modifies("procY", "c");

    SECTION("return more than 1 procedure")
    {
        result = modifies_bank.get_all_modifies_procedures();
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

TEST_CASE("ModifiesBank::get_all_modifies_statements()")
{
    ModifiesBank modifies_bank;

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = modifies_bank.get_all_modifies_statements();
        REQUIRE(result.empty());
    }

    modifies_bank.insert_modifies(1, "a");
    modifies_bank.insert_modifies(1, "b");

    SECTION("return 1 statement")
    {
        result = modifies_bank.get_all_modifies_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    modifies_bank.insert_modifies(5, "a");
    modifies_bank.insert_modifies(6, "c");

    SECTION("return more than 1 statement")
    {
        result = modifies_bank.get_all_modifies_statements();
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

TEST_CASE("ModifiesBank::get_all_modifies_statements_relationship()")
{
    ModifiesBank modifies_bank;

    std::unordered_map<int, std::vector<std::string>> result;
    std::unordered_map<int, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = modifies_bank.get_all_modifies_statements_relationship();
        REQUIRE(result.empty());
    }

    modifies_bank.insert_modifies(1, "a");
    modifies_bank.insert_modifies(1, "b");
    modifies_bank.insert_modifies(5, "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5,value2);
        result = modifies_bank.get_all_modifies_statements_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

TEST_CASE("ModifiesBank::get_all_modifies_procedures_relationship()")
{
    ModifiesBank modifies_bank;

    std::unordered_map<std::string, std::vector<std::string>> result;
    std::unordered_map<std::string, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = modifies_bank.get_all_modifies_procedures_relationship();
        REQUIRE(result.empty());
    }

    modifies_bank.insert_modifies("main", "a");
    modifies_bank.insert_modifies("main", "b");
    modifies_bank.insert_modifies("procX", "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX",value2);
        result = modifies_bank.get_all_modifies_procedures_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}
