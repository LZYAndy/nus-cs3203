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
        REQUIRE_FALSE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE_FALSE(follows_star_bank.does_follows_star_exist());
    }

    SECTION("extract 1 stmt FollowsBank")
    {    
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.insert_follows(1, 2);
        REQUIRE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE(follows_star_bank.does_follows_star_exist());
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 1);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 1);
    }

    SECTION("extract >1 stmt FollowsBank")
    {    
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.insert_follows(1, 2);
        follows_bank.insert_follows(2, 3);
        REQUIRE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE(follows_star_bank.does_follows_star_exist());
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 2);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 2);
        std::vector<int> result = follows_star_bank.get_follows_star(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("DesignExtractor::extract_parent_star()")
{
    SECTION("extract empty FollowsBank")
    {    
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        REQUIRE_FALSE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank);
        REQUIRE_FALSE(parent_star_bank.does_parent_star_exist());
    }

    SECTION("extract 1 stmt FollowsBank")
    {    
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 1);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 1);
    }

    SECTION("extract >1 stmt ParentBank 3-level depth")
    {    
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(2, 3);
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 2);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 2);
        std::vector<int> result = parent_star_bank.get_parent_star(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }

        SECTION("extract >1 stmt ParentBank 4-level depth")
    {    
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(1, 5);
        parent_bank.insert_parent(2, 3);
        parent_bank.insert_parent(3, 4);
        parent_bank.insert_parent(5, 6);
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 4);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 5);
        std::vector<int> result = parent_star_bank.get_parent_star(1);
        std::vector<int> expected({2, 3, 4, 5, 6});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}