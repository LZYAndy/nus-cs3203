#include "catch.hpp"
#include "AssignBank.h"
#include "Bank.cpp"

TEST_CASE("AssignBank::matches()")
{
    AssignBank assign_bank;
    assign_bank.insert_assign(1, "a", "b");
    assign_bank.insert_assign(2, "b", "c");
    assign_bank.insert_assign(3, "c", "d");
    assign_bank.insert_assign(4, "a", "bc");
    assign_bank.insert_assign(5, "a", "b");
    assign_bank.insert_assign(6, "b", "b");

    SECTION("return 1 stmt")
    {
        std::vector<int> stmts = assign_bank.matches("b", "c");
        REQUIRE(stmts.size() == 1);
        REQUIRE(stmts.at(0) == 2);
    }

    SECTION("return >1 stmts")
    {
        std::vector<int> stmts = assign_bank.matches("a", "b");
        REQUIRE(stmts.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        std::sort(expected.begin(), expected.end());
        std::sort(stmts.begin(), stmts.end());
        REQUIRE(expected == stmts);
    }

    SECTION("return 0 stmts")
    {
        std::vector<int> stmts;
        stmts = assign_bank.matches("a", "d");
        REQUIRE(stmts.empty());

        stmts = assign_bank.matches("a", "DNE");
        REQUIRE(stmts.empty());

        stmts = assign_bank.matches("DNE", "a");
        REQUIRE(stmts.empty());
    }
}

TEST_CASE("AssignBank::contains()")
{
    AssignBank assign_bank;
    assign_bank.insert_assign(1, "a", "b");
    assign_bank.insert_assign(2, "b", "c");
    assign_bank.insert_assign(3, "c", "d");
    assign_bank.insert_assign(4, "a", "bc");
    assign_bank.insert_assign(5, "a", "b");
    assign_bank.insert_assign(6, "b", "b");
    assign_bank.insert_assign(7, "e", "(b)");
    assign_bank.insert_assign(8, "f", "b+");
    assign_bank.insert_assign(9, "g", "-b");
    assign_bank.insert_assign(10, "h", "%b/");

    SECTION("return 1 stmt")
    {
        std::vector<int> stmts = assign_bank.contains("e", "b");
        REQUIRE(stmts.size() == 1);
        REQUIRE(stmts.at(0) == 7);
        std::vector<int> stmts_1 = assign_bank.contains("f", "b");
        REQUIRE(stmts_1.size() == 1);
        REQUIRE(stmts_1.at(0) == 8);
        std::vector<int> stmts_2 = assign_bank.contains("g", "b");
        REQUIRE(stmts_2.size() == 1);
        REQUIRE(stmts_2.at(0) == 9);
        std::vector<int> stmts_3 = assign_bank.contains("h", "b");
        REQUIRE(stmts_3.size() == 1);
        REQUIRE(stmts_3.at(0) == 10);
    }

    SECTION("return >1 stmts")
    {
        std::vector<int> stmts = assign_bank.contains("a", "b");
        REQUIRE(stmts.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        std::sort(expected.begin(), expected.end());
        std::sort(stmts.begin(), stmts.end());
        REQUIRE(expected == stmts);
    }

    SECTION("return 0 stmts")
    {
        std::vector<int> stmts;
        stmts = assign_bank.contains("a", "d");
        REQUIRE(stmts.empty());

        stmts = assign_bank.contains("a", "DNE");
        REQUIRE(stmts.empty());

        stmts = assign_bank.contains("DNE", "a");
        REQUIRE(stmts.empty());
    }
}

TEST_CASE("AssignBank::all_matches()")
{
    AssignBank assign_bank;
    assign_bank.insert_assign(1, "a", "b");
    assign_bank.insert_assign(2, "b", "c");
    assign_bank.insert_assign(3, "c", "d");
    assign_bank.insert_assign(4, "a", "bc");
    assign_bank.insert_assign(5, "a", "b");
    assign_bank.insert_assign(6, "b", "b");

    SECTION("return 0 stmt")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_matches("DNE");
        REQUIRE(stmts.empty());
    }

    SECTION("return 1 stmt")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_matches("c");
        REQUIRE(stmts.size() == 1);
        REQUIRE(stmts[0] == 2);
    }

    SECTION("return >1 stmts")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_matches("b");
        REQUIRE(stmts.size() == 3);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        std::sort(expected.begin(), expected.end());
        std::sort(stmts.begin(), stmts.end());
    }
}

TEST_CASE("AssignBank::all_contains()")
{
    AssignBank assign_bank;
    assign_bank.insert_assign(1, "a", "b");
    assign_bank.insert_assign(2, "b", "c");
    assign_bank.insert_assign(3, "c", "d");
    assign_bank.insert_assign(4, "a", "bc");
    assign_bank.insert_assign(5, "a", "b");
    assign_bank.insert_assign(6, "b", "b");

    SECTION("return 0 stmt")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_contains("DNE");
        REQUIRE(stmts.empty());
    }

    SECTION("return 1 stmt")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_contains("c");
        REQUIRE(stmts.size() == 1);
        REQUIRE(stmts[0] == 2);
    }

    SECTION("return >1 stmts")
    {
        std::vector<int> stmts;
        stmts = assign_bank.all_contains("b");
        REQUIRE(stmts.size() == 3);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        std::sort(expected.begin(), expected.end());
        std::sort(stmts.begin(), stmts.end());
    }
}

TEST_CASE("AssignBank::get_variable_from_statement()")
{
    AssignBank assign_bank;
    assign_bank.insert_assign(1, "a", "b");
    assign_bank.insert_assign(2, "b", "c");
    assign_bank.insert_assign(3, "c", "d");
    assign_bank.insert_assign(4, "a", "bc");
    assign_bank.insert_assign(5, "a", "b");
    assign_bank.insert_assign(6, "b", "b");

    SECTION("get empty")
    {
        std::string result = assign_bank.get_variable_from_statement(0);
        REQUIRE(result.empty());
    }

    SECTION("get success")
    {
        std::string result = assign_bank.get_variable_from_statement(6);
        REQUIRE(result == "b");
    }
}
