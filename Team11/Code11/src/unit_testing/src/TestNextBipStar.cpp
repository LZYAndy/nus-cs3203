#include "catch.hpp"
#include "NextBipStarCompute.h"

TEST_CASE("NextBipStarCompute::is_next_bip_star")
{
    NextBipBank next_bip_bank;
    NextBank next_bank;
    TypeBank type_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);

    NextBipStarCompute next_bip_star_compute(&next_bip_bank, &type_bank, &next_bank);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);

    SECTION("fail")
    {
        REQUIRE_FALSE(next_bip_star_compute.is_next_bip_star(4, 2));
        REQUIRE_FALSE(next_bip_star_compute.is_next_bip_star(1, 9));
        REQUIRE_FALSE(next_bip_star_compute.is_next_bip_star(8, 7));
    }

    SECTION("success")
    {
        REQUIRE(next_bip_star_compute.is_next_bip_star(1, 7));
        REQUIRE(next_bip_star_compute.is_next_bip_star(4, 7));
        REQUIRE(next_bip_star_compute.is_next_bip_star(5, 5));
        REQUIRE(next_bip_star_compute.is_next_bip_star(4, 4));
        REQUIRE(next_bip_star_compute.is_next_bip_star(5, 9));
        REQUIRE(next_bip_star_compute.is_next_bip_star(5, 9));
    }
}

TEST_CASE("NextBipStarCompute::get_next_bip_star")
{
    NextBipBank next_bip_bank;
    NextBank next_bank;
    TypeBank type_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    NextBipStarCompute next_bip_star_compute(&next_bip_bank, &type_bank, &next_bank);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);

    SECTION("empty")
    {
        REQUIRE(next_bip_star_compute.get_next_bip_star(7).empty());
    }

    SECTION(">1")
    {
        std::vector<int> result = next_bip_star_compute.get_next_bip_star(5);
        REQUIRE(result.size() == 5);
        std::vector<int> expected({9, 4, 5, 6, 7});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);

        std::vector<int> result1 = next_bip_star_compute.get_next_bip_star(2);
        REQUIRE(result1.size() == 4);
        std::vector<int> expected1({ 4, 5, 6, 7});
        std::sort(result1.begin(), result1.end());
        std::sort(expected1.begin(), expected1.end());
        REQUIRE(expected1 == result1);
    }
}

TEST_CASE("NextBipStarCompute::get_previous_bip_star")
{
    NextBipBank next_bip_bank;
    NextBank next_bank;
    TypeBank type_bank;
    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    NextBipStarCompute next_bip_star_compute(&next_bip_bank, &type_bank, &next_bank);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);

    SECTION("empty")
    {
        REQUIRE(next_bip_star_compute.get_previous_bip_star(8).empty());
    }

    SECTION(">1")
    {
        std::vector<int> result = next_bip_star_compute.get_previous_bip_star(9);
        REQUIRE(result.size() == 3);
        std::vector<int> expected({4, 5, 8});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);

        std::vector<int> result1 = next_bip_star_compute.get_previous_bip_star(4);
        REQUIRE(result1.size() == 5);
        std::vector<int> expected1({1, 2, 8, 5, 4});
        std::sort(result1.begin(), result1.end());
        std::sort(expected1.begin(), expected1.end());
        REQUIRE(expected1 == result1);
    }
}

TEST_CASE("NextBipStarCompute::get_all_next_bip_star_relationship")
{
    NextBipBank next_bip_bank;
    TypeBank type_bank;
    NextBank next_bank;
    NextBipStarCompute next_bip_star_compute(&next_bip_bank, &type_bank, &next_bank);

    SECTION("empty")
    {
        REQUIRE(next_bip_star_compute.get_all_next_bip_star_relationship().empty());
    }

    next_bip_bank.insert_next_bip(1, 2);
    next_bip_bank.insert_next_bip(2, 4);
    next_bip_bank.insert_next_bip(4, 5);
    next_bip_bank.insert_next_bip(4, 6);
    next_bip_bank.insert_next_bip(5, 4);
    next_bip_bank.insert_next_bip(6, 7);
    next_bip_bank.insert_next_bip(8, 4);
    next_bip_bank.insert_next_bip(4, 9);
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(4, EntityType::WHILE);
    type_bank.insert_type(5, EntityType::ASSIGN);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::ASSIGN);
    type_bank.insert_type(8, EntityType::CALL);
    type_bank.insert_type(9, EntityType::ASSIGN);
    next_bip_bank.insert_call_ingress_egress(2, 6);
    next_bip_bank.insert_call_ingress_egress(8, 9);

    SECTION(">1")
    {
        std::unordered_map<int, std::vector<int>> result = next_bip_star_compute.get_all_next_bip_star_relationship();
        std::unordered_map<int, std::vector<int>> expected;
        expected.insert({1, {2, 4, 5, 6, 7}});
        expected.insert({2, {4, 5, 6, 7}});
        expected.insert({4, {4, 5, 6, 7, 9}});
        expected.insert({5, {4, 5, 6, 7, 9}});
        expected.insert({6, {7}});
        expected.insert({8, {4, 5, 9}});
        REQUIRE(result.size() == 6);
        for (auto result_pair : result)
        {
            auto result_values = result_pair.second;
            auto expected_values = expected[result_pair.first];
            std::sort(result_values.begin(), result_values.end());
            std::sort(expected_values.begin(), expected_values.end());
            REQUIRE(expected_values == result_values);
        }
    }
}
