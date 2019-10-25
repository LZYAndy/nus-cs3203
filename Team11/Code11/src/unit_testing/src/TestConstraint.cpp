#include "catch.hpp"
#include "pql_dto/Constraint.h"
#include "ErrorMessages.h"

#include <string>

#include <pql_dto\FollowsRelationship.cpp>

TEST_CASE("Constraint variables can be set and get correctly.")
{
    SECTION("Set relationship object in Constraint.")
    {
        pql_dto::Constraint constraint = pql_dto::Constraint();

        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships follows_relationship = pql_dto::FollowsRelationship(first_param_entity,
            second_param_entity, false);

        constraint.set_relationship(follows_relationship);

        REQUIRE(constraint.get_first_param().equals(first_param_entity));
        REQUIRE(constraint.get_second_param().equals(second_param_entity));
        REQUIRE(constraint.get_relationship().equals(follows_relationship));
        REQUIRE(constraint.is_relationship() == true);
    }

    SECTION("Set pattern object in Constraint.")
    {
        pql_dto::Constraint constraint = pql_dto::Constraint();

        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("matchexpr", "y+z", false);
        pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param_entity,
            second_param_entity);

        constraint.set_pattern(pattern);

        REQUIRE(constraint.get_pattern_entity().equals(pattern_entity));
        REQUIRE(constraint.get_first_param().equals(first_param_entity));
        REQUIRE(constraint.get_second_param().equals(second_param_entity));
        REQUIRE(constraint.get_pattern().equals(pattern));
        REQUIRE(constraint.is_pattern() == true);
    }

    SECTION("Set with object in Constraint.")
    {
        pql_dto::Constraint constraint = pql_dto::Constraint();

        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::With with = pql_dto::With(first_param_entity, second_param_entity);

        constraint.set_with(with);

        REQUIRE(constraint.get_first_param().equals(first_param_entity));
        REQUIRE(constraint.get_second_param().equals(second_param_entity));
        REQUIRE(constraint.get_with().equals(with));
        REQUIRE(constraint.is_with() == true);
    }
}

TEST_CASE("Wrong pattern entity throws error correctly")
{
    SECTION("Get pattern entity when not pattern.")
    {
        pql_dto::Constraint constraint = pql_dto::Constraint();

        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships follows_relationship = pql_dto::FollowsRelationship(first_param_entity,
            second_param_entity, false);

        constraint.set_relationship(follows_relationship);

        REQUIRE_THROWS_WITH(constraint.get_pattern_entity(), error_messages::not_a_pattern_object);
    }
}
