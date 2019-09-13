#include "catch.hpp"
#include "ParentBank.h"

TEST_CASE("Init Parent Bank")
{
    ParentBank parent_bank;
    parent_bank.put(1, 2);
    REQUIRE(parent_bank.is_parent(1, 2) == true);
}