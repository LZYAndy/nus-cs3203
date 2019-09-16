#include "catch.hpp"
#include "PQLParser.h"

#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"

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

        REQUIRE(error == "Invalid Query! Duplicate Synonyms for entities in Declaration Clause.");
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms")
    {
        std::string test_query = "variable; print; assign";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Query! Missing synonym.");
    }

    SECTION("Invalid Declaration Clause With Missing Synonyms with extra space")
    {
        std::string test_query = "variable v1; print ; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Query! Missing synonym.");
    }

    SECTION("Invalid Declaration Clause With Wrong Synonyms name")
    {
        std::string test_query = "variable v1@; print prt; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Entity Name!");
    }

    SECTION("Invalid Declaration Clause With underscore as entity name")
    {
        std::string test_query = "variable _; print prt; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Entity Name!");
    }

    SECTION("Invalid Declaration Clause With Wrong Entity Type")
    {
        std::string test_query = "varible v1; print prt; assign a";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Entity Type!");
    }

    SECTION("Invalid Declaration Clause With No Spaces")
    {
        std::string test_query = "variablev1;printprt;assigna";
        std::string error = PQLParser::parse_declaration_clause(test_query, declaration_clause, declared_variables);

        REQUIRE(error == "Invalid Query! Missing synonym.");
    }
}

TEST_CASE("Parses and validate select clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::string condition_query;
    std::vector<pql_dto::Entity> declaration_clause, select_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

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

        REQUIRE(error == "Invalid query! Syntax Error.");
    }

    SECTION("Invalid Select Clause with no declared variable.")
    {
        std::string test_query = "Select s1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "No such variable exists!");
    }

    SECTION("Invalid Select Clause with no tuple variables. (Iteration 1)")
    {
        std::string test_query = "Select <v2, v1> such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "No such variable exists!");
    }

    SECTION("Invalid Select Clause with missing variables.")
    {
        std::string test_query = "Select such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "No such variable exists!");
    }

    SECTION("Invalid Select Clause with addition word before Select.")
    {
        std::string test_query = "var Select v1 such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "Invalid query! Syntax Error.");
    }

    SECTION("Invalid Select Clause with string after Select.")
    {
        std::string test_query = "Select \"v1 \" such that Modifies(4, v1) pattern a(_,_) ";
        std::string error = PQLParser::parse_select_clause(test_query, select_clause, declared_variables, condition_query);

        REQUIRE(error == "No such variable exists!");
    }
}

TEST_CASE("Parses and validate Follows such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

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

        REQUIRE(error == "First param for Follows Relationship is greater than the second param.");
    }

    SECTION("Invalid Such that Clause with Follows variables. Variables as parameters.")
    {
        std::string test_query = "such that Follows(v1, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Follows Relationship First Parameter Type!");
    }

    SECTION("Invalid Such that Clause with Follows variables. Missing parameters.")
    {
        std::string test_query = "such that Follows(a, )";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "No such variable exists!");
    }

    SECTION("Invalid Such that Clause with Follows variables. Invalid Syntax. Missing Params.")
    {
        std::string test_query = "such that Follows()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Syntax! Such that clause syntax error. Missing parameters.");
    }

    SECTION("Invalid Such that Clause with Follows variables. Invalid Syntax. Missing such that")
    {
        std::string test_query = "that Follows(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Syntax! Such that clause syntax error.");
    }

    SECTION("Invalid Such that Clause with Follows variables. Wrong format.")
    {
        std::string test_query = "such that Follows)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Relationship Format!");
    }

    SECTION("Invalid Such that Clause with Follows variables. Wrong entity.")
    {
        std::string test_query = "such that Follows(\"5\", \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Follows Relationship First Parameter Type!");
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

        REQUIRE(error == "First param for Parent Relationship is greater than the second param.");
    }

    SECTION("Invalid Such that Clause with Parent variables. Variables as parameters.")
    {
        std::string test_query = "such that Parent(v1, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Parent Relationship First Parameter Type!");
    }

    SECTION("Invalid Such that Clause with Parent variables. Missing parameters.")
    {
        std::string test_query = "such that Parent(a, )";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "No such variable exists!");
    }

    SECTION("Invalid Such that Clause with Parent variables. Invalid Syntax. Missing Params.")
    {
        std::string test_query = "such that Parent()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Syntax! Such that clause syntax error. Missing parameters.");
    }

    SECTION("Invalid Such that Clause with Parent variables. Invalid Syntax. Missing such that")
    {
        std::string test_query = "that Parent(5, 6)";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Syntax! Such that clause syntax error.");
    }

    SECTION("Invalid Such that Clause with Parent variables. Wrong format.")
    {
        std::string test_query = "such that Parent)()";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Relationship Format!");
    }

    SECTION("Invalid Such that Clause with Parent variables. Wrong entity.")
    {
        std::string test_query = "such that Parent(\"5\", \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "Invalid Parent Relationship First Parameter Type!");
    }
}

TEST_CASE("Parses and validate Uses such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
    std::vector<pql_dto::Entity> declaration_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::string declaration_error = PQLParser::parse_declaration_clause(declaration_query, declaration_clause, declared_variables);

    CHECK(declaration_error == "");

    SECTION("Valid Such that Clause with Uses.")
    {
        std::string test_query = "such that Uses(2, \"x\")";
        std::string error = PQLParser::parse_such_that_clause(test_query, such_that_clause, declared_variables);

        REQUIRE(error == "");
        REQUIRE(such_that_clause.size() == 1);

        CHECK(such_that_clause.at(0).equals(pql_dto::UsesRelationship(pql_dto::Entity("stmt", "2", false),
            pql_dto::Entity("string", "x", false), false)));
    }
}

TEST_CASE("Parses and validate Modifies such that clause.")
{
    /// Initialise declared variables for select clause
    std::unordered_map<std::string, std::string> declared_variables;
    std::string declaration_query = "variable v1, v2; print prt; assign a";
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
            pql_dto::Entity("string", "x", false), false)));
    }
}