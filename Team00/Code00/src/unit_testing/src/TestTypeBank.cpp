#include "catch.hpp"
#include "TypeBank.h"

TEST_CASE("TypeBank::get_statement_type()")
{
    TypeBank type_bank;
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(3, EntityType::IF);
    type_bank.insert_type(4, EntityType::PRINT);
    type_bank.insert_type(5, EntityType::READ);
    type_bank.insert_type(6, EntityType::WHILE);

    SECTION("get_statement_type success")
    {
        REQUIRE(type_bank.get_statement_type(1) == EntityType::ASSIGN);
        REQUIRE(type_bank.get_statement_type(2) == EntityType::CALL);
        REQUIRE(type_bank.get_statement_type(3) == EntityType::IF);
        REQUIRE(type_bank.get_statement_type(4) == EntityType::PRINT);
        REQUIRE(type_bank.get_statement_type(5) == EntityType::READ);
        REQUIRE(type_bank.get_statement_type(6) == EntityType::WHILE);
    }

    SECTION("get_statement_type fail")
    {
        REQUIRE(type_bank.get_statement_type(0) == EntityType::INVALID);
        REQUIRE(type_bank.get_statement_type(7) == EntityType::INVALID);
    }
}

TEST_CASE("TypeBank::get_all_of_type()")
{
    TypeBank type_bank;
    type_bank.insert_type(1, EntityType::ASSIGN);
    type_bank.insert_type(2, EntityType::CALL);
    type_bank.insert_type(3, EntityType::IF);
    type_bank.insert_type(5, EntityType::READ);
    type_bank.insert_type(6, EntityType::WHILE);

    SECTION("get_all_of_type 1 stmt")
    {
        std::vector<int> result = type_bank.get_all_of_type(EntityType::ASSIGN);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("get_all_of_type 1 stmt with duplicate insert")
    {
        type_bank.insert_type(1, EntityType::ASSIGN);
        std::vector<int> result = type_bank.get_all_of_type(EntityType::ASSIGN);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("get_all_of_type >1 stmts")
    {
        type_bank.insert_type(7, EntityType::ASSIGN);
        std::vector<int> result = type_bank.get_all_of_type(EntityType::ASSIGN);
        std::vector<int> expected({1, 7});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 2);
        REQUIRE(result == expected);
    }

    SECTION("get_all_of_type 0 stmt")
    {
        REQUIRE(type_bank.get_all_of_type(EntityType::PRINT).empty());
        REQUIRE(type_bank.get_all_of_type(EntityType::INVALID).empty());
    }
}

TEST_CASE("TypeBank::copy()")
{
    TypeBank type_bank;

    SECTION("empty copy")
    {
        std::unordered_map<int, std::vector<EntityType>> hashmap = type_bank.copy();
        REQUIRE(hashmap.empty());
    }
    SECTION("deep copy")
    {
        type_bank.insert_type(7, EntityType::ASSIGN);
        std::unordered_map<int, std::vector<EntityType>> hashmap = type_bank.copy();
        REQUIRE(hashmap.size() == 1);
        type_bank.insert_type(8, EntityType::ASSIGN);
        REQUIRE(hashmap.size() == 1); // test if shallow copy or deep clone
    }
}
