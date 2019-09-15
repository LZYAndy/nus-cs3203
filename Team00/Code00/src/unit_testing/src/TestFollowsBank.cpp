#include "catch.hpp"
#include "FollowsBank.h"

TEST_CASE("FollowBank::isfollows()")
{
    FollowsBank follows_bank;
    follows_bank.put(1, 2);

    SECTION("is_follow true")
    {
        REQUIRE(follows_bank.is_follows(1,2));
    }

    SECTION("is_follow false")
    {
        REQUIRE_FALSE(follows_bank.is_follows(1, 3));
        REQUIRE_FALSE(follows_bank.is_follows(2, 3));
    }
}
