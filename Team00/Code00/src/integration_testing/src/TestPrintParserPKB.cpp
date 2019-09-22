#include "catch.hpp"
#include "PrintParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("PrintParser integration with PKB")
{
    SECTION("insert_variable")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::PRINT, 5, "print a1;");
        PrintParser (pkb, stmt, "Parent");
        std::unordered_set<std::string> result = pkb.get_all_variables();
        std::unordered_set<std::string> expected({"a1"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_uses (statement)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::PRINT, 20, " print A12b6c;");
        PrintParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_used_by_statement(20);
        std::vector<std::string> expected({"A12b6c"});
        REQUIRE(result == expected);
    }
    SECTION("insert_uses (procedure)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::PRINT, 20, " print A12b     ;");
        PrintParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_used_by_procedure("Proc1");
        std::vector<std::string> expected({"A12b     "});
        REQUIRE(result == expected);
    }
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::PRINT, 20, "print D0p3D;");
        PrintParser (pkb, stmt, "10");
        int result = pkb.get_parent(20);
        int expected = 10;
        REQUIRE(result == expected);
    }
    SECTION("insert_type")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::PRINT, 1, "print a0;");
        PrintParser (pkb, stmt, "Proc1");
        EntityType result = pkb.get_statement_type(1);
        EntityType expected(EntityType::PRINT);
        REQUIRE(result == expected);
    }
}
