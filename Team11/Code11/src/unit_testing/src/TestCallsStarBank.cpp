#include "catch.hpp"
#include "CallsStarBank.h"

TEST_CASE("CallsStarBank::does_calls_star_exist()")
{
    CallsStarBank calls_star_bank;
    
    SECTION("empty")
    {
        calls_star_bank.insert_calls_star("hello", "hello");
        REQUIRE_FALSE(calls_star_bank.does_calls_star_exist());
    }

    SECTION(">1")
    {
        calls_star_bank.insert_calls_star("hello", "helloWorld");
        REQUIRE(calls_star_bank.does_calls_star_exist());
    }
}

TEST_CASE("CallsStarBank::is_calls_star()")
{
    CallsStarBank calls_star_bank;
    calls_star_bank.insert_calls_star("hello", "world");
    calls_star_bank.insert_calls_star("foo", "bar");
    calls_star_bank.insert_calls_star("chocolate", "vanilla");
    calls_star_bank.insert_calls_star("hello", "chocolate");

    SECTION("return false")
    {
        REQUIRE_FALSE(calls_star_bank.is_calls_star("hello", "vanilla"));
        REQUIRE_FALSE(calls_star_bank.is_calls_star("Foo", "Bar"));
    }

    SECTION("return true")
    {
        REQUIRE(calls_star_bank.is_calls_star("foo", "bar"));
        REQUIRE(calls_star_bank.is_calls_star("hello", "world"));
        REQUIRE(calls_star_bank.is_calls_star("hello", "chocolate"));
    }
}

TEST_CASE("CallsStarBank::get_all_procedures_calls_star()")
{
    CallsStarBank calls_star_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_star_bank.get_all_procedures_calls_star().empty());
    }

    SECTION("return 1")
    {
        calls_star_bank.insert_calls_star("hello", "world");
        calls_star_bank.insert_calls_star("bye", "world");
        std::vector<std::string> result = calls_star_bank.get_all_procedures_calls_star();
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        calls_star_bank.insert_calls_star("hello", "world");
        calls_star_bank.insert_calls_star("hello", "banana");
        calls_star_bank.insert_calls_star("chocolate", "banana");
        calls_star_bank.insert_calls_star("chocolate", "pie");
        std::vector<std::string> result = calls_star_bank.get_all_procedures_calls_star();
        REQUIRE(result.size() == 3);
        std::vector<std::string> expected;
        expected.push_back("world");
        expected.push_back("banana");
        expected.push_back("pie");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("CallsStarBank::get_all_procedures_called_star()")
{
    CallsStarBank calls_star_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_star_bank.get_all_procedures_called_star().empty());
    }

    SECTION("return 1")
    {
        calls_star_bank.insert_calls_star("hello", "world");
        calls_star_bank.insert_calls_star("hello", "itsMe");
        std::vector<std::string> result = calls_star_bank.get_all_procedures_called_star();
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        calls_star_bank.insert_calls_star("hello", "world");
        calls_star_bank.insert_calls_star("hello", "banana");
        calls_star_bank.insert_calls_star("chocolate", "banana");
        calls_star_bank.insert_calls_star("chocolate", "pie");
        std::vector<std::string> result = calls_star_bank.get_all_procedures_called_star();
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("hello");
        expected.push_back("chocolate");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("CallsStarBank::get_procedures_called_by_star()")
{
    CallsStarBank calls_star_bank;
    calls_star_bank.insert_calls_star("hello", "world");
    calls_star_bank.insert_calls_star("hello", "itsMe");
    calls_star_bank.insert_calls_star("hello", "banana");
    calls_star_bank.insert_calls_star("chocolate", "banana");
    calls_star_bank.insert_calls_star("chocolate", "pie");
    calls_star_bank.insert_calls_star("banana", "pie");

    SECTION("return empty")
    {
        REQUIRE(calls_star_bank.get_procedures_called_by_star("bye").empty());
    }

    SECTION("return 1")
    {
        std::vector<std::string> result = calls_star_bank.get_procedures_called_by_star("banana");
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("pie");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        std::vector<std::string> result = calls_star_bank.get_procedures_called_by_star("chocolate");
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("banana");
        expected.push_back("pie");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}


TEST_CASE("CallsStarBank::get_all_procedures_calls_star_relationship()")
{
    CallsStarBank calls_star_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_star_bank.get_all_procedures_calls_star_relationship().empty());
    }

    calls_star_bank.insert_calls_star("hello", "world");
    calls_star_bank.insert_calls_star("hello", "itsMe");
    calls_star_bank.insert_calls_star("hello", "banana");

    SECTION("return 1")
    {
        std::unordered_map<std::string, std::vector<std::string>> result = calls_star_bank.get_all_procedures_calls_star_relationship();
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        std::vector<std::string> result_values = result["hello"];
        std::sort(expected.begin(), expected.end());
        std::sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);
    }


    SECTION("return >1")
    {
        calls_star_bank.insert_calls_star("chocolate", "banana");
        calls_star_bank.insert_calls_star("chocolate", "pie");
        calls_star_bank.insert_calls_star("banana", "pie");
        std::unordered_map<std::string, std::vector<std::string>> result = calls_star_bank.get_all_procedures_calls_star_relationship();
        REQUIRE(result.size() == 3);
        std::vector<std::string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        std::vector<std::string> result_values = result["hello"];
        std::sort(expected.begin(), expected.end());
        std::sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);

        std::vector<std::string> expected2;
        expected2.push_back("pie");
        expected2.push_back("banana");
        std::vector<std::string> result_values2 = result["chocolate"];
        std::sort(expected2.begin(), expected2.end());
        std::sort(result_values2.begin(), result_values2.end());
        REQUIRE(expected2 == result_values2);

        std::vector<std::string> expected3;
        expected3.push_back("pie");
        std::vector<std::string> result_values3 = result["banana"];
        std::sort(expected3.begin(), expected3.end());
        std::sort(result_values3.begin(), result_values3.end());
        REQUIRE(expected3 == result_values3);
    }
}
