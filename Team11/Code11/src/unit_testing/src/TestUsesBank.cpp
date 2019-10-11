#include "catch.hpp"
#include "UsesBank.h"

TEST_CASE("UsesBank::get_statements_uses()")
{
    UsesBank uses_bank;
    uses_bank.insert_uses(1, "a");
    uses_bank.insert_uses(2, "b");
    uses_bank.insert_uses(7, "a");
    uses_bank.insert_uses(7, "d");
    uses_bank.insert_uses(9, "c");

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = uses_bank.get_statements_uses("nya");
        REQUIRE(result.empty());

        result = uses_bank.get_statements_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = uses_bank.get_statements_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);

        result = uses_bank.get_statements_uses("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);

        result = uses_bank.get_statements_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }

    SECTION("return more than 1 statement")
    {
        result = uses_bank.get_statements_uses("a");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }

}

TEST_CASE("UsesBank::get_procedures_uses()")
{
    UsesBank uses_bank;
    uses_bank.insert_uses("main", "a");
    uses_bank.insert_uses("main", "b");
    uses_bank.insert_uses("procX", "a");
    uses_bank.insert_uses("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = uses_bank.get_procedures_uses("nya");
        REQUIRE(result.empty());

        result = uses_bank.get_procedures_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 procedure")
    {
        result = uses_bank.get_procedures_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);

        result = uses_bank.get_procedures_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }

    SECTION("return more than 1 procedure")
    {
        result = uses_bank.get_procedures_uses("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("UsesBank::get_used_by_statement()")
{
    UsesBank uses_bank;

    uses_bank.insert_uses(1, "a");
    uses_bank.insert_uses(2, "b");
    uses_bank.insert_uses(5, "a");
    uses_bank.insert_uses(5, "d");
    uses_bank.insert_uses(100, "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = uses_bank.get_used_by_statement(3);
        REQUIRE(result.empty());

        result = uses_bank.get_used_by_statement(233);
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = uses_bank.get_used_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);

        result = uses_bank.get_used_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = uses_bank.get_used_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = uses_bank.get_used_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("UsesBank::get_used_by_procedure()")
{
    UsesBank uses_bank;
    uses_bank.insert_uses("main", "a");
    uses_bank.insert_uses("main", "b");
    uses_bank.insert_uses("procX", "a");
    uses_bank.insert_uses("procY", "c");

    std::vector<std::string> result;

    SECTION("return 0 variable")
    {
        result = uses_bank.get_used_by_procedure("nya");
        REQUIRE(result.empty());

        result = uses_bank.get_used_by_procedure("procx");
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = uses_bank.get_used_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = uses_bank.get_used_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = uses_bank.get_used_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("UsesBank::is_uses() for stmt")
{
    UsesBank uses_bank;
    uses_bank.insert_uses(1,"a");
    uses_bank.insert_uses(2,"a");

    SECTION("return true")
    {
        REQUIRE(uses_bank.is_uses(1, "a"));
        REQUIRE(uses_bank.is_uses(2, "a"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(uses_bank.is_uses(3, "a"));
        REQUIRE_FALSE(uses_bank.is_uses(2, "b"));
    }
}

TEST_CASE("UsesBank::is_uses() for proc")
{
    UsesBank uses_bank;
    uses_bank.insert_uses("main","a");
    uses_bank.insert_uses("main","b");

    SECTION("return true")
    {
        REQUIRE(uses_bank.is_uses("main", "a"));
        REQUIRE(uses_bank.is_uses("main", "b"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(uses_bank.is_uses("proc", "a"));
        REQUIRE_FALSE(uses_bank.is_uses("main", "B"));
    }
}

TEST_CASE("UsesBank::get_all_uses_procedures()")
{
    UsesBank uses_bank;

    std::vector<std::string> result;

    SECTION("return 0 procedure")
    {
        result = uses_bank.get_all_uses_procedures();
        REQUIRE(result.empty());
    }

    uses_bank.insert_uses("main", "a");
    uses_bank.insert_uses("main", "b");

    SECTION("return 1 procedure")
    {
        result = uses_bank.get_all_uses_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }

    uses_bank.insert_uses("procX", "a");
    uses_bank.insert_uses("procY", "c");

    SECTION("return more than 1 procedure")
    {
        result = uses_bank.get_all_uses_procedures();
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

TEST_CASE("UsesBank::get_all_uses_statements()")
{
    UsesBank uses_bank;

    std::vector<int> result;

    SECTION("return 0 statement")
    {
        result = uses_bank.get_all_uses_statements();
        REQUIRE(result.empty());
    }

    uses_bank.insert_uses(1, "a");
    uses_bank.insert_uses(1, "b");

    SECTION("return 1 statement")
    {
        result = uses_bank.get_all_uses_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    uses_bank.insert_uses(5, "a");
    uses_bank.insert_uses(6, "c");

    SECTION("return more than 1 statement")
    {
        result = uses_bank.get_all_uses_statements();
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

TEST_CASE("UsesBank::get_all_uses_statements_relationship()")
{
    UsesBank uses_bank;

    std::unordered_map<int, std::vector<std::string>> result;
    std::unordered_map<int, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = uses_bank.get_all_uses_statements_relationship();
        REQUIRE(result.empty());
    }

    uses_bank.insert_uses(1, "a");
    uses_bank.insert_uses(1, "b");
    uses_bank.insert_uses(5, "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5,value2);
        result = uses_bank.get_all_uses_statements_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

TEST_CASE("UsesBank::get_all_uses_procedures_relationship()")
{
    UsesBank uses_bank;

    std::unordered_map<std::string, std::vector<std::string>> result;
    std::unordered_map<std::string, std::vector<std::string>> expected;

    SECTION("bank without element")
    {
        result = uses_bank.get_all_uses_procedures_relationship();
        REQUIRE(result.empty());
    }

    uses_bank.insert_uses("main", "a");
    uses_bank.insert_uses("main", "b");
    uses_bank.insert_uses("procX", "b");

    SECTION("bank with element(s)")
    {
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX",value2);
        result = uses_bank.get_all_uses_procedures_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}

TEST_CASE("UsesBank::insert_uses_for_call()")
{
    UsesBank uses_bank;
    uses_bank.insert_uses("main", "x");
    uses_bank.insert_uses("procY", "y");
    SECTION("return false")
    {
        REQUIRE_FALSE(uses_bank.insert_uses_for_call("main", "procX"));
    }
    SECTION("return true")
    {
        uses_bank.insert_uses_for_call("main", "procY");
        std::vector<std::string> result = uses_bank.get_used_by_procedure("main");
        REQUIRE(uses_bank.insert_uses_for_call("main", "procY"));
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == "x");
        REQUIRE(result[1] == "y");
    }
}
