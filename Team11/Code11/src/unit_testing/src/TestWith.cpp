#include "catch.hpp"
#include "pql_dto/With.h"

#include <string>

TEST_CASE("Check Equal With Method.")
{
    SECTION("Check Same With.")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("prog_line", "4", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "y", true);
        pql_dto::With with_1 = pql_dto::With(first_param_entity, second_param_entity);
        pql_dto::With with_2 = pql_dto::With(first_param_entity, second_param_entity);
        pql_dto::With with_3 = pql_dto::With(second_param_entity, first_param_entity);

        REQUIRE(with_1 == with_2);
        REQUIRE(with_2 == with_3);
        REQUIRE(with_1 == with_3);
        REQUIRE(with_1.equals(with_2));
    }

    SECTION("Check Diff With.")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("prog_line", "4", false);
        pql_dto::Entity second_param_entity_1 = pql_dto::Entity("prog_line", "y", true);
        pql_dto::Entity second_param_entity_2 = pql_dto::Entity("prog_line", "z", true);
        pql_dto::With with_1 = pql_dto::With(first_param_entity, second_param_entity_1);
        pql_dto::With with_2 = pql_dto::With(first_param_entity, second_param_entity_2);

        REQUIRE_FALSE(with_1 == with_2);
        REQUIRE_FALSE(with_1.equals(with_2));
    }
}

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

    SECTION("With with both integer params.", "With s.stmt# = c.value")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s", true);
        first_param_entity.set_entity_attr("stmt#");
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        second_param_entity.set_entity_attr("value");
        REQUIRE_NOTHROW(pql_dto::With(first_param_entity, second_param_entity));
    }

    SECTION("With with both string params.", "With v1.varName = proc.procName")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        first_param_entity.set_entity_attr("varName");
        pql_dto::Entity second_param_entity = pql_dto::Entity("procedure", "proc", true);
        second_param_entity.set_entity_attr("procName");
        REQUIRE_NOTHROW(pql_dto::With(first_param_entity, second_param_entity));
    }

    SECTION("With with one declared and one undeclared.", "With v1.varName = \"count\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        first_param_entity.set_entity_attr("varName");
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

    SECTION("With with 2 declared variables mismatch type.", "With v.varName = s.stmt#")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        first_param_entity.set_entity_attr("varName");
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s", true);
        second_param_entity.set_entity_attr("stmt#");
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::invalid_with_mismatch_type);
    }

    SECTION("With with 1 declared variables mismatch type.", "With proc = 5")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "proc", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "5", false);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::invalid_with_param);
    }

    SECTION("With with same type but different strings.", "With \"count\" = \"long\"")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "count", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "long", false);
        REQUIRE_THROWS_WITH(pql_dto::With(first_param_entity, second_param_entity),
            error_messages::with_trivial_false);
    }
}