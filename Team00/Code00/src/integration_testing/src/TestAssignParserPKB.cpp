#include "catch.hpp"
#include "AssignParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("AssignParser integration with PKB")
{
    SECTION("get_all_variables")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 2, "a123 = a0 + (2 + BC)");
        AssignParser (pkb, stmt, "Parent");
        std::unordered_set<std::string> result = pkb.get_all_variables();
        std::unordered_set<std::string> expected({"a123", "a0", "BC"});
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (procedure)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c + d");
        AssignParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_modified_by_procedure("Proc1");
        std::vector<std::string> expected({"a"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (statement)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d");
        AssignParser (pkb, stmt, "2");
        std::vector<std::string> result = pkb.get_modified_by_statement(3);
        std::vector<std::string> expected({"a"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("!insert_assign")
    {
//        PKB pkb;
//        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d");
//        AssignParser (pkb, stmt, "2");
//        std::vector<int> result = pkb.get_assign_pattern_contains("a","b+c*d");
//        std::vector<int> expected({});
//        for (int i : result)
//            std::cout << i << "\n";
//        REQUIRE(result.size() == 1);
//        REQUIRE(result == expected);
    }
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::ASSIGN, 3, "a = b + c * d");
        AssignParser (pkb, stmt, "2");
        int result = pkb.get_parent(3);
        int expected = 2;
        REQUIRE(result == expected);
    }
    SECTION("!insert_uses (procedure)")
    {
//        PKB pkb;
//        Statement stmt = Statement(EntityType::ASSIGN, 1, "a = e + f * g");
//        AssignParser (pkb, stmt, "Proc1");
//        std::vector<std::string> result = pkb.get_used_by_procedure("Proc1");
//        for (std::string i : result)
//            std::cout << i << "\n";
//        std::vector<std::string> expected({"e", "f", "g"});
//        REQUIRE(result == expected);
//
    }
}
