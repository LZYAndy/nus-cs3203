#include "catch.hpp"
#include "CallsBank.h"

TEST_CASE("CallsBank::does_calls_exist()")
{
    CallsBank calls_bank;
    
    SECTION("empty")
    {
        calls_bank.insert_calls(1, "hello", "hello");
        REQUIRE_FALSE(calls_bank.does_calls_exist());
    }

    SECTION(">1")
    {
        calls_bank.insert_calls(1, "hello", "helloWorld");
        REQUIRE(calls_bank.does_calls_exist());
    }
}

TEST_CASE("CallsBank::is_calls()")
{
    CallsBank calls_bank;
    calls_bank.insert_calls(1, "hello", "world");
    calls_bank.insert_calls(2, "foo", "bar");
    calls_bank.insert_calls(3, "chocolate", "vanilla");
    calls_bank.insert_calls(4, "hello", "chocolate");

    SECTION("return false")
    {
        REQUIRE_FALSE(calls_bank.is_calls("hello", "vanilla"));
        REQUIRE_FALSE(calls_bank.is_calls("Foo", "Bar"));
    }

    SECTION("return true")
    {
        REQUIRE(calls_bank.is_calls("foo", "bar"));
        REQUIRE(calls_bank.is_calls("hello", "world"));
        REQUIRE(calls_bank.is_calls("hello", "chocolate"));
    }
}

TEST_CASE("CallsBank::get_all_procedures_calls()")
{
    CallsBank calls_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_bank.get_all_procedures_calls().empty());
    }

    SECTION("return 1")
    {
        calls_bank.insert_calls(1, "hello", "world");
        calls_bank.insert_calls(2, "bye", "world");
        std::vector<std::string> result = calls_bank.get_all_procedures_calls();
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        calls_bank.insert_calls(1, "hello", "world");
        calls_bank.insert_calls(2, "hello", "banana");
        calls_bank.insert_calls(3, "chocolate", "banana");
        calls_bank.insert_calls(4, "chocolate", "pie");
        std::vector<std::string> result = calls_bank.get_all_procedures_calls();
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

TEST_CASE("CallsBank::get_all_procedures_called()")
{
    CallsBank calls_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_bank.get_all_procedures_called().empty());
    }

    SECTION("return 1")
    {
        calls_bank.insert_calls(1, "hello", "world");
        calls_bank.insert_calls(2, "hello", "itsMe");
        std::vector<std::string> result = calls_bank.get_all_procedures_called();
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        calls_bank.insert_calls(1, "hello", "world");
        calls_bank.insert_calls(2, "hello", "banana");
        calls_bank.insert_calls(3, "chocolate", "banana");
        calls_bank.insert_calls(4, "chocolate", "pie");
        std::vector<std::string> result = calls_bank.get_all_procedures_called();
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("hello");
        expected.push_back("chocolate");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("CallsBank::get_procedures_called_by()")
{
    CallsBank calls_bank;
    calls_bank.insert_calls(1, "hello", "world");
    calls_bank.insert_calls(2, "hello", "itsMe");
    calls_bank.insert_calls(3, "hello", "banana");
    calls_bank.insert_calls(4, "chocolate", "banana");
    calls_bank.insert_calls(5, "chocolate", "pie");
    calls_bank.insert_calls(6, "banana", "pie");

    SECTION("return empty")
    {
        REQUIRE(calls_bank.get_procedures_called_by("bye").empty());
    }

    SECTION("return 1")
    {
        std::vector<std::string> result = calls_bank.get_procedures_called_by("banana");
        REQUIRE(result.size() == 1);
        std::vector<std::string> expected;
        expected.push_back("pie");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        std::vector<std::string> result = calls_bank.get_procedures_called_by("chocolate");
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("banana");
        expected.push_back("pie");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}


TEST_CASE("CallsBank::get_all_procedures_calls_relationship()")
{
    CallsBank calls_bank;

    SECTION("return empty")
    {
        REQUIRE(calls_bank.get_all_procedures_calls_relationship().empty());
    }

    calls_bank.insert_calls(1, "hello", "world");
    calls_bank.insert_calls(2, "hello", "itsMe");
    calls_bank.insert_calls(3, "hello", "banana");

    SECTION("return 1")
    {
        std::unordered_map<std::string, std::vector<std::string>> result = calls_bank.get_all_procedures_calls_relationship();
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
        calls_bank.insert_calls(1, "chocolate", "banana");
        calls_bank.insert_calls(2, "chocolate", "pie");
        calls_bank.insert_calls(3, "banana", "pie");
        std::unordered_map<std::string, std::vector<std::string>> result = calls_bank.get_all_procedures_calls_relationship();
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

TEST_CASE("CallsBank::get_all_statements_calls_relationship()")
{
    CallsBank calls_bank;

    SECTION("empty")
    {
        REQUIRE(calls_bank.get_all_statements_calls_relationship().empty());
    }

    SECTION(">1")
    {
        calls_bank.insert_calls(1, "hello", "world");
        calls_bank.insert_calls(2, "hello", "itsMe");
        calls_bank.insert_calls(3, "hello", "banana");
        std::unordered_map<int, std::vector<std::string>> result = calls_bank.get_all_statements_calls_relationship();
        std::unordered_map<int, std::vector<std::string>> expected;
        expected.insert({1, {"world"}});
        expected.insert({2, {"itsMe"}});
        expected.insert({3, {"banana"}});
        REQUIRE(expected == result);
    }
}
