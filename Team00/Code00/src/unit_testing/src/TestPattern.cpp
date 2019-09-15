#include "catch.hpp"
#include "pql_dto/Pattern.h"

#include <string>

TEST_CASE("Pattern can store and retrieve correct entity types.")
{
    SECTION("Trivial Pattern Relationship.", "Pattern a(\"x\",\"y+z\")")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("string", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("pattexpr", "y+z", false);
        pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity);

        pql_dto::Entity entity = pattern.get_pattern_entity();
        pql_dto::Entity first_param = pattern.get_first_param();
        pql_dto::Entity second_param = pattern.get_second_param();

        REQUIRE(entity.equals(pattern_entity));
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Pattern with both any param.", "Pattern a(_,_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity));
    }

    SECTION("Pattern with any first param.", "Pattern a(_,\"x\")")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("pattexpr", "a", false);
        REQUIRE_NOTHROW(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity));
    }

    SECTION("Pattern with _ expr _ in second param.", "Pattern a(_,_\"x+y\"_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("pattexpr", "_\"x+y\"_", false);
        REQUIRE_NOTHROW(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity));
    }
}

TEST_CASE("Pattern throws error for incorrect entity types.")
{
    SECTION("Trivial Pattern with first param as an expression.", "Pattern a(\"x+y\",_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("pattexpr", "\"x+y\"", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity), "Invalid Entity Type For Pattern First Param!");
    }

    SECTION("Pattern with wrong pattern entity.", "Pattern s(_,_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("stmt", "s", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity), "Invalid Entity Type For Pattern Entity!");
    }

    SECTION("Pattern with second param as a declared constant.", "Pattern a(\"x\",c)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("string", "\"x\"", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity), "Invalid Entity Type For Pattern Second Param!");
    }

    SECTION("Pattern with second param as a declared variable.", "Pattern a(\"x\",v)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("string", "\"x\"", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity), "Invalid Entity Type For Pattern Second Param!");
    }
}