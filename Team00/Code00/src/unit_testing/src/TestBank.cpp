#include "catch.hpp"
#include "Bank.h"


TEST_CASE("Bank<int, int>::get()/put()")
{
    Bank<int, int> bank;
    bank.put(1, 2);
    SECTION("get successful 1 value")
    {
        std::vector<int> result = bank.get(1);
        REQUIRE(result.size() == 1);
        int popped_value = result.at(0);
        REQUIRE(popped_value == 2);
    }
    SECTION("get successful 1 value with duplicate insert")
    {
        bank.put(1, 2);
        std::vector<int> result = bank.get(1);
        REQUIRE(result.size() == 1);
        int popped_value = result.at(0);
        REQUIRE(popped_value == 2);
    }
    SECTION("get successful >1 value")
    {
        bank.put(1, 3);
        std::vector<int> result = bank.get(1);
        REQUIRE(result.size() == 2);
        std::vector<int> expected_result;
        expected_result.push_back(2);
        expected_result.push_back(3);
        std::sort(expected_result.begin(), expected_result.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected_result);
    }

    SECTION("get failed")
    {
        std::vector<int> values = bank.get(2);
        REQUIRE(values.empty());
    }
}

TEST_CASE("Bank<int, int>::get_reverse()")
{
    Bank<int, int> bank;
    bank.put(1, 2);

    SECTION("get_reverse success 1 value")
    {
        std::vector<int> result = bank.get_reverse(2);
        REQUIRE(result.size() == 1);
        int popped_key = result.at(0);
        REQUIRE(popped_key == 1);
    }

    SECTION("get_reverse success >1 value")
    {
        bank.put(2, 2);
        std::vector<int> result = bank.get_reverse(2);
        REQUIRE(result.size() == 2);
        std::vector<int> expected_result;
        expected_result.push_back(1);
        expected_result.push_back(2);
        std::sort(expected_result.begin(), expected_result.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected_result);
    }
}

TEST_CASE("Bank<int, int>::get_all_keys()")
{
    Bank<int, int> bank;

    SECTION("get_all_keys empty")
    {
        REQUIRE(bank.get_all_keys().empty());
    }

    SECTION("get_all_keys success")
    {
        bank.put(1, 2);
        bank.put(2, 3);
        std::vector<int> expected_result;
        expected_result.push_back(2);
        expected_result.push_back(1);
        std::vector<int> result = bank.get_all_keys();
        std::sort(expected_result.begin(), expected_result.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected_result);
    }
}

TEST_CASE("Bank<int, int>::get_all_values()")
{
     Bank<int, int> bank;

    SECTION("get_all_values empty")
    {
        REQUIRE(bank.get_all_values().empty());
    }

    SECTION("get_all_values success")
    {
        bank.put(1, 2);
        bank.put(2, 3);
        std::vector<int> expected_result;
        expected_result.push_back(3);
        expected_result.push_back(2);
        std::vector<int> result = bank.get_all_values();
        std::sort(expected_result.begin(), expected_result.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected_result);
    }
}

TEST_CASE("Bank<int, int>::empty()")
{
    Bank<int, int> bank;
    
    SECTION("empty true")
    {
        REQUIRE(bank.empty());
    }

    SECTION("empty false")
    {
        bank.put(1, 2);
        REQUIRE_FALSE(bank.empty());
    }
}

TEST_CASE("Bank<int, int>::copy()")
{
    Bank<int, int> bank;
    SECTION("empty copy")
    {
        std::unordered_map<int, std::vector<int>> hashmap = bank.copy();
        REQUIRE(hashmap.empty());
    }
    SECTION("deep copy")
    {
    bank.put(1,2);
    std::unordered_map<int, std::vector<int>> hashmap = bank.copy();
    REQUIRE(hashmap.size() == 1);
    bank.put(2,3);
    REQUIRE(hashmap.size() == 1); // test if shallow copy or deep clone
    }
}

TEST_CASE("Bank<int, std::string>")
{
    Bank<int, std::string> bank;
}

TEST_CASE("Bank<std::string, std::string>")
{
    Bank<std::string, std::string> bank;
}
