#include "catch.hpp"
#include "PQLParser.h"

#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"

TEST_CASE("Parses and validate Follows such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Such that Clause. No query.")
    {
        std::string test_query = "";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 0);
    }

    SECTION("Valid Such that Clause with Follows. 2 undeclared.")
    {
        std::string test_query = "such that Follows(4, 5)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::FollowsRelationship(pql_dto::Entity("stmt", "4", false),
                                            pql_dto::Entity("stmt", "5", false), false)));
    }

    SECTION("Valid Such that Clause with Follows variables. 2 declared.")
    {
        std::string test_query = "such that Follows(a, prt)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::FollowsRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("print", "prt", true), false)));
    }

    SECTION("Valid Such that Clause with Follows variables. 1 declared, 1 undeclared.")
    {
        std::string test_query = "such that Follows(a, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::FollowsRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("stmt", "6", false), false)));
    }

    SECTION("Invalid Such that Clause with Follows variables. First statement greater than second statement number.")
    {
        std::string test_query = "such that Follows(7, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_order_of_params);
    }

    SECTION("Invalid Such that Clause with Follows variables. Variables as parameters.")
    {
        std::string test_query = "such that Follows(v1, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_follows_relationship_first_param);
    }

    SECTION("Invalid Such that Clause with Follows variables. Missing parameters.")
    {
        std::string test_query = "such that Follows(a, )";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_declared_entity_name);
    }

    SECTION("Invalid Such that Clause with Follows variables. Invalid Syntax. Missing Params.")
    {
        std::string test_query = "such that Follows()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Follows variables. Invalid Syntax. Missing such that")
    {
        std::string test_query = "that Follows(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Follows variables. Wrong format.")
    {
        std::string test_query = "such that Follows)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Follows variables. Wrong entity.")
    {
        std::string test_query = "such that Follows(\"5\", \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_synonym_name);
    }

    SECTION("Valid Such that Clause with Follows*.")
    {
        std::string test_query = "such that Follows*(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::FollowsRelationship(pql_dto::Entity("stmt", "5", false),
                                            pql_dto::Entity("stmt", "6", false), true)));
    }
}

TEST_CASE("Parses and validate Parent such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Such that Clause with Parent. 2 undeclared.")
    {
        std::string test_query = "such that Parent(2, 5)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ParentRelationship(pql_dto::Entity("stmt", "2", false),
                                            pql_dto::Entity("stmt", "5", false), false)));
    }

    SECTION("Valid Such that Clause with Parent variables. 2 declared.")
    {
        std::string test_query = "such that Parent(a, prt)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ParentRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("print", "prt", true), false)));
    }

    SECTION("Valid Such that Clause with Parent variables. 1 declared, 1 undeclared.")
    {
        std::string test_query = "such that Parent(a, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ParentRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("stmt", "6", false), false)));
    }

    SECTION("Invalid Such that Clause with Parent variables. First statement greater than second statement number.")
    {
        std::string test_query = "such that Parent(7, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_order_of_params);
    }

    SECTION("Invalid Such that Clause with Parent variables. Variables as parameters.")
    {
        std::string test_query = "such that Parent(v1, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_parent_relationship_first_param);
    }

    SECTION("Invalid Such that Clause with Parent variables. Missing parameters.")
    {
        std::string test_query = "such that Parent(a, )";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_declared_entity_name);
    }

    SECTION("Invalid Such that Clause with Parent variables. Invalid Syntax. Missing Params.")
    {
        std::string test_query = "such that Parent()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Parent variables. Invalid Syntax. Missing such that")
    {
        std::string test_query = "that Parent(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Parent variables. Wrong format.")
    {
        std::string test_query = "such that Parent)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Parent variables. Wrong entity.")
    {
        std::string test_query = "such that Parent(\"5\", \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_synonym_name);
    }

    SECTION("Valid Such that Clause with Parent*.")
    {
        std::string test_query = "such that Parent*(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ParentRelationship(pql_dto::Entity("stmt", "5", false),
                                            pql_dto::Entity("stmt", "6", false), true)));
    }
}

TEST_CASE("Parses and validate Uses such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a; procedure p";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Such that Clause with Uses. 2 undeclared.")
    {
        std::string test_query = "such that Uses(2, \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::UsesRelationship(pql_dto::Entity("stmt", "2", false),
                                            pql_dto::Entity("variable", "x", false), false)));
    }

    SECTION("Valid Such that Clause with Uses. 2 declared")
    {
        std::string test_query = "such that Uses(a, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::UsesRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("variable", "v1", true), false)));
    }

    SECTION("Valid Such that Clause with Uses. 1 declared, 1 undeclared")
    {
        std::string test_query = "such that Uses(p, \"y\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::UsesRelationship(pql_dto::Entity("procedure", "p", true),
                                            pql_dto::Entity("variable", "y", false), false)));
    }

    SECTION("Valid Such that Clause with Uses. 1 declared, underscore as second param")
    {
        std::string test_query = "such that Uses(p, _)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::UsesRelationship(pql_dto::Entity("procedure", "p", true),
                                            pql_dto::Entity("any", "_", false), false)));
    }

    SECTION("Invalid Such that Clause with Uses. Wrong second entity")
    {
        std::string test_query = "such that Uses(p, a)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_uses_relationship_second_param);
    }

    SECTION("Invalid Such that Clause with Uses. Wrong first entity")
    {
        std::string test_query = "such that Uses(v2, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_uses_relationship_first_param);
    }

    SECTION("Invalid Such that Clause with Uses. Missing Params")
    {
        std::string test_query = "such that Uses()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Uses. Invalid Syntax")
    {
        std::string test_query = "such that Uses)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Uses. Wrong relationship spelling")
    {
        std::string test_query = "such that Uss(a, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_relationship_type);
    }

    SECTION("Invalid Such that Clause with Uses. Underscore as first param")
    {
        std::string test_query = "such that Uses(_, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_uses_relationship_first_param);
    }
}

TEST_CASE("Parses and validate Modifies such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a; procedure p";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Such that Clause with Modifies.")
    {
        std::string test_query = "such that Modifies(a, \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ModifiesRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("variable", "x", false), false)));
    }

    SECTION("Valid Such that Clause with Modifies. 2 declared")
    {
        std::string test_query = "such that Modifies(a, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ModifiesRelationship(pql_dto::Entity("assign", "a", true),
                                            pql_dto::Entity("variable", "v1", true), false)));
    }

    SECTION("Valid Such that Clause with Modifies. 1 declared, 1 undeclared")
    {
        std::string test_query = "such that Modifies(p, \"y\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ModifiesRelationship(pql_dto::Entity("procedure", "p", true),
                                            pql_dto::Entity("variable", "y", false), false)));
    }

    SECTION("Valid Such that Clause with Modifies. 1 declared, underscore as second param")
    {
        std::string test_query = "such that Modifies(p, _)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::ModifiesRelationship(pql_dto::Entity("procedure", "p", true),
                                            pql_dto::Entity("any", "_", false), false)));
    }

    SECTION("Invalid Such that Clause with Modifies. Wrong second entity")
    {
        std::string test_query = "such that Modifies(p, a)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_modifies_relationship_second_param);
    }

    SECTION("Invalid Such that Clause with Modifies. Wrong first entity")
    {
        std::string test_query = "such that Modifies(v2, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_modifies_relationship_first_param);
    }

    SECTION("Invalid Such that Clause with Modifies. Missing Params")
    {
        std::string test_query = "such that Modifies()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Modifies. Invalid Syntax")
    {
        std::string test_query = "such that Modifies)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid Such that Clause with Modifies. Wrong relationship spelling")
    {
        std::string test_query = "such that Uss(a, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_relationship_type);
    }

    SECTION("Invalid Such that Clause with Modifies. Underscore as first param")
    {
        std::string test_query = "such that Modifies(_, v1)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_modifies_relationship_first_param);
    }
}