#include "catch.hpp"
#include "ParentStarBank.h"

TEST_CASE("ParentStarBank::is_parent_star")
{
    ParentStarBank parent_star_bank;
    parent_star_bank.insert_parent_star(1, 2);
    parent_star_bank.insert_parent_star(1, 3);
    
    SECTION("is_parent_star true")
    {
        REQUIRE(parent_star_bank.is_parent_star(1, 2));
        REQUIRE(parent_star_bank.is_parent_star(1, 3));
    }

    SECTION("is_parent_star false")
    {
        REQUIRE_FALSE(parent_star_bank.is_parent_star(1, 4));
        REQUIRE_FALSE(parent_star_bank.is_parent_star(2, 3));
    }
}