#include "catch.hpp"
#include "PrintParser.h"

TEST_CASE("PrintParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "x"), "parent"), "Invalid print statement");
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print "), "parent"), "Invalid print statement");
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print a_"), "parent"), "Invalid print statement");
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print a a"), "parent"), "Invalid print statement");
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::ANY, 1, "print a;"), "parent"), "Incorrect print type");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::PRINT, 1, "print x;"), "parent");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::PRINT, 1, " print x1a ;"), "0");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::PRINT, 1, "       print            x            ;"), "0");
}
