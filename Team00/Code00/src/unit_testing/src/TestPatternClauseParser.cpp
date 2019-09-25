#include "catch.hpp"
#include "PQLParser.h"

TEST_CASE("Parses and validate Pattern clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a; procedure p";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Pattern Clause. Both param defined.")
    {
        std::string test_query = "pattern a (\"x\", \"x\")";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(pattern_clause.size() == 1);

        CHECK(pattern_clause.at(0).equals(pql_dto::Pattern(pql_dto::Entity("assign", "a", true),
                                          pql_dto::Entity("variable", "x", false), pql_dto::Entity("matchexpr", "x", false))));
    }

    SECTION("Valid Pattern Clause. Both params underscore")
    {
        std::string test_query = "pattern a (_,_)";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(pattern_clause.size() == 1);

        CHECK(pattern_clause.at(0).equals(pql_dto::Pattern(pql_dto::Entity("assign", "a", true),
                                          pql_dto::Entity("any", "_", false), pql_dto::Entity("any", "_", false))));
    }

    SECTION("Valid Pattern Clause. Exact Match second param expression")
    {
        std::string test_query = "pattern a (_,\"x+y*z\")";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(pattern_clause.size() == 1);

        CHECK(pattern_clause.at(0).equals(pql_dto::Pattern(pql_dto::Entity("assign", "a", true),
                                          pql_dto::Entity("any", "_", false), pql_dto::Entity("matchexpr", "x+y*z", false))));
    }

    SECTION("Valid Pattern Clause. Contains Match second param expression")
    {
        std::string test_query = "pattern a (_,_\"       x+y*z\"_)";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(pattern_clause.size() == 1);

        CHECK(pattern_clause.at(0).equals(pql_dto::Pattern(pql_dto::Entity("assign", "a", true),
                                          pql_dto::Entity("any", "_", false), pql_dto::Entity("pattexpr", "x+y*z", false))));
    }

    SECTION("Invalid Pattern Clause. Wrong pattern entity")
    {
        std::string test_query = "pattern v1 (_,_       \"x+y*z\"_)";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_wrong_pattern_entity);
    }

    SECTION("Invalid Pattern Clause. No pattern clause")
    {
        std::string test_query = "a (_,_\"x+y*z\"_)";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_pattern_clause_syntax);
    }

    SECTION("Invalid Pattern Clause. Missing Params")
    {
        std::string test_query = "pattern a ()";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_pattern_clause_syntax);
    }

    SECTION("Invalid Pattern Clause. Wrong Format")
    {
        std::string test_query = "pattern a )()";
        std::string error = PQLParser::parse_pattern_clause(test_query, pattern_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_pattern_clause_syntax);
    }
}
