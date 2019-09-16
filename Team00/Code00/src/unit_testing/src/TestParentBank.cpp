#include "catch.hpp"
#include "ParentBank.h"

TEST_CASE("ParentBank::is_parent()")
{
    ParentBank parent_bank;
    parent_bank.put(1, 2);

    SECTION("is_parent true")
    {
        REQUIRE(parent_bank.is_parent(1, 2));
    }

    SECTION("is_parent false")
    {
        REQUIRE_FALSE(parent_bank.is_parent(1, 3));
        REQUIRE_FALSE(parent_bank.is_parent(2, 1));
    }
}