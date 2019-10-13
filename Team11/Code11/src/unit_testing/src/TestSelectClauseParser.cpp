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
    std::string declaration_error = PQLParserHelper::parse_declaration_clause(declaration_query, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Select Clause with one such that clause.")
    {
        std::string test_query = "Select v1 such that Modifies(4, v1)  ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("variable", "v1", true)));
        CHECK(condition_query == "such that Modifies(4, v1)");
    }

    SECTION("Valid Select Clause with one such that and one pattern clause.")
    {
        std::string test_query = "Select prt such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("print", "prt", true)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with tuple variables.")
    {
        std::string test_query = "Select <v2, v1> such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("variable", "v2", true)));
        CHECK(select_clause.at(1).equals(pql_dto::Entity("variable", "v1", true)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with tuple variables and attributes.")
    {
        std::string test_query = "Select <v2.varName, v1.varName> such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);

        pql_dto::Entity entity_1 = pql_dto::Entity("variable", "v2", true);
        entity_1.set_entity_attr("varName");
        CHECK(select_clause.at(0).equals(entity_1));

        pql_dto::Entity entity_2 = pql_dto::Entity("variable", "v1", true);
        entity_2.set_entity_attr("varName");
        CHECK(select_clause.at(1).equals(entity_2));

        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with one tuple variable.")
    {
        std::string test_query = "Select <v2> such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("variable", "v2", true)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with tuple variables with spaces.")
    {
        std::string test_query = "Select <   v2   , v1   > such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("variable", "v2", true)));
        CHECK(select_clause.at(1).equals(pql_dto::Entity("variable", "v1", true)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with tuple variables with spaces in attribute values.")
    {
        std::string test_query = "Select <   v2  .  varName   , a   .  stmt#   > such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);

        pql_dto::Entity entity_1 = pql_dto::Entity("variable", "v2", true);
        entity_1.set_entity_attr("varName");
        CHECK(select_clause.at(0).equals(entity_1));

        pql_dto::Entity entity_2 = pql_dto::Entity("assign", "a", true);
        entity_2.set_entity_attr("stmt#");
        CHECK(select_clause.at(1).equals(entity_2));

        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with BOOLEAN.")
    {
        std::string test_query = "Select BOOLEAN such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        CHECK(select_clause.at(0).equals(pql_dto::Entity("boolean", "BOOLEAN", false)));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with one Select variable with attribute.")
    {
        std::string test_query = "Select v1.varName such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        pql_dto::Entity entity = pql_dto::Entity("variable", "v1", true);
        entity.set_entity_attr("varName");
        CHECK(select_clause.at(0).equals(entity));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with one Select variable with attribute separated by spaces.")
    {
        std::string test_query = "Select v1      .     varName such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);

        pql_dto::Entity entity = pql_dto::Entity("variable", "v1", true);
        entity.set_entity_attr("varName");
        CHECK(select_clause.at(0).equals(entity));
        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Valid Select Clause with tuple with attribute.")
    {
        std::string test_query = "Select < v1.varName , a.stmt# > such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);

        pql_dto::Entity entity_1 = pql_dto::Entity("variable", "v1", true);
        entity_1.set_entity_attr("varName");
        CHECK(select_clause.at(0).equals(entity_1));

        pql_dto::Entity entity_2 = pql_dto::Entity("assign", "a", true);
        entity_2.set_entity_attr("stmt#");
        CHECK(select_clause.at(1).equals(entity_2));

        CHECK(condition_query == "such that Modifies(4, v1) pattern a(_,_)");
    }

    SECTION("Invalid Select Clause with no Select word.")
    {
        std::string test_query = "prt such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_select_clause_syntax);
    }

    SECTION("Invalid Select Clause with no declared variable.")
    {
        std::string test_query = "Select s1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with missing variables.")
    {
        std::string test_query = "Select such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with addition word before Select.")
    {
        std::string test_query = "var Select v1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_select_clause_syntax);
    }

    SECTION("Invalid Select Clause with string after Select.")
    {
        std::string test_query = "Select \"v1 \" such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid Select Clause with wrong attribute value.")
    {
        std::string test_query = "Select v1.stmt# such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_entity_attr);
    }

    SECTION("Invalid Select Clause with multiple attribute value.")
    {
        std::string test_query = "Select v1.stmt#.value such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParserHelper::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == error_messages::invalid_query_select_attr_syntax);
    }
}
