#include "catch.hpp"
#include "ReadParser.h"
#include "ErrorMessages.h"

TEST_CASE("ReadParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "x"), "parent"), error_messages::invalid_read_statement);
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read "), "parent"), error_messages::invalid_read_statement);
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read a_"), "parent"), error_messages::invalid_read_statement);
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::READ, 1, "read a a"), "parent"), error_messages::invalid_read_statement);
    REQUIRE_THROWS_WITH(ReadParser(pkb, Statement(EntityType::ANY, 1, "read a;"), "parent"), error_messages::invalid_read_type);
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, "read x;"), "parent");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, " read x1a ;"), "0");
    REQUIRE_NOTHROW(pkb, Statement(EntityType::READ, 1, "       read            x            ;"), "0");
}
