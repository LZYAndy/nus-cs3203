#include "catch.hpp"
#include "FollowsBank.h"

TEST_CASE("FollowBank<int, int> Test")
{
    FollowsBank follows_bank;
    std::vector<int> expected_result({1,2});
    follows_bank.put(1,2);
    follows_bank.put(2, 3);
    std::vector<int> result = follows_bank.get_all_keys();
    REQUIRE(result == expected_result);
}
