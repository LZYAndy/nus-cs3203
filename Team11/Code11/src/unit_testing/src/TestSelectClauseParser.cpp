#include "catch.hpp"
#include "PQLParser.h"
#include "ErrorMessages.h"

TEST_CASE("Parses and validate select clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::string condition_query;
    std::vector<pql_dto::Entity> select_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Select Clause with one such that clause.")
    {
        std::string test_query = "Select v1 such that Modifies(4, v1)  ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("variable", "v1", true)));
        CHECK(condition_query == "such that Modifies(4, v1)");
    }

    SECTION("Valid Select Clause with one such that and one pattern clause.")
    {
        std::string test_query = "Select prt such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("print", "prt", true)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Invalid Select Clause with no Select word.")
    {
        std::string test_query = "prt such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_select_clause_syntax);
    }

    SECTION("Invalid Select Clause with no declared variable.")
    {
        std::string test_query = "Select s1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with no tuple variables. (Iteration 1)")
    {
        std::string test_query = "Select <v2, v1> such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with missing variables.")
    {
        std::string test_query = "Select such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with addition word before Select.")
    {
        std::string test_query = "var Select v1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_select_clause_syntax);
    }

    SECTION("Invalid Select Clause with string after Select.")
    {
        std::string test_query = "Select \"v1 \" such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }
}