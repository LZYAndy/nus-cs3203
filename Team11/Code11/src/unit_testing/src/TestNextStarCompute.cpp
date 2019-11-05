#include "catch.hpp"
#include <NextStarCompute.h>

TEST_CASE("NextStarCompute::get_statements_previous_star()")
{
    NextBank next_bank;
    NextStarCompute next_star_compute;
    next_bank.insert_next(1, 2);
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4); // stmt3 is while
    next_bank.insert_next(3, 9); // stmt9 is the first stmt out of while stmtList
    next_bank.insert_next(4, 5); // stmt4 is if
    next_bank.insert_next(4, 7); // stmt7 is in else
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 8); // stmt8 is not in else
    next_bank.insert_next(7, 8);
    next_bank.insert_next(8, 3);
    std::vector<int> result;
    std::vector<int> expected;

    SECTION("return 0 statement")
    {
        result = next_star_compute.get_statements_previous_star(1, 9, next_bank);
        REQUIRE(result.size() == 0);
    }

    SECTION("return 1 statement")
    {
        result = next_star_compute.get_statements_previous_star(2, 9, next_bank);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statement")
    {
        result = next_star_compute.get_statements_previous_star(9, 9, next_bank);
        REQUIRE(result.size() == 8);
        for(int i = 1; i <= 8; i++)
        {
            expected.push_back(i);
        }
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("NextStarCompute::get_statements_next_star()")
{
    NextBank next_bank;
    NextStarCompute next_star_compute;
    next_bank.insert_next(1, 2);
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 9);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(4, 7);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 8);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(8, 3);
    next_bank.insert_next(9, 10);
    std::vector<int> result;
    std::vector<int> expected;

    SECTION("return 0 statement")
    {
        result = next_star_compute.get_statements_next_star(10, 10, next_bank);
        REQUIRE(result.size() == 0);
    }

    SECTION("return 1 statement")
    {
        result = next_star_compute.get_statements_next_star(9,10, next_bank);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 10);
    }

    SECTION("return more than 1 statement")
    {
        result = next_star_compute.get_statements_next_star(3, 10, next_bank);
        //REQUIRE(result.size() == 8);
        for(int i = 3; i <= 10; i++)
        {
            expected.push_back(i);
        }
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("NextStarCompute::is_next_star()")
{
    NextBank next_bank;
    NextStarCompute next_star_compute;
    next_bank.insert_next(1, 2);
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 9);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(4, 7);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 8);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(8, 3);

    SECTION("return false")
    {
       REQUIRE_FALSE(next_star_compute.is_next_star(2, 1, 9, next_bank));
       REQUIRE_FALSE(next_star_compute.is_next_star(3, 2, 9, next_bank));
       REQUIRE_FALSE(next_star_compute.is_next_star(3, 1, 9, next_bank));
       REQUIRE_FALSE(next_star_compute.is_next_star(10, 9, 9, next_bank));
       REQUIRE_FALSE(next_star_compute.is_next_star(9, 7, 9, next_bank));
    }

    SECTION("return true")
    {
        REQUIRE(next_star_compute.is_next_star(3, 3, 9, next_bank));
        REQUIRE(next_star_compute.is_next_star(5, 5, 9, next_bank));
        REQUIRE(next_star_compute.is_next_star(6, 3, 9, next_bank));
        REQUIRE(next_star_compute.is_next_star(7, 9, 9, next_bank));
        REQUIRE(next_star_compute.is_next_star(5, 7, 9, next_bank));
    }
}

TEST_CASE("NextStarCompute::get_all_next_star_relationship()")
{
    NextBank next_bank;
    NextStarCompute next_star_compute;
    std::unordered_map<int, std::vector<int>> result;
    std::unordered_map<int, std::vector<int>> expected;
    std::vector<int> vec;
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector<int> vec3;

    SECTION("return empty map")
    {
        result = next_star_compute.get_all_next_star_relationship(0, next_bank);
        REQUIRE(result.empty());
    }

    next_bank.insert_next(1, 2);

    SECTION("return map with one pair")
    {
        result = next_star_compute.get_all_next_star_relationship(2, next_bank);
        vec.push_back(2);
        expected.emplace(1, vec);
        REQUIRE(result.size() == 1);
        REQUIRE(result.at(1)[0] == 2);
        REQUIRE(result == expected);
    }

    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 9);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(4, 7);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 8);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(8, 3);
    next_bank.insert_next(9, 10);

    SECTION("return map with more than one pair")
    {
        result = next_star_compute.get_all_next_star_relationship(10, next_bank);
        vec3.push_back(10);
        for(int i = 3; i <= 10; i++)
        {
            vec1.push_back(i);
        }
        for(int i = 2; i <= 10; i++)
        {
            vec2.push_back(i);
        }
        REQUIRE(result.size() == 9);
        for (int i = 1; i <= 9; i++)
        {
        std::sort(result.at(i).begin(), result.at(i).end());
            if(i == 1)
            {
                REQUIRE(result.at(i) == vec2);
            }
            else if(i == 9)
            {
                REQUIRE(result.at(i) == vec3);
            }
            else
            {
                REQUIRE(result.at(i) == vec1);
            }

        }
    }
}
