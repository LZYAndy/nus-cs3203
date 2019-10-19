#include <WhileBank.h>
#include "catch.hpp"

TEST_CASE("WhileBank::insert_while()")
{
    WhileBank while_bank;
    SECTION("return false")
    {
        REQUIRE_FALSE(while_bank.insert_while(0, {"y"}));
    }

    SECTION("return true")
    {
        REQUIRE(while_bank.insert_while(5, {"y"}));
    }
}

TEST_CASE("WhileBank::insert_stmt_in_while_stmtLst()")
{
    WhileBank while_bank;
    while_bank.insert_while(2, {"x"});
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
    while_bank.insert_while(10, {"x"});
    SECTION("return true")
    {
        REQUIRE_FALSE(while_bank.is_while(1));
    }

    SECTION("return false")
    {
        REQUIRE(while_bank.is_while(10));
    }
}

TEST_CASE("WhileBank::get_while_stmtLst()")
{
    WhileBank while_bank;
    while_bank.insert_while(3, {"x"});
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

TEST_CASE("WhileBank::get_while_with_control_var()")
{
    WhileBank while_bank;
    while_bank.insert_while(1, {"x", "y"});
    while_bank.insert_while(10, {"x"});

    SECTION("return 0 statement")
    {
        std::vector<int> result = while_bank.get_while_with_control_var("y");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 0 statements")
    {
        std::vector<int> result = while_bank.get_while_with_control_var("x");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(10);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("WhileBank::get_all_whilestmt_and_control_var()")
{
    WhileBank while_bank;
    SECTION("return 0 relationship")
    {
        std::unordered_map<int, std::vector<std::string>> result = while_bank.get_all_whilestmt_and_control_var();
        REQUIRE(result.empty());
    }

    while_bank.insert_while(1, {"x", "y"});
    while_bank.insert_while(10, {"x"});
    SECTION("return more than 0 relationships")
    {
        std::unordered_map<int, std::vector<std::string>> result = while_bank.get_all_whilestmt_and_control_var();
        REQUIRE(result.size() == 2);
        std::unordered_map<int, std::vector<std::string>> expected;
        std::vector<std::string> value1;
        std::vector<std::string> value2;
        value1.push_back("x");
        value1.push_back("y");
        value2.push_back("x");
        expected.emplace(1, value1);
        expected.emplace(10, value2);
        REQUIRE(expected == result);
    }
}
