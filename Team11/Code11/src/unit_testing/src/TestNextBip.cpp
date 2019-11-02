#include "catch.hpp"
#include "NextBipBank.h"

TEST_CASE("NextBipBank::get_next_bip")
{
    NextBipBank next_bip_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION("no next bip")
    {
        REQUIRE(next_bip_bank.get_next_bip(7).empty());
        REQUIRE(next_bip_bank.get_next_bip(0).empty());
    }

    SECTION("1 next bip")
    {
        std::vector<int> result = next_bip_bank.get_next_bip(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({2}));
    }

    SECTION(">1 next bip")
    {
        std::vector<int> result = next_bip_bank.get_next_bip(4);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({5, 6});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("NextBipBank::get_previous_bip")
{
    NextBipBank next_bip_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION("no previous bip")
    {
        REQUIRE(next_bip_bank.get_previous_bip(1).empty());
        REQUIRE(next_bip_bank.get_previous_bip(8).empty());
    }

    SECTION("1 previous bip")
    {
        std::vector<int> result = next_bip_bank.get_previous_bip(7);
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({6}));
    }

    SECTION(">1 previous bip")
    {
        std::vector<int> result = next_bip_bank.get_previous_bip(4);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({5, 2});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("NextBipBank::get_all_next_bip")
{
    NextBipBank next_bip_bank;
    
    SECTION("no next bip")
    {
        REQUIRE(next_bip_bank.get_all_next_bip().empty());
    }
    
    next_bip_bank.insert_next_bip(1, 2);
   
    SECTION("1 next bip")
    {
        std::vector<int> result = next_bip_bank.get_all_next_bip();
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({2}));
    }

    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION(">1 next bip")
    {
        std::vector<int> result = next_bip_bank.get_all_next_bip();
        REQUIRE(result.size() == 5);
        std::vector<int> expected({2, 4, 5, 6, 7});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("NextBipBank::get_all_previous_bip")
{
    NextBipBank next_bip_bank;
    
    SECTION("no previous bip")
    {
        REQUIRE(next_bip_bank.get_all_previous_bip().empty());
    }
    
    next_bip_bank.insert_next_bip(1, 2);
   
    SECTION("1 previous bip")
    {
        std::vector<int> result = next_bip_bank.get_all_previous_bip();
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({1}));
    }

    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION(">1 previous bip")
    {
        std::vector<int> result = next_bip_bank.get_all_previous_bip();
        REQUIRE(result.size() == 5);
        std::vector<int> expected({2, 4, 5, 6, 1});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("NextBipBank::get_all_next_bip_relationship")
{
    NextBipBank next_bip_bank;
    
    SECTION("no next bip")
    {
        REQUIRE(next_bip_bank.get_all_next_bip_relationship().empty());
    }
    
    next_bip_bank.insert_next_bip(1, 2);
   
    SECTION("1 next bip")
    {
        std::unordered_map<int, std::vector<int>> result = next_bip_bank.get_all_next_bip_relationship();
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == std::vector<int>({2}));
    }

    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION(">1 next bip")
    {
        std::unordered_map<int, std::vector<int>> result = next_bip_bank.get_all_next_bip_relationship();
        REQUIRE(result.size() == 5);

        std::unordered_map<int, std::vector<int>> expected;
        expected.insert({1, {2}});
        expected.insert({2, {4}});
        expected.insert({4, {5, 6}});
        expected.insert({5, {4}});
        expected.insert({6, {7}});
        REQUIRE(expected == result);
    }
}

TEST_CASE("NextBipBank::is_next_bip")
{
    NextBipBank next_bip_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION("false")
    {
        REQUIRE_FALSE(next_bip_bank.is_next_bip(1, 4));
        REQUIRE_FALSE(next_bip_bank.is_next_bip(4, 4));
    }

    SECTION("true")
    {
        REQUIRE(next_bip_bank.is_next_bip(1, 2));
        REQUIRE(next_bip_bank.is_next_bip(4, 6));
    }
}

TEST_CASE("NextBipBank::does_next_bip_exists")
{
    NextBipBank next_bip_bank;

    SECTION("false")
    {
        REQUIRE_FALSE(next_bip_bank.does_next_bip_exists());
    }

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);

    SECTION("true")
    {
        REQUIRE(next_bip_bank.does_next_bip_exists());
    }
}