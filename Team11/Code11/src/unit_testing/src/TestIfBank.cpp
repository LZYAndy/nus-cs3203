#include "catch.hpp"
#include "IfBank.h"

TEST_CASE("IfBank::all_matches()")
{
    IfBank if_bank;

    if_bank.insert_if(1, "x==1");
    if_bank.insert_if(2, "x==2");
    if_bank.insert_if(2, "x==2");
    if_bank.insert_if(3, "x==1");

    SECTION("return empty")
    {
        REQUIRE(if_bank.all_matches("x != DONTEXIST").empty());
    }

    SECTION("return 1 result")
    {
        REQUIRE(if_bank.all_matches("x==2").size() == 1);
        REQUIRE(if_bank.all_matches("x==2")[0] == 2);
    }

    SECTION("return >1 result")
    {
        std::vector<int> result = if_bank.all_matches("x==1");
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("IfBank::all_contains()")
{
    IfBank if_bank;

    if_bank.insert_if(1, "x==1");
    if_bank.insert_if(2, "x==2");
    if_bank.insert_if(2, "x==2");
    if_bank.insert_if(3, "x==1");

    SECTION("return empty")
    {
        REQUIRE(if_bank.all_contains("x != DONTEXIST").empty());
        REQUIRE(if_bank.all_contains("X").empty());
    }

    SECTION("return 1 result")
    {
        REQUIRE(if_bank.all_contains("x==2").size() == 1);
        REQUIRE(if_bank.all_contains("x==2")[0] == 2);
    }

    SECTION("return >1 result")
    {
        std::vector<int> result = if_bank.all_contains("x");
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}