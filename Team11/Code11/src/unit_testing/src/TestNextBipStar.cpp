#include "catch.hpp"
#include "NextBipStarCompute.h"

TEST_CASE("NextBipStarCompute::is_next_bip_star")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    NextBipStarCompute next_bip_star_compute(next_bip_bank, type_bank);
    next_bip_bank.insert_call_ingress_egress(2, 6);

    SECTION("fail")
    {
        REQUIRE_FALSE(next_bip_star_compute.is_next_bip_star(4, 2));
    }

    SECTION("success")
    {
        REQUIRE(next_bip_star_compute.is_next_bip_star(1, 7));
        REQUIRE(next_bip_star_compute.is_next_bip_star(4, 7));
        REQUIRE(next_bip_star_compute.is_next_bip_star(5, 5));
        REQUIRE(next_bip_star_compute.is_next_bip_star(4, 4));
    }
}