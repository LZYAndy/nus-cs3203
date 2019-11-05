#include "catch.hpp"
#include "AffectsBipCompute.h"

TEST_CASE("AffectsBipCompute::is_affects_bip()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    SECTION("false")
    {
        REQUIRE_FALSE(affects_bip_compute.is_affects_bip(1, 9));
        REQUIRE_FALSE(affects_bip_compute.is_affects_bip(7, 1));
    }

    SECTION("true")
    {
        REQUIRE(affects_bip_compute.is_affects_bip(5, 5));
        REQUIRE(affects_bip_compute.is_affects_bip(1, 6));
        REQUIRE(affects_bip_compute.is_affects_bip(6, 7));
        REQUIRE(affects_bip_compute.is_affects_bip(10, 9));
    }
}

TEST_CASE("AffectsBipCompute::get_all_assigns_affects_bip()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    SECTION("empty")
    {
        REQUIRE(affects_bip_compute.get_all_assigns_affects_bip().empty());
    }
    
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION(">1")
    {
       std::vector<int> result = affects_bip_compute.get_all_assigns_affects_bip();
         REQUIRE(result.size() == 4);
        std::vector<int> expected({1, 5, 6, 10});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsBipCompute::get_all_assigns_affected_bip()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    SECTION("empty")
    {
        REQUIRE(affects_bip_compute.get_all_assigns_affected_bip().empty());
    }

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION(">1")
    {
        std::vector<int> result = affects_bip_compute.get_all_assigns_affected_bip();
        REQUIRE(result.size() == 4);
        std::vector<int> expected({5, 6, 7, 9});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsBipCompute::get_all_affects_bip_relationship()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    SECTION("empty")
    {
        REQUIRE(affects_bip_compute.get_all_affects_bip_relationship().empty());
    }

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION(">1")
    {
        std::unordered_map<int, std::vector<int>> result = affects_bip_compute.get_all_affects_bip_relationship();
        REQUIRE(result.size() == 4);
        std::unordered_map<int, std::vector<int>>  expected;
        expected.insert({1, {6}});
        expected.insert({5, {5}});
        expected.insert({6, {7}});
        expected.insert({10, {9}});
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsBipCompute::does_affects_bip_exist()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    SECTION("false")
    {
        REQUIRE_FALSE(affects_bip_compute.does_affects_bip_exist());
    }

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION("true")
    {
        REQUIRE(affects_bip_compute.does_affects_bip_exist());
    }
}

TEST_CASE("AffectsBipCompute::get_assigns_affected_bip_by()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION("empty")
    {
        REQUIRE(affects_bip_compute.get_assigns_affected_bip_by(2).empty());
        REQUIRE(affects_bip_compute.get_assigns_affected_bip_by(9).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(affects_bip_compute.get_assigns_affected_bip_by(10) == std::vector<int>({9}));
        REQUIRE(affects_bip_compute.get_assigns_affected_bip_by(5) == std::vector<int>({5}));
    }
}

TEST_CASE("AffectsBipCompute::get_assigns_affects_bip()")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    AffectsBipCompute affects_bip_compute(&next_bip_bank, &modifies_bank, &uses_bank, &type_bank);

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    next_bip_bank.insert_next_bip(10, 8);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);
    modifies_bank.insert_modifies(1, "one");
    modifies_bank.insert_modifies(5, "five");
    modifies_bank.insert_modifies(6, "yellow");
    modifies_bank.insert_modifies(7, "one");
    modifies_bank.insert_modifies(9, "one");
    modifies_bank.insert_modifies(10, "red");
    uses_bank.insert_uses(1, "yellow");
    uses_bank.insert_uses(5, "five");
    uses_bank.insert_uses(6, "one");
    uses_bank.insert_uses(7, "yellow");
    uses_bank.insert_uses(9, "red");
    uses_bank.insert_uses(9, "one");

    uses_bank.insert_uses(2, "five");
    uses_bank.insert_uses(4, "five");
    uses_bank.insert_uses(8, "five");
    modifies_bank.insert_modifies(2, "five");
    modifies_bank.insert_modifies(4, "five");
    modifies_bank.insert_modifies(8, "five");


    SECTION("empty")
    {
        REQUIRE(affects_bip_compute.get_assigns_affects_bip(2).empty());
        REQUIRE(affects_bip_compute.get_assigns_affects_bip(10).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(affects_bip_compute.get_assigns_affects_bip(9) == std::vector<int>({10}));
        REQUIRE(affects_bip_compute.get_assigns_affects_bip(5) == std::vector<int>({5}));
    }
}