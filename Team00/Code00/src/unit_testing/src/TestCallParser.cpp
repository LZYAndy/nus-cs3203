#include "catch.hpp"
#include "CallParser.h"
#include "ErrorMessages.h"

TEST_CASE("CallParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "x"), "parent"), error_messages::invalid_call_statement);
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call "), "parent"), error_messages::invalid_call_statement);
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call a_"), "parent"), error_messages::invalid_call_statement);
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::CALL, 1, "call a a"), "parent"), error_messages::invalid_call_statement);
    REQUIRE_THROWS_WITH(CallParser(pkb, Statement(EntityType::PRINT, 1, "call a;"), "parent"), error_messages::invalid_call_type);
    REQUIRE_NOTHROW(CallParser(pkb, Statement(EntityType::CALL, 1, "call x;"), "parent"));
    REQUIRE_NOTHROW(CallParser(pkb, Statement(EntityType::CALL, 1, " call x1a ;"), "0"));
    REQUIRE_NOTHROW(CallParser(pkb, Statement(EntityType::CALL, 1, "       call            x           ;"), "0"));
}
