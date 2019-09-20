#include "catch.hpp"
#include "CallParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("CallParser integration with PKB")
{
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 25, "call ProcEdur310;");
        CallParser (pkb, stmt, "2");
        int result = pkb.get_parent(25);
        int expected = 2;
        REQUIRE(result == expected);
    }
    SECTION("insert_type")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 1, "call proc9;");
        CallParser (pkb, stmt, "Proc1");
        EntityType result = pkb.get_statement_type(1);
        EntityType expected(EntityType::CALL);
        REQUIRE(result == expected);
    }
}
