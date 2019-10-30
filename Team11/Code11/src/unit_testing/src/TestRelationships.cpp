#include "catch.hpp"
#include "pql_dto/Relationships.h"
#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"
#include "pql_dto/CallsRelationship.cpp"
#include "pql_dto/NextRelationship.cpp"
#include "pql_dto/AffectsRelationship.cpp"
#include "pql_dto/NextBipRelationship.cpp"
#include "pql_dto/AffectsBipRelationship.cpp"

#include <string>

TEST_CASE("Follows Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Follow Relationship.", "Follows(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships follows_relationship = pql_dto::FollowsRelationship(first_param_entity,
                second_param_entity, false);

        RelationshipType relationship_type = follows_relationship.get_relationship_type();
        pql_dto::Entity first_param = follows_relationship.get_first_param();
        pql_dto::Entity second_param = follows_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::FOLLOWS);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Follow Relationship with both unknown param.", "Follows(s1,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::FollowsRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Follow Relationship with any param and declared variable.", "Follows(_,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::FollowsRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Follow Relationship with a stmt number and any param.", "Follows(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::FollowsRelationship(first_param_entity,
                        second_param_entity, false));
    }
}

TEST_CASE("Follows Relationships throws error for incorrect entity types.")
{
    SECTION("Trivial Follow Relationship with first param greater than second param.", "Follows(7,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::FollowsRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_order_of_params);
    }

    SECTION("Follow Relationship with invalid procedure first param entity.", "Follows(p,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::FollowsRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_follows_relationship_first_param);
    }

    SECTION("Follow Relationship with invalid constant second param entity.", "Follows(7,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::FollowsRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_follows_relationship_second_param);
    }

    SECTION("Follow Relationship with invalid variable first param entity.", "Follows(v,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::FollowsRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_follows_relationship_first_param);
    }
}

TEST_CASE("Parent Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Parent Relationship.", "Parent(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships parent_relationship = pql_dto::ParentRelationship(first_param_entity,
                second_param_entity, false);

        RelationshipType relationship_type = parent_relationship.get_relationship_type();
        pql_dto::Entity first_param = parent_relationship.get_first_param();
        pql_dto::Entity second_param = parent_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::PARENT);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Parent Relationship with both unknown param.", "Parent(w,s1)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("while", "w", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s1", true);
        REQUIRE_NOTHROW(pql_dto::ParentRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Parent Relationship with any param and declared variable.", "Parent(_,ifs)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("if", "ifs", true);
        REQUIRE_NOTHROW(pql_dto::ParentRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Parent Relationship with a stmt number and any param.", "Parent(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::ParentRelationship(first_param_entity,
                        second_param_entity, false));
    }
}

TEST_CASE("Parent Relationships throws error for incorrect entity types.")
{
    SECTION("Trivial Parent Relationship with first param greater than second param.", "Parent(7,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::ParentRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_order_of_params);
    }

    SECTION("Parent Relationship with invalid string first param entity.", "Parent(\"a\",2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "a", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::ParentRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_parent_relationship_first_param);
    }

    SECTION("Parent Relationship with invalid pattern expression second param entity.", "Parent(7,_\"x + y\"_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("pattexpr", "x+y", false);
        REQUIRE_THROWS_WITH(pql_dto::ParentRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_parent_relationship_second_param);
    }

    SECTION("Parent Relationship with invalid string of pattern first param entity.", "Parent(\"x+y\", s1)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("matchexpr", "x+y", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s1", true);
        REQUIRE_THROWS_WITH(pql_dto::ParentRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_parent_relationship_first_param);
    }
}

TEST_CASE("Uses Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Uses Relationship.", "Uses(\"a\",\"x\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "a", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Relationships uses_relationship = pql_dto::UsesRelationship(first_param_entity,
                second_param_entity, false);

        RelationshipType relationship_type = uses_relationship.get_relationship_type();
        pql_dto::Entity first_param = uses_relationship.get_first_param();
        pql_dto::Entity second_param = uses_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::USES);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Uses Relationship with both unknown param.", "Uses(s1,v2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v2", true);
        REQUIRE_NOTHROW(pql_dto::UsesRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Uses Relationship with declared statement and any param.", "Uses(s1,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::UsesRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Uses Relationship with a stmt number and a variable.", "Uses(6,\"x\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        REQUIRE_NOTHROW(pql_dto::UsesRelationship(first_param_entity,
                        second_param_entity, false));
    }
}

TEST_CASE("Uses Relationships throws error for incorrect entity types.")
{
    SECTION("Trivial Uses Relationship with second param as statement.", "Uses(7,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::UsesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_uses_relationship_second_param);
    }

    SECTION("Uses Relationship with invalid any first param entity.", "Uses(_,v)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(pql_dto::UsesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_uses_relationship_first_param);
    }

    SECTION("Uses Relationship with invalid stmt second param entity.", "Uses(2,s1)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s1", true);
        REQUIRE_THROWS_WITH(pql_dto::UsesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_uses_relationship_second_param);
    }

    SECTION("Uses Relationship with invalid read first param entity.", "Uses(r,v)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("read", "r", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(pql_dto::UsesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_uses_relationship_first_param);
    }

    SECTION("Uses Relationship with invalid variable first param entity.", "Uses(v1,v2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v2", true);
        REQUIRE_THROWS_WITH(pql_dto::UsesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_uses_relationship_first_param);
    }
}

TEST_CASE("Modifies Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Modifies Relationship.", "Modifies(\"a\",\"x\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "a", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        pql_dto::Relationships modifies_relationship = pql_dto::ModifiesRelationship(first_param_entity,
                second_param_entity, false);

        RelationshipType relationship_type = modifies_relationship.get_relationship_type();
        pql_dto::Entity first_param = modifies_relationship.get_first_param();
        pql_dto::Entity second_param = modifies_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::MODIFIES);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Modifies Relationship with both unknown param.", "Modifies(s1,v2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v2", true);
        REQUIRE_NOTHROW(pql_dto::ModifiesRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Modifies Relationship with declared statement and any param.", "Modifies(s1,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::ModifiesRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Modifies Relationship with a stmt number and a variable.", "Modifies(6,\"x\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        REQUIRE_NOTHROW(pql_dto::ModifiesRelationship(first_param_entity,
                        second_param_entity, false));
    }

    SECTION("Modifies Relationship with a read statement and a string.", "Modifies(r,\"y\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("read", "r", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "y", false);
        REQUIRE_NOTHROW(pql_dto::ModifiesRelationship(first_param_entity,
                        second_param_entity, false));
    }
}

TEST_CASE("Modifies Relationships throws error for incorrect entity types.")
{
    SECTION("Trivial Modifies Relationship with second param as statement.", "Modifies(7,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::ModifiesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_modifies_relationship_second_param);
    }

    SECTION("Modifies Relationship with invalid any first param entity.", "Modifies(_,v)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(pql_dto::ModifiesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_modifies_relationship_first_param);
    }

    SECTION("Modifies Relationship with invalid stmt second param entity.", "Modifies(2,s1)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s1", true);
        REQUIRE_THROWS_WITH(pql_dto::ModifiesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_modifies_relationship_second_param);
    }

    SECTION("Modifies Relationship with invalid print first param entity.", "Modifies(prt,\"x\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("print", "prt", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "x", false);
        REQUIRE_THROWS_WITH(pql_dto::ModifiesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_modifies_relationship_first_param);
    }

    SECTION("Modifies Relationship with invalid variable param entity.", "Modifies(v1,v2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("variable", "v2", true);
        REQUIRE_THROWS_WITH(pql_dto::ModifiesRelationship(first_param_entity,
                            second_param_entity, false), error_messages::invalid_modifies_relationship_first_param);
    }
}

TEST_CASE("Calls Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Calls Relationship.", "Calls(\"proc1\",\"proc2\")")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "proc1", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("procedure", "proc2", false);
        pql_dto::Relationships calls_relationship = pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false);

        RelationshipType relationship_type = calls_relationship.get_relationship_type();
        pql_dto::Entity first_param = calls_relationship.get_first_param();
        pql_dto::Entity second_param = calls_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::CALLS);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Calls Relationship with both unknown param.", "Calls(p1,p2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("procedure", "p2", true);
        REQUIRE_NOTHROW(pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Calls Relationship with declared procedure and any param.", "Calls(p1,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Calls Relationship with both any.", "Calls(_,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false));
    }
}

TEST_CASE("Calls Relationships throws error for incorrect entity types.")
{
    SECTION("Trivial Calls Relationship with second param as statement.", "Calls(7,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_calls_relationship_first_param);
    }

    SECTION("Calls Relationship with invalid stmt second param entity.", "Calls(p1,s1)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p1", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s1", true);
        REQUIRE_THROWS_WITH(pql_dto::CallsRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_calls_relationship_second_param);
    }
}

TEST_CASE("Next Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Next Relationship.", "Next(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("prog_line", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "7", false);
        pql_dto::Relationships Next_relationship = pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false);

        RelationshipType relationship_type = Next_relationship.get_relationship_type();
        pql_dto::Entity first_param = Next_relationship.get_first_param();
        pql_dto::Entity second_param = Next_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::NEXT);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Next Relationship with both unknown param.", "Next(s1,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Next Relationship with any param and declared variable.", "Next(_,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Next Relationship with a stmt number and any param.", "Next(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false));
    }
}

TEST_CASE("Next Relationships throws error for incorrect entity types.")
{
    SECTION("Next Relationship with invalid procedure first param entity.", "Next(p,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_relationship_first_param);
    }

    SECTION("Next Relationship with invalid constant second param entity.", "Next(7,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_relationship_second_param);
    }

    SECTION("Next Relationship with invalid variable first param entity.", "Next(v,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::NextRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_relationship_first_param);
    }
}

TEST_CASE("Affects Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial Affects Relationship.", "Affects(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships Affects_relationship = pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false);

        RelationshipType relationship_type = Affects_relationship.get_relationship_type();
        pql_dto::Entity first_param = Affects_relationship.get_first_param();
        pql_dto::Entity second_param = Affects_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::AFFECTS);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("Affects Relationship with both unknown param.", "Affects(s1,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Affects Relationship with any param and declared variable.", "Affects(_,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("Affects Relationship with a stmt number and any param.", "Affects(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false));
    }
}

TEST_CASE("Affects Relationships throws error for incorrect entity types.")
{
    SECTION("Affects Relationship with invalid procedure first param entity.", "Affects(p,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_relationship_first_param);
    }

    SECTION("Affects Relationship with invalid constant second param entity.", "Affects(7,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_relationship_second_param);
    }

    SECTION("Affects Relationship with invalid variable first param entity.", "Affects(v,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::AffectsRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_relationship_first_param);
    }
}

TEST_CASE("NextBip Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial NextBip Relationship.", "NextBip(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("prog_line", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("prog_line", "7", false);
        pql_dto::Relationships NextBip_relationship = pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false);

        RelationshipType relationship_type = NextBip_relationship.get_relationship_type();
        pql_dto::Entity first_param = NextBip_relationship.get_first_param();
        pql_dto::Entity second_param = NextBip_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::NEXTBIP);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("NextBip Relationship with both unknown param.", "NextBip(s1,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("NextBip Relationship with any param and declared variable.", "NextBip(_,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("NextBip Relationship with a stmt number and any param.", "NextBip(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false));
    }
}

TEST_CASE("NextBip Relationships throws error for incorrect entity types.")
{
    SECTION("NextBip Relationship with invalid procedure first param entity.", "NextBip(p,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_bip_relationship_first_param);
    }

    SECTION("NextBip Relationship with invalid constant second param entity.", "NextBip(7,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_bip_relationship_second_param);
    }

    SECTION("NextBip Relationship with invalid variable first param entity.", "NextBip(v,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::NextBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_next_bip_relationship_first_param);
    }
}

TEST_CASE("AffectsBip Relationships can store and retrieve correct entity types.")
{
    SECTION("Trivial AffectsBip Relationship.", "AffectsBip(2,7)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "2", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Relationships AffectsBip_relationship = pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false);

        RelationshipType relationship_type = AffectsBip_relationship.get_relationship_type();
        pql_dto::Entity first_param = AffectsBip_relationship.get_first_param();
        pql_dto::Entity second_param = AffectsBip_relationship.get_second_param();

        REQUIRE(relationship_type == RelationshipType::AFFECTSBIP);
        REQUIRE(first_param.equals(first_param_entity));
        REQUIRE(second_param.equals(second_param_entity));
    }

    SECTION("AffectsBip Relationship with both unknown param.", "AffectsBip(s1,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "s1", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("AffectsBip Relationship with any param and declared variable.", "AffectsBip(_,s2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "s2", true);
        REQUIRE_NOTHROW(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false));
    }

    SECTION("AffectsBip Relationship with a stmt number and any param.", "AffectsBip(6,_)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "6", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        REQUIRE_NOTHROW(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false));
    }
}

TEST_CASE("AffectsBip Relationships throws error for incorrect entity types.")
{
    SECTION("AffectsBip Relationship with invalid procedure first param entity.", "AffectsBip(p,2)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("procedure", "p", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("stmt", "2", false);
        REQUIRE_THROWS_WITH(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_bip_relationship_first_param);
    }

    SECTION("AffectsBip Relationship with invalid constant second param entity.", "AffectsBip(7,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("stmt", "7", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_bip_relationship_second_param);
    }

    SECTION("AffectsBip Relationship with invalid variable first param entity.", "AffectsBip(v,c)")
    {
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "v", true);
        pql_dto::Entity second_param_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(pql_dto::AffectsBipRelationship(first_param_entity,
            second_param_entity, false), error_messages::invalid_affects_bip_relationship_first_param);
    }
}
