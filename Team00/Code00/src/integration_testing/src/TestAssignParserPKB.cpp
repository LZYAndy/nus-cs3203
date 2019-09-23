#include "catch.hpp"
#include "AssignParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("AssignParser integration with PKB")
{
    SECTION("insert_variable")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 2, "a123 = a0 + (2 + BC);");
        AssignParser (pkb, stmt, "Parent");
        std::unordered_set<std::string> result = pkb.get_all_variables();
        std::unordered_set<std::string> expected({"a123", "a0", "BC"});
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
    SECTION("insert_constant")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 2, "a = 1 + 20 - 300 / 400 ;");
        AssignParser (pkb, stmt, "Parent");
        std::vector<int> result = pkb.get_all_constants();
        std::vector<int> expected({400, 300, 20, 1});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 4);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (procedure)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c + d;");
        AssignParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_modified_by_procedure("Proc1");
        std::vector<std::string> expected({"a"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (statement)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d;");
        AssignParser (pkb, stmt, "2");
        std::vector<std::string> result = pkb.get_modified_by_statement(3);
        std::vector<std::string> expected({"a"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_assign")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d;");
        AssignParser (pkb, stmt, "2");
        std::vector<int> result = pkb.get_all_assigns();
        std::vector<int> expected({3});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d;");
        AssignParser (pkb, stmt, "2");
        int result = pkb.get_parent(3);
        int expected = 2;
        REQUIRE(result == expected);
    }
    SECTION("insert_uses (statement)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 12, "a = aZ+ 1 + b0 % c0A;");
        AssignParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_used_by_statement(12);
        std::vector<std::string> expected({"aZ", "b0", "c0A"});
        REQUIRE(result == expected);
    }
    SECTION("insert_uses (procedure)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 1, "a = e + f * g;");
        AssignParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_used_by_procedure("Proc1");
        std::vector<std::string> expected({"e", "f", "g"});
        REQUIRE(result == expected);
    }
    SECTION("insert_type")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 1, "a = e + f * g;");
        AssignParser (pkb, stmt, "Proc1");
        EntityType result = pkb.get_statement_type(1);
        EntityType expected(EntityType::ASSIGN);
        REQUIRE(result == expected);
    }
}
