#include "catch.hpp"
#include "PQLParser.h"

TEST_CASE("Pql query parser parse and validate correctly.")
{
    std::vector<pql_dto::Entity> declaration_clause, select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;

    SECTION("Valid query 1.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 such that Modifies(4, v1) pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 2.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 pattern a (_,_) such that Modifies(4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 3.")
    {
        std::string test_query = "         variable v1\t, v2\n; assign a; Select v1 pattern a(_,          _) such  \v that    Modifies    (4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, declaration_clause, select_clause, such_that_clause, pattern_clause);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 3);
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }
}

