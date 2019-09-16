#include "catch.hpp"
#include "FollowsStarBank.h"

TEST_CASE("FollowStarBank::isfollows()")
{
    FollowsStarBank follows_star_bank;
    follows_star_bank.insert_follows_star(1, 2);
    follows_star_bank.insert_follows_star(1, 3);

    SECTION("is_follows_star true")
    {
        REQUIRE(follows_star_bank.is_follows_star(1, 2));
        REQUIRE(follows_star_bank.is_follows_star(1, 3));
    }

    SECTION("is_follows_star false")
    {
        REQUIRE_FALSE(follows_star_bank.is_follows_star(1, 4));
        REQUIRE_FALSE(follows_star_bank.is_follows_star(2, 3));
    }
}