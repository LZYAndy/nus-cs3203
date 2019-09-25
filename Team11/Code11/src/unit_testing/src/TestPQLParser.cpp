#include "catch.hpp"
#include "PQLParser.h"

TEST_CASE("Pql query parser parse and validate valid query correctly.")
{
    std::vector<pql_dto::Entity> declaration_clause, select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;

    SECTION("Valid query 1.")
    {
        std::string test_query = "variable v; Select v";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 1);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 2.")
    {
        std::string test_query = "variable v; Select v such that Uses(6, v)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 1);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 3.")
    {
        std::string test_query = "variable v; assign a; Select v pattern a (\"x\",_)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 2);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 4.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 such that Modifies(4, v1) pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 5.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 pattern a (_,_) such that Modifies(4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 6.")
    {
        std::string test_query = "         variable v1\t, v2\n; assign a; Select v1 pattern a(_,          _) such  \v that    Modifies    (4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 7.")
    {
        std::string test_query = "while w;\nSelect w such that Parent(w, 7)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 1);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
    }
}

TEST_CASE("Pql query parser parse and validate invalid query correctly.")
{
    std::vector<pql_dto::Entity> declaration_clause, select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;

    SECTION("Invalid query 1.")
    {
        std::string test_query = "variable v; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid query 2.")
    {
        std::string test_query = "variable v; assign a; Select v such that Uses(6, v) and pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_query_pattern_clause_syntax);
    }

    SECTION("Invalid query 3.")
    {
        std::string test_query = "variable v; assign a; Select v pattern a (\"x\",_) and such that Modifies (6, v)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_query_such_that_clause_syntax);
    }

    SECTION("Invalid query 4.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 such that Modifies(_, v1) pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_modifies_relationship_first_param);
    }

    SECTION("Invalid query 5.")
    {
        std::string test_query = "variable v1 v2; assign a; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_declared_entity_name);
    }

    SECTION("Invalid query 6.")
    {
        std::string test_query = "variable v1, v2; assignment a; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_entity_type);
    }

    SECTION("Invalid query 7.")
    {
        std::string test_query = "while w;Select w;";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_query_declaration_duplicate_synonyms);
    }

    SECTION("Invalid query 8.")
    {
        std::string test_query = ";Select w;";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }
}

