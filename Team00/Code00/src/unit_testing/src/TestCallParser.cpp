#include "catch.hpp"
#include "CallParser.h"

TEST_CASE("CallParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "x"), "parent"), "Invalid call statement");
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call "), "parent"), "Invalid call statement");
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call a_"), "parent"), "Invalid call statement");
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call a a"), "parent"), "Invalid call statement");
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::PRINT, 1, "call a"), "parent"), "Incorrect call type");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::CALL, 1, "call x"), "parent");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::CALL, 1, " call x1a "), "0");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::CALL, 1, "       call            x            "), "0");
}
