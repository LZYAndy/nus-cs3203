#include "catch.hpp"
#include "PQLParser.h"
#include "ErrorMessages.h"

TEST_CASE("Parses and validate declaration clause.")
{
    std::unordered_map<std::string, std::string> declared_variables;
    std::vector<pql_dto::Entity> declaration_clause;

    SECTION("Valid Declaration Clause")
    {
        std::string test_query = "variable v1, v2; print prt; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(declaration_clause.size() == 4);
        REQUIRE(declared_variables.size() == 4);

        CHECK(declaration_clause.at(0).equals(pql_dto::Entity("variable", "v1", true)));
        CHECK(declaration_clause.at(1).equals(pql_dto::Entity("variable", "v2", true)));
        CHECK(declaration_clause.at(2).equals(pql_dto::Entity("print", "prt", true)));
        CHECK(declaration_clause.at(3).equals(pql_dto::Entity("assign", "a", true)));

        CHECK(declared_variables.at("v1") == "variable");
        CHECK(declared_variables.at("v2") == "variable");
        CHECK(declared_variables.at("prt") == "print");
        CHECK(declared_variables.at("a") == "assign");
    }

    SECTION("Invalid Declaration Clause With Duplicate Synonyms")
    {
        std::string test_query = "variable v1, v2; print prt; assign v1";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_duplicate_synonyms);
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms")
    {
        std::string test_query = "variable; print; assign";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms with extra space")
    {
        std::string test_query = "variable v1; print ; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }

    SECTION("Invalid Declaration Clause With No Spaces")
    {
        std::string test_query = "variablev1;printprt;assigna";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }
}