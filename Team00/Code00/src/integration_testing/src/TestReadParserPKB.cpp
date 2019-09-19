#include "catch.hpp"
#include "ReadParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("ReadParser integration with PKB")
{
    SECTION("insert_variable")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::READ, 5, "read a101");
        ReadParser (pkb, stmt, "Parent");
        std::unordered_set<std::string> result = pkb.get_all_variables();
        std::unordered_set<std::string> expected({"a101"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (procedure)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::READ, 3, "  read a00m ");
        ReadParser (pkb, stmt, "Proc1");
        std::vector<std::string> result = pkb.get_modified_by_procedure("Proc1");
        std::vector<std::string> expected({"a00m "});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_modifies (statement)")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::READ, 30, " read a11n");
        ReadParser (pkb, stmt, "10");
        std::vector<std::string> result = pkb.get_modified_by_statement(30);
        std::vector<std::string> expected({"a11n"});
        REQUIRE(result.size() == 1);
        REQUIRE(result == expected);
    }
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::READ, 20, "read D0l2Z");
        ReadParser (pkb, stmt, "10");
        int result = pkb.get_parent(20);
        int expected = 10;
        REQUIRE(result == expected);
    }
    SECTION("!insert_type")
    {
    }
}
