#include "catch.hpp"
#include "pql_dto/Pattern.h"

#include <string>

TEST_CASE("Check Equal Pattern Method.")
{
    SECTION("Check Same Pattern.")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("matchexpr", "y+z", false);
        pql_dto::Pattern pattern_1 = pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity);
        pql_dto::Pattern pattern_2 = pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity);

        REQUIRE(pattern_1 == pattern_2);
        REQUIRE(pattern_1.equals(pattern_2));
    }

    SECTION("Check Diff Pattern.")
    {
        pql_dto::Entity pattern_entity_1 = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity pattern_entity_2 = pql_dto::Entity("if", "ifs", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Pattern pattern_1 = pql_dto::Pattern(pattern_entity_1, first_param_entity,
            second_param_entity);
        pql_dto::Pattern pattern_2 = pql_dto::Pattern(pattern_entity_2, first_param_entity,
            second_param_entity);

        REQUIRE_FALSE(pattern_1 == pattern_2);
        REQUIRE_FALSE(pattern_1.equals(pattern_2));
    }
}

TEST_CASE("Pattern can store and retrieve correct entity types.")
{
    SECTION("Trivial Pattern Relationship.", "Pattern a(\"x\",\"y+z\")")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("matchexpr", "y+z", false);
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
        pql_dto::Entity second_param_entity = pql_dto::Entity("matchexpr", "x", false);
        REQUIRE_NOTHROW(pql_dto::Pattern(pattern_entity, first_param_entity,
                                         second_param_entity));
    }

    SECTION("Pattern with _ expr _ in second param.", "Pattern a(_,_\"x+y\"_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("pattexpr", "x+y", false);
        REQUIRE_NOTHROW(pql_dto::Pattern(pattern_entity, first_param_entity,
                                         second_param_entity));
    }
}

TEST_CASE("Pattern throws error for incorrect entity types.")
{
    SECTION("Trivial Pattern with first param as an expression.", "Pattern a(\"x+y\",_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("matchexpr", "x+y", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
                                             second_param_entity), error_messages::invalid_pattern_first_param);
    }

    SECTION("Pattern with wrong pattern entity.", "Pattern s(_,_)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("stmt", "s", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
                                             second_param_entity), error_messages::invalid_pattern_entity);
    }

    SECTION("Pattern with second param as a declared constant.", "Pattern a(\"x\",c)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
                                             second_param_entity), error_messages::invalid_pattern_second_param);
    }

    SECTION("Pattern with second param as a declared variable.", "Pattern a(\"x\",v)")
    {
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(pql_dto::Pattern(pattern_entity, first_param_entity,
                                             second_param_entity), error_messages::invalid_pattern_second_param);
    }
}