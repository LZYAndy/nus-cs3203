#include "catch.hpp"
#include "PKB.h"
#include "AffectsStarCompute.h"

TEST_CASE("AffectsStarCompute::is_affects_star()")
{
    AffectsStarCompute affects_star_compute;
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");
    pkb.insert_while(4, {"x"});
    pkb.insert_next(3, 4);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_parent(4, 5);
    pkb.insert_parent(4, 6);
    pkb.insert_assign(5, "forever", "loop");
    pkb.insert_next(4, 5);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_modifies(5, "forever");
    pkb.insert_uses(5, "loop");
    pkb.insert_assign(6, "loop", "+ is true");
    pkb.insert_next(5, 6);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_modifies(6, "loop");
    pkb.insert_uses(6, "is");
    pkb.insert_uses(6, "true");
    pkb.insert_next(6, 7);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_assign(6, "true", "forever");
    pkb.insert_modifies(7, "true");
    pkb.insert_uses(7, "forever");
    pkb.insert_next(7, 8);
    pkb.insert_type(8, EntityType::IF);
    pkb.insert_next(8, 9);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_modifies(9, "if");
    pkb.insert_uses(9, "else");
    pkb.insert_next(8, 10);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_modifies(10, "else");
    pkb.insert_uses(10, "if");
    pkb.insert_next(9, 4);
    pkb.insert_next(10, 4);
    pkb.insert_next(4, 11);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_modifies(11, "a");
    pkb.insert_uses(11, "if");

    SECTION("fails")
    {
        REQUIRE_FALSE(affects_star_compute.is_affects_star(pkb, 1, 4, false));
        REQUIRE_FALSE(affects_star_compute.is_affects_star(pkb, 5, 2, false));
    }

    SECTION("success")
    {
        REQUIRE(affects_star_compute.is_affects_star(pkb, 1, 2, false));
        REQUIRE(affects_star_compute.is_affects_star(pkb, 2, 3, false));
        REQUIRE(affects_star_compute.is_affects_star(pkb, 1, 3, false));
        REQUIRE(affects_star_compute.is_affects_star(pkb, 6, 5, false));
        REQUIRE(affects_star_compute.is_affects_star(pkb, 5, 6, false));
        REQUIRE(affects_star_compute.is_affects_star(pkb, 10, 11, false));
    }
}

TEST_CASE("AffectsStarCompute::get_affected_star()")
{
    AffectsStarCompute affects_star_compute;
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");
    pkb.insert_while(4, {"x"});
    pkb.insert_next(3, 4);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_parent(4, 5);
    pkb.insert_parent(4, 6);
    pkb.insert_assign(5, "forever", "loop");
    pkb.insert_next(4, 5);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_modifies(5, "forever");
    pkb.insert_uses(5, "loop");
    pkb.insert_assign(6, "loop", "+ is true");
    pkb.insert_next(5, 6);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_modifies(6, "loop");
    pkb.insert_uses(6, "is");
    pkb.insert_uses(6, "true");
    pkb.insert_next(6, 7);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_assign(6, "true", "forever");
    pkb.insert_modifies(7, "true");
    pkb.insert_uses(7, "forever");
    pkb.insert_next(7, 8);


    SECTION("fails")
    {
        REQUIRE(affects_star_compute.get_affected_star(pkb, 3, false).empty());
    }

    SECTION("success")
    {
        std::vector<int> result = affects_star_compute.get_affected_star(pkb, 1, false);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}


TEST_CASE("AffectsStarCompute::get_affects_star()")
{
    AffectsStarCompute affects_star_compute;
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("fails")
    {
        REQUIRE(affects_star_compute.get_affects_star(pkb, 1).empty());
    }

    SECTION("success")
    {
        std::vector<int> result = affects_star_compute.get_affects_star(pkb, 3);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(1);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsStarCompute::get_all_affects_star_relationship()")
{
    AffectsStarCompute affects_star_compute;
    PKB pkb;

    SECTION("fails")
    {
        REQUIRE(affects_star_compute.get_all_affects_star_relationship(pkb).empty());
    }

    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("success")
    {
        std::unordered_map<int, ::vector<int>> result = affects_star_compute.get_all_affects_star_relationship(pkb);
        std::unordered_map<int, ::vector<int>> expected;
        expected.insert({1, {2, 3}});
        expected.insert({2, {3}});
        REQUIRE(expected == result);
    }
}