#include "catch.hpp"
#include "DesignExtractor.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"

TEST_CASE("DesignExtractor::extract_follows_star()")
{
    SECTION("extract empty FollowsBank")
    {    
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        REQUIRE(follows_bank.empty());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE(follows_star_bank.empty());
    }

    SECTION("extract 1 stmt FollowsBank")
    {    
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.put(1, 2);
        REQUIRE_FALSE(follows_bank.empty());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE_FALSE(follows_star_bank.empty());
        REQUIRE(follows_star_bank.get_all_keys().size() == 1);
        REQUIRE(follows_star_bank.get_all_values().size() == 1);
    }

    SECTION("extract >1 stmt FollowsBank")
    {    
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.put(1, 2);
        follows_bank.put(2, 3);
        REQUIRE_FALSE(follows_bank.empty());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE_FALSE(follows_star_bank.empty());
        REQUIRE(follows_star_bank.get_all_keys().size() == 2);
        REQUIRE(follows_star_bank.get_all_values().size() == 2);
        std::vector<int> result = follows_star_bank.get(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("DesignExtractor::extract_parent_star()")
{
    SECTION("extract >1 stmt FollowsBank")
    {    
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        parent_bank.put(1, 2);
        parent_bank.put(2, 3);
        REQUIRE_FALSE(parent_bank.empty());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank);
        REQUIRE_FALSE(parent_star_bank.empty());
        REQUIRE(parent_star_bank.get_all_keys().size() == 2);
        REQUIRE(parent_star_bank.get_all_values().size() == 2);
        std::vector<int> result = parent_star_bank.get(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}