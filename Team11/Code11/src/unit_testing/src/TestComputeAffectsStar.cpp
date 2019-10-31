#include "catch.hpp"
#include "PKB.h"
#include "ComputeAffectsStar.h"

TEST_CASE("ComputeAffectsStar::is_affects()")
{
    ComputeAffectsStar compute_affects_star;
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");
    pkb.insert_while(4, {"x"});
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_parent(4, 5);
    pkb.insert_parent(4, 6);
    pkb.insert_assign(5, "forever", "loop");
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_modifies(5, "forever");
    pkb.insert_uses(5, "loop");
    pkb.insert_assign(6, "loop", "+ is true");
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_modifies(6, "loop");
    pkb.insert_uses(6, "is");
    pkb.insert_uses(6, "true");

    SECTION("fails")
    {
        REQUIRE_FALSE(compute_affects_star.is_affects_star(pkb, 1, 2));
        REQUIRE_FALSE(compute_affects_star.is_affects_star(pkb, 5, 2));
    }

    SECTION("success")
    {
        REQUIRE(compute_affects_star.is_affects_star(pkb, 1, 2));
        REQUIRE(compute_affects_star.is_affects_star(pkb, 2, 3));
        REQUIRE(compute_affects_star.is_affects_star(pkb, 1, 3));
        REQUIRE(compute_affects_star.is_affects_star(pkb, 5, 6));
        REQUIRE(compute_affects_star.is_affects_star(pkb, 6, 5));
    }
}

TEST_CASE("ComputeAffectsStar::get_affects_star()")
{
    ComputeAffectsStar compute_affects_star;
    PKB pkb;
    pkb.insert_assign(1, "x", "y + z");
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "ello + x");
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("fails")
    {
        REQUIRE(compute_affects_star.get_affects_star(pkb, 3).empty());
    }

    SECTION("success")
    {
        std::vector<int> result = compute_affects_star.get_affects_star(pkb, 1);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}


TEST_CASE("ComputeAffectsStar::get_affected_star()")
{
    ComputeAffectsStar compute_affects_star;
    PKB pkb;
    pkb.insert_assign(1, "x", "y + z");
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "ello + x");
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("fails")
    {
        REQUIRE(compute_affects_star.get_affected_star(pkb, 1).empty());
    }

    SECTION("success")
    {
        std::vector<int> result = compute_affects_star.get_affected_star(pkb, 3);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(1);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("ComputeAffectsStar::get_all_affects_star_relationship()")
{
    ComputeAffectsStar compute_affects_star;
    PKB pkb;

    SECTION("fails")
    {
        REQUIRE(compute_affects_star.get_all_affects_star_relationship(pkb).empty());
    }

    pkb.insert_assign(1, "x", "y + z");
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "ello + x");
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("success")
    {
        std::unordered_map<int, ::vector<int>> result = compute_affects_star.get_all_affects_star_relationship(pkb);
        std::unordered_map<int, ::vector<int>> expected;
        expected.insert({1, {2, 3}});
        expected.insert({2, {3}});
        REQUIRE(expected == result);
    }
}