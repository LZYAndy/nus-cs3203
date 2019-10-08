#include <WhileBank.h>
#include "catch.hpp"

TEST_CASE("WhileBank::insert_while()")
{
    WhileBank while_bank;
    while_bank.insert_while(1, "x == 1");
    SECTION("return false")
    {
        REQUIRE_FALSE(while_bank.insert_while(0, "y > 1"));
    }

    SECTION("return true")
    {
        REQUIRE(while_bank.insert_while(5, "y == 1"));
    }
}

TEST_CASE("WhileBank::insert_stmt_in_while_stmtLst()")
{
    WhileBank while_bank;
    while_bank.insert_while(2, "x == 1");
    SECTION("return false")
    {
        REQUIRE_FALSE(while_bank.insert_stmt_in_while_stmtLst(3, 5));
        REQUIRE_FALSE(while_bank.insert_stmt_in_while_stmtLst(0, 5));
        REQUIRE_FALSE(while_bank.insert_stmt_in_while_stmtLst(2, 2));
    }

    SECTION("return true")
    {
        REQUIRE(while_bank.insert_stmt_in_while_stmtLst(2, 5));
    }
}

TEST_CASE("WhileBank::is_while()")
{
    WhileBank while_bank;
    while_bank.insert_while(10, "x == 1");
    SECTION("return true")
    {
        REQUIRE_FALSE(while_bank.is_while(1));
    }

    SECTION("return false")
    {
        REQUIRE(while_bank.is_while(10));
    }
}

TEST_CASE("WhileBank::get_while_statements()")
{
    WhileBank while_bank;
    SECTION("return 0 statement")
    {
        std::vector<int> result = while_bank.get_while_statements();
        REQUIRE(result.empty());
    }

    while_bank.insert_while(1, "x == 1");
    SECTION("return 1 statement")
    {
        std::vector<int> result = while_bank.get_while_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    while_bank.insert_while(5, "y == 1");
    while_bank.insert_while(10, "x == y");
    SECTION("return more than 1 statements")
    {
        std::vector<int> result = while_bank.get_while_statements();
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(10);
        expected.push_back(5);
        expected.push_back(1);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("WhileBank::get_while_stmtLst()")
{
    WhileBank while_bank;
    while_bank.insert_while(3, "x == 1");
    while_bank.insert_stmt_in_while_stmtLst(3, 4);
    SECTION("return 1 statement")
    {
        std::vector<int> result = while_bank.get_while_stmtLst(3);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 4);
    }
    while_bank.insert_stmt_in_while_stmtLst(3, 5);
    while_bank.insert_stmt_in_while_stmtLst(3, 6);
    SECTION("return more than 1 statements")
    {
        std::vector<int> result = while_bank.get_while_stmtLst(3);
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(6);
        expected.push_back(5);
        expected.push_back(4);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}
