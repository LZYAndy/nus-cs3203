#include "catch.hpp"
#include "DesignExtractor.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "CallsBank.h"
#include "CallsStarBank.h"

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
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        REQUIRE_FALSE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE_FALSE(parent_star_bank.does_parent_star_exist());
        REQUIRE(uses_bank.does_uses_exist());
        REQUIRE(modifies_bank.does_modifies_exist());
    }

    SECTION("extract 1 stmt FollowsBank")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        uses_bank.insert_uses(2, "v");
        modifies_bank.insert_modifies(2, "v");
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 1);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 1);
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 1);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);
    }

    SECTION("extract >1 stmt ParentBank 3-level depth")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(2, 3);
        uses_bank.insert_uses(3, "v");
        modifies_bank.insert_modifies(3, "v");
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 2);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 2);
        std::vector<int> result_parent = parent_star_bank.get_parent_star(3);
        std::vector<int> expected_parent({2, 1});
        std::sort(result_parent.begin(), result_parent.end());
        std::sort(expected_parent.begin(), expected_parent.end());
        REQUIRE(result_parent == expected_parent);
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 1);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);

        std::vector<int> result_child = parent_star_bank.get_children_star(1);
        std::vector<int> expected_child({2, 3});
        std::sort(result_child.begin(), result_child.end());
        std::sort(expected_child.begin(), expected_child.end());
        REQUIRE(result_child == expected_child);
    }

    SECTION("extract >1 stmt ParentBank 4-level depth")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(1, 5);
        parent_bank.insert_parent(2, 3);
        parent_bank.insert_parent(3, 4);
        parent_bank.insert_parent(5, 6);
        uses_bank.insert_uses(5, "t");
        modifies_bank.insert_modifies(5, "v");
        uses_bank.insert_uses(6, "v");
        modifies_bank.insert_modifies(6, "v");
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 4);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 5);
        std::vector<int> result = parent_star_bank.get_parent_star(6);
        std::vector<int> expected({1, 5});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 2);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);
        REQUIRE(result == expected);

        std::vector<int> result_child = parent_star_bank.get_children_star(1);
        std::vector<int> expected_child({2, 3, 4, 5, 6});
        std::sort(result_child.begin(), result_child.end());
        std::sort(expected_child.begin(), expected_child.end());
        REQUIRE(result_child == expected_child);
    }
}

TEST_CASE("DesignExtractor::extract_calls_star()")
{
    CallsBank calls_bank;
    CallsStarBank calls_star_bank;

    calls_bank.insert_calls("a", "b");
    calls_bank.insert_calls("b", "c");
    calls_bank.insert_calls("c", "d");
    calls_bank.insert_calls("s", "e");
    calls_bank.insert_calls("e", "x");
    calls_bank.insert_calls("x", "d");

    REQUIRE(DesignExtractor::extract_calls_star(calls_bank, calls_star_bank));
    REQUIRE(calls_star_bank.is_calls_star("a", "d"));

}
