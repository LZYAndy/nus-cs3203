#include "catch.hpp"
#include "PQLParser.h"

TEST_CASE("Pql query parser parse and validate valid query correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;

    SECTION("Valid query 1.")
    {
        std::string test_query = "variable v; Select v";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 2.")
    {
        std::string test_query = "variable v; Select v such that Uses(6, v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 3.")
    {
        std::string test_query = "variable v; assign a; Select v pattern a (\"x\",_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 4.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 such that Modifies(4, v1) pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 5.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 pattern a (_,_) such that Modifies(4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 6.")
    {
        std::string test_query = "         variable v1\t, v2\n; assign a; Select v1 pattern a(_,          _) such  \v that    Modifies    (4, v1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 7.")
    {
        std::string test_query = "while w;\nSelect w such that Parent(w, 7)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 8.")
    {
        std::string test_query = "while w;\nSelect w such that Parent(w, 7) and Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
    }

    SECTION("Valid query 9.")
    {
        std::string test_query = "while w;\nSelect w such that Parent(w, 7) and Follows(w, 8) pattern w (\"x\", _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 1);
    }

    SECTION("Valid query 9.")
    {
        std::string test_query = "while w; if ifs;\nSelect w such that Parent(w, 7) and Follows(w, 8) pattern w (\"x\", _) and ifs (\"x\", _, _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 2);
    }

    SECTION("Valid query 10.")
    {
        std::string test_query = "while w; if ifs;\nSelect w such that Parent(w, 7) and Follows(w, 8) with w.stmt# = 5";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 11.")
    {
        std::string test_query = "while w; if ifs;\nSelect w with w.stmt# = 5 such that Parent(w, 7) and Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 12.")
    {
        std::string test_query = "while w; if ifs;\nSelect w with 5 = w.stmt# such that Parent(w, 7) and Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 13.")
    {
        std::string test_query = "Select BOOLEAN such that Calls*(_, _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 14.")
    {
        std::string test_query = "procedure p1; procedure p2; Select <p1, p2> such that Calls*(p1, p2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 15.")
    {
        std::string test_query = "Select BOOLEAN such that Calls*(\"main\", \"computeCentroid\")";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 16.")
    {
        std::string test_query = "Select BOOLEAN such that Calls(_, \"computeCentroid\")";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 17.")
    {
        std::string test_query = "Select BOOLEAN such that Calls(_, _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 18.")
    {
        std::string test_query = "procedure p1; procedure p2; Select <p1, p2> such that Calls(p1, p2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 19.")
    {
        std::string test_query = "if ifs; stmt s; Select <ifs, s> such that Next(ifs, s)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 20.")
    {
        std::string test_query = "if ifs; variable v; Select <ifs, v> pattern ifs(v, _, _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 1);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 21.")
    {
        std::string test_query = "while w; variable v; Select <w, v> pattern w(v, _)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 1);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 22.")
    {
        std::string test_query = "while w; if ifs;\nSelect w with w   .    stmt# = 5 such that Parent(w, 7) and Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 23.")
    {
        std::string test_query = "while w; if ifs;\nSelect w with w.    stmt# = 5 such that Parent(w, 7) and Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 24.")
    {
        std::string test_query = "procedure p1; procedure p2; Select <    p1\n,\t p2\n> such that Calls     (p1, p2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 25.")
    {
        std::string test_query = "procedure p1; procedure p2; Select <    p1\n,\t p2\n>such that Calls  *   (p1, p2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 2);
        REQUIRE(such_that_clause.size() == 1);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 26.")
    {
        std::string test_query = "while w; if ifs;\nSelect w with w.    stmt# = 5 such that Parent(w, 7)and\n Follows(w, 8)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 2);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 1);
    }

    SECTION("Valid query 27.")
    {
        std::string test_query = "assign a; variable v; Select a pattern a(v, \"(b+c*(b-q/(abc%d)))/e%a\")";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 0);
        REQUIRE(pattern_clause.size() == 1);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 28.")
    {
        std::string test_query = "assign a, a1; variable v; Select a such that Affects(1,2) and Affects  * (a, 4) and AffectsBip(a1, a)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 3);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }

    SECTION("Valid query 29.")
    {
        std::string test_query = "assign a, a1; stmt s1; variable v; Select a such that Next(1,2) and Next  * (a, 4) and NextBip*(a1, s1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == "");
        REQUIRE(select_clause.size() == 1);
        REQUIRE(such_that_clause.size() == 3);
        REQUIRE(pattern_clause.size() == 0);
        REQUIRE(with_clause.size() == 0);
    }
}

TEST_CASE("Pql query parser parse and validate invalid query correctly.")
{
    std::vector<pql_dto::Entity> declaration_clause, select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;

    SECTION("Invalid query 1.")
    {
        std::string test_query = "variable v; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_variables_not_declared);
    }

    SECTION("Invalid query 2.")
    {
        std::string test_query = "variable v; assign a; Select v such that Uses(6, v) and pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_relationship_type);
    }

    SECTION("Invalid query 3.")
    {
        std::string test_query = "variable v; assign a; Select v pattern a (\"x\",_) and such that Modifies (6, v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_wrong_pattern_entity);
    }

    SECTION("Invalid query 4.")
    {
        std::string test_query = "variable v1, v2; assign a; Select v1 such that Modifies(_, v1) pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_modifies_relationship_first_param);
    }

    SECTION("Invalid query 5.")
    {
        std::string test_query = "variable v1 v2; assign a; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_declared_entity_name);
    }

    SECTION("Invalid query 6.")
    {
        std::string test_query = "variable v1, v2; assignment a; Select v1";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_entity_type);
    }

    SECTION("Invalid query 7.")
    {
        std::string test_query = "while w;Select w;";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_declaration_duplicate_synonyms);
    }

    SECTION("Invalid query 8.")
    {
        std::string test_query = ";Select w;";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_declaration_clause_syntax);
    }

    SECTION("Invalid query 9.")
    {
        std::string test_query = "variable v; assign a; Select v such that Uses(6, v) and such that Uses(6, v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_relationship_type);
    }

    SECTION("Invalid query 10.")
    {
        std::string test_query = "variable v1, v2; assign a; if ifs; Select v1 pattern ifs (_,_,v1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_pattern_clause_syntax);
    }

    SECTION("Invalid query 11.")
    {
        std::string test_query = "variable v1, v2; assign a; if ifs; Select v1 pattern if (_,_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_query_wrong_pattern_entity);
    }

    SECTION("Invalid query 12.")
    {
        std::string test_query = "variable v1, v2; assign a; while w; Select v1 pattern w (v2,v1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_pattern_second_param);
    }

    SECTION("Invalid query 13.")
    {
        std::string test_query = "variable v1, v2; assign a; while w; Select v1 pattern w (v,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        REQUIRE(error == error_messages::invalid_declared_entity_name);
    }
}

