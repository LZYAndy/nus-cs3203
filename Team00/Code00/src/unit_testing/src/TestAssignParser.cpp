#include "catch.hpp"
#include "AssignParser.h"
#include "pql_dto/Entity.h"
#include "ErrorMessages.h"

TEST_CASE("AssignParser")
{
    PKB pkb;
    SECTION("Success test case")
    {
        Statement stmt = Statement(EntityType::ASSIGN, 2, "a1 = 2;");
        REQUIRE_NOTHROW(AssignParser (pkb, stmt, "Parent"));
        stmt = Statement(EntityType::ASSIGN, 2, "a = 2 + b;");
        REQUIRE_NOTHROW(AssignParser (pkb, stmt, "Parent"));
    }

    SECTION("Invalid assign statement")
    {
        Statement stmt = Statement(EntityType::ASSIGN, 1, "10");
        REQUIRE_THROWS_WITH(AssignParser (pkb, stmt, "Parent"), error_messages::invalid_assign_statement);
    }

    SECTION("Invalid statement type")
    {
        Statement stmt = Statement(EntityType::ANY, 1, "a = 1;");
        REQUIRE_THROWS_WITH(AssignParser (pkb, stmt, "Parent"), error_messages::invalid_assign_type);
    }
}
