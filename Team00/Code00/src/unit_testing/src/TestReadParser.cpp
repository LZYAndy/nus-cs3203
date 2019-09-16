#include "catch.hpp"
#include "ReadParser.h"

TEST_CASE("ReadParser")
{
REQUIRE_THROWS_WITH(ReadParser(PKB (), Statement(EntityType::READ, 1, "x"), "parent"), "Invalid read statement");
REQUIRE_THROWS_WITH(ReadParser(PKB (), Statement(EntityType::READ, 1, "read "), "parent"), "Invalid read statement");
REQUIRE_THROWS_WITH(ReadParser(PKB (), Statement(EntityType::READ, 1, "read a_"), "parent"), "Invalid read statement");
REQUIRE_THROWS_WITH(ReadParser(PKB (), Statement(EntityType::READ, 1, "read a a"), "parent"), "Invalid read statement");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::READ, 1, "read x"), "parent");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::READ, 1, " read x1a "), "0");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::READ, 1, "       read            x            "), "0");
}
