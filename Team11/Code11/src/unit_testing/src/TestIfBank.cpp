#include "catch.hpp"
#include "IfBank.h"

TEST_CASE("IfBank::all_contains()")
{
    IfBank if_bank;

    if_bank.insert_if(1, {"y"});
    if_bank.insert_if(2, {"x", "y"});
    if_bank.insert_if(2, {"x", "y"});
    if_bank.insert_if(3, {"y"});

    SECTION("return empty")
    {
        REQUIRE(if_bank.all_contains("DONTEXIST").empty());
        REQUIRE(if_bank.all_contains("X").empty());
    }

    SECTION("return 1 result")
    {
        REQUIRE(if_bank.all_contains("x").size() == 1);
        REQUIRE(if_bank.all_contains("x")[0] == 2);
    }

    SECTION("return >1 result")
    {
        std::vector<int> result = if_bank.all_contains("y");
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

TEST_CASE("IfBank::get_all_if_and_control_variables_map()")
{
    IfBank if_bank;

    SECTION("empty")
    {
        REQUIRE(if_bank.get_all_if_and_control_variables_map().empty());
    }
    
    if_bank.insert_if(1, {"y"});
    if_bank.insert_if(2, {"x", "y"});
    if_bank.insert_if(2, {"x", "y"});
    if_bank.insert_if(3, {"y"});

    SECTION(">1")
    {
        std::unordered_map<int, std::vector<std::string>> expected;
        expected.insert({1, {"y"}});
        expected.insert({2, {"x", "y"}});
        expected.insert({3, {"y"}});
        REQUIRE(expected == if_bank.get_all_if_and_control_variables_map());
    }
}
