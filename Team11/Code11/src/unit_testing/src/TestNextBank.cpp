#include <NextBank.h>
#include "catch.hpp"

TEST_CASE("NextBank::insert_next()")
{
    NextBank next_bank;
    SECTION("return false")
    {
        REQUIRE_FALSE(next_bank.insert_next(3, 3));
        REQUIRE_FALSE(next_bank.insert_next(0, 1));
        REQUIRE_FALSE(next_bank.insert_next(1, 0));
    }

    SECTION("return false")
    {
        REQUIRE(next_bank.insert_next(3, 4));
    }
}

TEST_CASE("NextBank::is_next()")
{
    NextBank next_bank;
    next_bank.insert_next(3, 4);
    SECTION("return false")
    {
        REQUIRE_FALSE(next_bank.is_next(3, 5));
        REQUIRE_FALSE(next_bank.is_next(4, 3));
    }

    SECTION("return true")
    {
        REQUIRE(next_bank.is_next(3, 4));
    }
}

TEST_CASE("NextBank::does_next_exists()")
{
    NextBank next_bank;
    SECTION("return false")
    {
        REQUIRE_FALSE(next_bank.does_next_exists());
    }

    next_bank.insert_next(1, 2);
    SECTION("return true")
    {
        REQUIRE(next_bank.does_next_exists());
    }
}

TEST_CASE("NextBank::get_statements_previous()")
{
    NextBank next_bank;
    next_bank.insert_next(3, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(1, 2);
    SECTION("return 0 statement")
    {
        std::vector<int> result = next_bank.get_statements_previous(3);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        std::vector<int> result = next_bank.get_statements_previous(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statements")
    {
        std::vector<int> result = next_bank.get_statements_previous(10);
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(9);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("NextBank::get_statements_next()")
{
    NextBank next_bank;
    next_bank.insert_next(3, 10);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(1, 2);
    SECTION("return 0 statement")
    {
        std::vector<int> result = next_bank.get_statements_next(2);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        std::vector<int> result = next_bank.get_statements_next(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    SECTION("return more than 1 statement")
    {
        std::vector<int> result = next_bank.get_statements_next(3);
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(10);
        expected.push_back(4);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("NextBank::get_all_previous()")
{
    NextBank next_bank;
    SECTION("return 0 statement")
    {
        std::vector<int> result = next_bank.get_all_previous();
        REQUIRE(result.empty());
    }

    next_bank.insert_next(5, 10);
    SECTION("return 1 statement")
    {
        std::vector<int> result = next_bank.get_all_previous();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 5);
    }

    next_bank.insert_next(9, 10);
    SECTION("return more than 1 statement")
    {
        std::vector<int> result = next_bank.get_all_previous();
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(5);
        expected.push_back(9);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("NextBank::get_all_next()")
{
    NextBank next_bank;
    SECTION("return 0 statement")
    {
        std::vector<int> result = next_bank.get_all_next();
        REQUIRE(result.empty());
    }

    next_bank.insert_next(1, 2);
    SECTION("return 1 statement")
    {
        std::vector<int> result = next_bank.get_all_next();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    next_bank.insert_next(1, 10);
    SECTION("return more than 1 statement")
    {
        std::vector<int> result = next_bank.get_all_next();
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(10);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}
