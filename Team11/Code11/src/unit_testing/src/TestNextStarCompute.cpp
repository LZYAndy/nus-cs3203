#include "catch.hpp"
#include <PKB.h>

TEST_CASE("get_statements_previous_star()")
{
    PKB pkb;
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(4, 7);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 8);
    pkb.insert_next(7, 8);
    pkb.insert_next(8, 3);
    std::vector<int> result;
    std::vector<int> expected;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_previous_star(1);
        REQUIRE(result.size() == 0);
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_previous_star(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_previous_star(9);
        REQUIRE(result.size() == 8);
        for(int i = 1; i<= 8; i++)
        {
            expected.push_back(i);
        }
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}