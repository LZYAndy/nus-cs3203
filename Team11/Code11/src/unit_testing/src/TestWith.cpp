#include "catch.hpp"
#include "pql_dto/With.h"

#include <string>

TEST_CASE("With can store and retrieve correct entity types.")
{
    SECTION("Trivial With Relationship.", "With \"x\"=\"x\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::With with = pql_dto::With(first_param_entity, second_param_entity);

        pql_dto::Entity first_param = with.get_first_param();
        pql_dto::Entity second_param = with.get_second_param();

        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("With with both integer params.", "With s = c")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_NOTHROW(pql_dto::With(first_param_entity, second_param_entity));
    }

    SECTION("With with both string params.", "With v1 = proc")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("procedure", "proc", true);
        REQUIRE_NOTHROW(pql_dto::With(first_param_entity, second_param_entity));
    }

    SECTION("With with one declared and one undeclared.", "With v1 = \"count\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "count", false);
        REQUIRE_NOTHROW(pql_dto::With(first_param_entity, second_param_entity));
    }

    SECTION("With with one declared and one undeclared. Update undeclared type.", "With proc.procName = \"count\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "proc", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "count", false);
        first_param_entity.set_entity_attr("procName");

        pql_dto::With with = pql_dto::With(first_param_entity, second_param_entity);
        second_param_entity.set_entity_type("procedure");
        second_param_entity.set_entity_attr("procName");

        REQUIRE(with.get_second_param().equals(second_param_entity));
    }

    SECTION("With with one declared and one undeclared. Update undeclared type.", "With a.stmt# = 5")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "5", false);
        first_param_entity.set_entity_attr("stmt#");

        pql_dto::With with = pql_dto::With(first_param_entity, second_param_entity);
        second_param_entity.set_entity_type("assign");
        second_param_entity.set_entity_attr("stmt#");

        REQUIRE(with.get_second_param().equals(second_param_entity));
    }
}

TEST_CASE("With throws error for incorrect entity types.")
{
    SECTION("Trivial With with mismatch type.", "With \"count\" = 5 ")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "count", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "5", false);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::invalid_with_mismatch_type);
    }

    SECTION("With with 2 declared variables mismatch type.", "With v = s")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s", true);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::invalid_with_mismatch_type);
    }

    SECTION("With with 1 declared variables mismatch type.", "With proc = 5")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "proc", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "5", false);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::invalid_with_mismatch_type);
    }

    SECTION("With with same type but different strings.", "With \"count\" = \"long\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "count", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "long", false);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::with_trivial_false);
    }
}