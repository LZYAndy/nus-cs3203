#include "catch.hpp"
#include "ReadParser.h"

TEST_CASE("ReadParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "x"), "parent"), "Invalid read statement");
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read "), "parent"), "Invalid read statement");
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read a_"), "parent"), "Invalid read statement");
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read a a"), "parent"), "Invalid read statement");
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::ANY, 1, "read a;"), "parent"), "Incorrect read type");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, "read x;"), "parent");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, " read x1a ;"), "0");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, "       read            x            ;"), "0");
}
