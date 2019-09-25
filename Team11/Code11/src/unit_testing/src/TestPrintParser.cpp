#include "catch.hpp"
#include "PrintParser.h"
#include "ErrorMessages.h"

TEST_CASE("PrintParser")
{
    PKB pkb;
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "x"), "parent"), error_messages::invalid_print_statement);
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print "), "parent"), error_messages::invalid_print_statement);
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print a_"), "parent"), error_messages::invalid_print_statement);
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print a a"), "parent"), error_messages::invalid_print_statement);
    REQUIRE_THROWS_WITH(PrintParser(pkb, Statement(EntityType::ANY, 1, "print a;"), "parent"), error_messages::invalid_print_type);
    REQUIRE_NOTHROW(PrintParser(pkb, Statement(EntityType::PRINT, 1, "print x;"), "parent"));
    REQUIRE_NOTHROW(PrintParser(pkb, Statement(EntityType::PRINT, 1, " print x1a ;"), "0"));
    REQUIRE_NOTHROW(PrintParser(pkb, Statement(EntityType::PRINT, 1, "       print            x            ;"), "0"));
}
