#include "catch.hpp"
#include "PrintParser.h"

TEST_CASE("PrintParser")
{
REQUIRE_THROWS_WITH(PrintParser(PKB (), Statement(EntityType::PRINT, 1, "x"), "parent"), "Invalid print statement");
REQUIRE_THROWS_WITH(PrintParser(PKB (), Statement(EntityType::PRINT, 1, "print "), "parent"), "Invalid print statement");
REQUIRE_THROWS_WITH(PrintParser(PKB (), Statement(EntityType::PRINT, 1, "print a_"), "parent"), "Invalid print statement");
REQUIRE_THROWS_WITH(PrintParser(PKB (), Statement(EntityType::PRINT, 1, "print a a"), "parent"), "Invalid print statement");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::PRINT, 1, "print x"), "parent");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::PRINT, 1, " print x1a "), "0");
REQUIRE_NOTHROW(PKB (), Statement(EntityType::PRINT, 1, "       print            x            "), "0");
}
