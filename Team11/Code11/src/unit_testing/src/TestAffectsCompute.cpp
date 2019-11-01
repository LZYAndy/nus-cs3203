#include <AffectsCompute.h>
#include "catch.hpp"

TEST_CASE("AffectsCompute::get_all_assigns_affect()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;
    std::vector<int> result;
    std::vector<int> expected;

    SECTION("return 0 statement")
    {
        result = affects.get_all_assigns_affect(15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
    }

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");
    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return more than 0 statements")
    {
        result = affects.get_all_assigns_affect(15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 8);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(4);
        expected.push_back(6);
        expected.push_back(8);
        expected.push_back(9);
        expected.push_back(10);
        expected.push_back(11);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsCompute::get_assigns_affect()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;
    std::vector<int> result;
    std::vector<int> expected;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");
    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return 0 statement")
    {
        result = affects.get_assigns_affect(1, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
        result = affects.get_assigns_affect(5, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = affects.get_assigns_affect(11, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 10);
    }

    SECTION("return more than 1 statement")
    {
        result = affects.get_assigns_affect(4, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 2);
        expected.push_back(1);
        expected.push_back(4);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);

        expected.pop_back();
        expected.pop_back();
        result = affects.get_assigns_affect(12, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 5);
        expected.push_back(1);
        expected.push_back(4);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(11);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsCompute::get_all_affects_relationship()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;
    std::vector<int> affected1;
    affected1.push_back(4);
    affected1.push_back(8);
    affected1.push_back(10);
    affected1.push_back(12);
    std::vector<int> affected2;
    affected2.push_back(6);
    affected2.push_back(10);
    std::vector<int> affected4;
    affected4.push_back(4);
    affected4.push_back(8);
    affected4.push_back(10);
    affected4.push_back(12);
    std::vector<int> affected6;
    affected6.push_back(6);
    affected6.push_back(10);
    std::vector<int> affected8;
    affected8.push_back(10);
    affected8.push_back(12);
    std::vector<int> affected9;
    affected9.push_back(10);
    std::vector<int> affected10;
    affected10.push_back(11);
    affected10.push_back(12);
    std::vector<int> affected11;
    affected11.push_back(12);

    std::unordered_map<int, std::vector<int>> result;
    std::unordered_map<int, std::vector<int>> expected;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");

    SECTION("return empty map")
    {
        result = affects.get_all_affects_relationship(2, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
    }

    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return non-empty map")
    {
        result = affects.get_all_affects_relationship(15, next_bank, modifies_bank, uses_bank, type_bank);
        expected.emplace(1, affected1);
        expected.emplace(2, affected2);
        expected.emplace(4, affected4);
        expected.emplace(6, affected6);
        expected.emplace(8, affected8);
        expected.emplace(9, affected9);
        expected.emplace(10, affected10);
        expected.emplace(11, affected11);
        for (int i = 1; i <= 15; i++)
        {
            if(result.find(i) != result.end())
            {
                std::sort(expected.at(i).begin(), expected.at(i).end());
                std::sort(result.at(i).begin(), result.at(i).end());
                REQUIRE(expected.at(i) == result.at(i));
            }
        }
    }
}

TEST_CASE("AffectsCompute::get_all_assigns_affected()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;
    std::vector<int> result;
    std::vector<int> expected;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");

    SECTION("return 0 statement")
    {
        result = affects.get_all_assigns_affected(2, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
    }

    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return more than 0 statement")
    {
        result = affects.get_all_assigns_affected(15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 6);
        expected.push_back(4);
        expected.push_back(6);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(11);
        expected.push_back(12);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsCompute::get_assigns_affected_by()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;
    std::vector<int> result;
    std::vector<int> expected;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");

    SECTION("return 0 statement")
    {
        result = affects.get_assigns_affected_by(1, 2, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.empty());
    }

    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return more than 0 statements")
    {
        result = affects.get_assigns_affected_by(1, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 4);
        expected.push_back(4);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(12);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);

        result = affects.get_assigns_affected_by(4, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 4);
        REQUIRE(expected == result);
        expected.clear();

        result = affects.get_assigns_affected_by(6, 15, next_bank, modifies_bank, uses_bank, type_bank);
        REQUIRE(result.size() == 2);
        expected.push_back(6);
        expected.push_back(10);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("AffectsCompute::does_affects_exist()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");

    SECTION("return false")
    {
        REQUIRE_FALSE(affects.does_affects_exist(2, next_bank, modifies_bank, uses_bank, type_bank));
    }

    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return true")
    {
        REQUIRE(affects.does_affects_exist(15, next_bank, modifies_bank, uses_bank, type_bank));
    }
}

TEST_CASE("AffectsCompute::is_affects()")
{
    NextBank next_bank;
    ModifiesBank modifies_bank;
    UsesBank uses_bank;
    TypeBank type_bank;
    AffectsCompute affects;

    next_bank.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    next_bank.insert_next(2, 3);
    next_bank.insert_next(3, 4);
    next_bank.insert_next(3, 7);
    next_bank.insert_next(4, 5);
    next_bank.insert_next(5, 6);
    next_bank.insert_next(6, 3);
    next_bank.insert_next(7, 8);
    next_bank.insert_next(7, 9);
    next_bank.insert_next(8, 10);
    next_bank.insert_next(9, 10);
    next_bank.insert_next(10, 11);
    next_bank.insert_next(11, 12);
    next_bank.insert_next(13, 14);
    next_bank.insert_next(14, 15);

    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::ASSIGN);
    type_bank.insert_type(3, EntityType::WHILE);
    type_bank.insert_type(4, EntityType::ASSIGN);
    type_bank.insert_type(5, EntityType::CALL);
    type_bank.insert_type(6, EntityType::ASSIGN);
    type_bank.insert_type(7, EntityType::IF);
    type_bank.insert_type(8, EntityType::ASSIGN);
    type_bank.insert_type(9, EntityType::ASSIGN);
    type_bank.insert_type(10, EntityType::ASSIGN);
    type_bank.insert_type(11, EntityType::ASSIGN);
    type_bank.insert_type(12, EntityType::ASSIGN);
    type_bank.insert_type(13, EntityType::ASSIGN);
    type_bank.insert_type(14, EntityType::ASSIGN);
    type_bank.insert_type(15, EntityType::PRINT);

    modifies_bank.insert_modifies(1, "x");
    modifies_bank.insert_modifies(2, "i");
    modifies_bank.insert_modifies(3, "x");
    modifies_bank.insert_modifies(3, "i");
    modifies_bank.insert_modifies(4, "x");
    modifies_bank.insert_modifies(6, "i");
    modifies_bank.insert_modifies(7, "x");
    modifies_bank.insert_modifies(7, "z");
    modifies_bank.insert_modifies(8, "x");
    modifies_bank.insert_modifies(9, "z");
    modifies_bank.insert_modifies(10, "z");
    modifies_bank.insert_modifies(11, "y");
    modifies_bank.insert_modifies(12, "x");
    modifies_bank.insert_modifies(13, "z");
    modifies_bank.insert_modifies(14, "v");
    modifies_bank.insert_modifies("Third", "z");
    modifies_bank.insert_modifies("Third", "v");

    uses_bank.insert_uses(3, "i");
    uses_bank.insert_uses(3, "x");
    uses_bank.insert_uses(3, "y");
    uses_bank.insert_uses(3, "v");
    uses_bank.insert_uses(4, "x");
    uses_bank.insert_uses(4, "y");
    uses_bank.insert_uses(5, "v");
    uses_bank.insert_uses(6, "i");
    uses_bank.insert_uses(7, "x");
    uses_bank.insert_uses(8, "x");
    uses_bank.insert_uses(10, "z");
    uses_bank.insert_uses(10, "x");
    uses_bank.insert_uses(10, "i");
    uses_bank.insert_uses(11, "z");
    uses_bank.insert_uses(12, "x");
    uses_bank.insert_uses(12, "y");
    uses_bank.insert_uses(12, "z");
    uses_bank.insert_uses(15, "v");

    SECTION("return false")
    {
        REQUIRE_FALSE(affects.is_affects(9, 11, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE_FALSE(affects.is_affects(9, 12, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE_FALSE(affects.is_affects(2, 3, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE_FALSE(affects.is_affects(9, 6, next_bank, modifies_bank, uses_bank, type_bank));
    }

    SECTION("return true")
    {
        REQUIRE(affects.is_affects(2, 6, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(4, 8, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(4, 10, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(6, 6, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(1, 4, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(1, 8, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(1, 10, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(1, 12, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(2, 10, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(9, 10, next_bank, modifies_bank, uses_bank, type_bank));
        REQUIRE(affects.is_affects(4, 4, next_bank, modifies_bank, uses_bank, type_bank));
    }
}
