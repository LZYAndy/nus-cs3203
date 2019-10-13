#include "catch.hpp"
#include "PQLParserHelper.h"
#include "PQLParser.h"
#include "ErrorMessages.h"

TEST_CASE("Parses and validate declaration clause.")
{
    std::unordered_map<std::string, std::string> declared_variables;
    std::vector<pql_dto::Entity> declaration_clause;

    SECTION("Valid Declaration Clause")
    {
        std::string test_query = "variable v1, v2; print prt; assign a";
        std::string error = PQLParserHelper::parse_declaration_clause(test_query, declared_variables);

        REQUIRE(error == "");
        REQUIRE(declared_variables.size() == 4);

        CHECK(declared_variables.at("v1") == "variable");
        CHECK(declared_variables.at("v2") == "variable");
        CHECK(declared_variables.at("prt") == "print");
        CHECK(declared_variables.at("a") == "assign");
    }

    SECTION("Invalid Declaration Clause With Duplicate Synonyms")
    {
        std::string test_query = "variable v1, v2; print prt; assign v1";
        std::string error = PQLParserHelper::parse_declaration_clause(test_query, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_duplicate_synonyms);
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms")
    {
        std::string test_query = "variable; print; assign";
        std::string error = PQLParserHelper::parse_declaration_clause(test_query, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms with extra space")
    {
        std::string test_query = "variable v1; print ; assign a";
        std::string error = PQLParserHelper::parse_declaration_clause(test_query, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }

    SECTION("Invalid Declaration Clause With No Spaces")
    {
        std::string test_query = "variablev1;printprt;assigna";
        std::string error = PQLParserHelper::parse_declaration_clause(test_query, declared_variables);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }
}