#include "catch.hpp"
#include "Statement.h"
#include "pql_dto/Entity.h"

TEST_CASE("TestStatement")
{
    Statement stmt = Statement(EntityType::ASSIGN, 1, "a = b ");
    REQUIRE(stmt.get_statement_type() == EntityType::ASSIGN);
    REQUIRE(stmt.get_prog_line() == 1);
    REQUIRE(stmt.get_statement() == "a = b ");

    stmt.set_procedure("main");
    REQUIRE(stmt.get_procedure() == "main");
}
