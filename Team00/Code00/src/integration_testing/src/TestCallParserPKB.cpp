#include "catch.hpp"
#include "CallParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("CallParser integration with PKB")
{
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 25, "call ProcEdur310");
        CallParser (pkb, stmt, "2");
        int result = pkb.get_parent(25);
        int expected = 2;
        REQUIRE(result == expected);
    }
    SECTION("!insert_type")
    {
    }
}
