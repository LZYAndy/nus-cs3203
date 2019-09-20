#include "catch.hpp"
#include "./../../spa/src/QueryEvaluator.h"
#include "PKBStub.cpp"

using namespace std;

PKBStub PKB;

TEST_CASE("No such that or pattern clauses")
{
    SECTION("variable")
    {
        string pql_query = "variable v; Select v";
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("assign")
    {
        string pql_query = "assign a; Select a";
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Follows and Follows*")
{
    SECTION("Follows(a, _)")
    {
        string pql_query_1 = "assign a; Select a such that Follows(a, _)";
        string pql_query_2 = "assign a; variable v; Select v such that Follows(a, _)";
        unordered_set<string> expected_result_1 {"1", "10", "11", "12", "15", "16", "17", "21"};
        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Follows(s, 12)")
    {
        string pql_query_1 = "stmt s; Select s such that Follows(s, 12)";
        string pql_query_2 = "stmt s; variable v; Select v such that Follows(s, 12)";
        string pql_query_3 = "stmt s; Select s such that Follows(s, 15)";
        unordered_set<string> expected_result_1 {"11"};
        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        unordered_set<string> expected_result_3 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
        REQUIRE(QueryEvaluator::get_result(pql_query_3, PKB) == expected_result_3);
    }

    SECTION("Follows(s, s)")
    {
        string pql_query = "stmt s; Select s such that Follows(s, s)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows(s, cl)")
    {
        string pql_query_1 = "call cl; stmt s; Select s such that Follows(s, cl)";
        string pql_query_2 = "call cl; while w; variable v; Select v such that Follows(cl, w)";
        unordered_set<string> expected_result_1 {"1", "2", "12", "17"};
        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Follows(_, _)")
    {
        string pql_query = "call cl; Select cl such that Follows(_, _)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows(_, 2)")
    {
        string pql_query = "call cl; Select cl such that Follows(_, 2)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows*(s, 12)")
    {
        string pql_query = "stmt s; Select s such that Follows*(s, 12)";
        unordered_set<string> expected_result {"10", "11"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows*(s, cl)")
    {
        string pql_query = "call cl; stmt s; Select s such that Follows*(s, cl)";
        unordered_set<string> expected_result {"1", "2", "10", "11", "12", "15", "16", "17"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows*(_, _)")
    {
        string pql_query = "call cl; Select cl such that Follows*(_, _)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Follows*(_, 12)")
    {
        string pql_query = "call cl; Select cl such that Follows*(_, 12)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Parent and Parent*")
{
    SECTION("Parent(s, _)")
    {
        string pql_query = "stmt s; Select s such that Parent(s, _)";
        unordered_set<string> expected_result {"14", "19"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(s, 15)")
    {
        string pql_query = "stmt s; Select s such that Parent(s, 15)";
        unordered_set<string> expected_result {"14"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(s, s)")
    {
        string pql_query = "stmt s; Select s such that Parent(s, s)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(s, a)")
    {
        string pql_query = "assign a; stmt s; Select s such that Parent(s, a)";
        unordered_set<string> expected_result {"14", "19"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(_, _)")
    {
        string pql_query = "call cl; Select cl such that Parent(_, _)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(_, 2)")
    {
        string pql_query_1 = "call cl; Select cl such that Parent(_, 2)";
        string pql_query_2 = "call cl; Select cl such that Parent(_, 22)";
        unordered_set<string> expected_result_1 {};
        unordered_set<string> expected_result_2 {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Parent*(s, 18)")
    {
        string pql_query = "stmt s; Select s such that Parent*(s, 18)";
        unordered_set<string> expected_result {"14"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(19, s)")
    {
        string pql_query = "stmt s; Select s such that Parent*(19, s)";
        unordered_set<string> expected_result {"20", "21", "22"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(s, cl)")
    {
        string pql_query = "call cl; stmt s; Select s such that Parent*(s, cl)";
        unordered_set<string> expected_result {"14"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(_, _)")
    {
        string pql_query = "call cl; Select cl such that Parent*(_, _)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(_, 17)")
    {
        string pql_query = "assign a; Select a such that Parent*(_, 17)";
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Modifies")
{
    SECTION("Modifies(1, v)")
    {
        string pql_query = "variable v; Select v such that Modifies(1, v)";
        unordered_set<string> expected_result {"flag"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

//    SECTION("Modifies(\"main\", v)")
//    {
//        string pql_query = "variable v; Select v such that Modifies(\"main\", v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result == expected_result);
//    }

    SECTION("Modifies(p, v)")
    {
        string pql_query = "procedure p; variable v; Select p such that Modifies(p, v)";
        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

//    SECTION("Modifies(s, v)")
//    {
//        string pql_query = "variable v; stmt s; Select s such that Modifies(s, v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"1", "2", "4", "5", "10", "11", "12", "13", "14", "15", "16", "17",
//                                               "18", "19", "20", "21", "22", "23"};
//        REQUIRE(my_result == expected_result);
//    }

    SECTION("Modifies(p, _)")
    {
        string pql_query = "procedure p; Select p such that Modifies(p, _)";
        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(p, \"flag\")")
    {
        string pql_query = "procedure p; Select p such that Modifies(p, \"flag\")";
        unordered_set<string> expected_result {"main", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(a, _)")
    {
        string pql_query = "assign a; Select a such that Modifies(a, _)";
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(s, \"x\")")
    {
        string pql_query = "stmt s; Select s such that Modifies(s, \"x\")";
        unordered_set<string> expected_result {"4"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(1, \"x\")")
    {
    string pql_query = "call cl; Select cl such that Modifies(14, \"cenX\")";
    unordered_set<string> expected_result {"2", "3", "13", "18"};
    REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Uses")
{
    SECTION("Uses(15, v)")
    {
        string pql_query = "variable v; Select v such that Modifies(15, v)";
        unordered_set<string> expected_result {"count"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(\"computeCentroid\", v)")
    {
        string pql_query = "variable v; Select v such that Uses(\"computeCentroid\", v)";
        unordered_set<string> expected_result {"count", "cenX", "cenY", "x", "y"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

//    SECTION("Uses(p, v)")
//    {
//        string pql_query = "procedure p; variable v; Select p such that Uses(p, v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid"};
//        REQUIRE(my_result == expected_result);
//    }

    SECTION("Uses(a, v)")
    {
        string pql_query = "variable v; assign a; Select a such that Uses(a, v)";
        unordered_set<string> expected_result {"15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(w, _)")
    {
        string pql_query = "while w; Select w such that Uses(w, _)";
        unordered_set<string> expected_result {"14"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(p, \"normSq\")")
    {
        string pql_query = "procedure p; Select p such that Uses(p, \"normSq\")";
        unordered_set<string> expected_result {"printResults"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(a, _)")
    {
        string pql_query = "assign a; Select a such that Uses(a, _)";
        unordered_set<string> expected_result {"15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(a, \"x\")")
    {
        string pql_query = "assign a; Select a such that Uses(a, \"x\")";
        unordered_set<string> expected_result {"16"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(14, \"x\")")
    {
        string pql_query = "call cl; Select cl such that Uses(14, \"x\")";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One pattern clause: Assign")
{
    SECTION("pattern a(_, _)")
    {
        string pql_query = "assign a; Select a pattern a(_, _)";
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(\"flag\", _)")
    {
        string pql_query = "assign a; Select a pattern a(\"flag\", _)";
        unordered_set<string> expected_result {"1", "20"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(v, _)")
    {
        string pql_query = "assign a; variable v; Select v pattern a(v, _)";
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "normSq"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(_, _\"x\"_)")
    {
        string pql_query = "assign a; Select a pattern a(_, _\"cenX\"_)";
        unordered_set<string> expected_result {"16", "20", "21", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(\"cenX\", _\"cenX\"_)")
    {
        string pql_query = R"(assign a; Select a pattern a("cenX", _"cenX"_))";
        unordered_set<string> expected_result {"16", "21"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(v, _\"cenX\"_)")
    {
        string pql_query = "assign a; variable v; Select v pattern a(v, _\"cenX\"_)";
        unordered_set<string> expected_result {"cenX", "flag", "normSq"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(_, \"0\")")
    {
        string pql_query = "assign a; Select a pattern a(_, \"0\")";
        unordered_set<string> expected_result {"1", "10", "11", "12"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(\"count\", \"0\")")
    {
        string pql_query = R"(assign a; Select a pattern a("count", "0"))";
        unordered_set<string> expected_result {"10"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(v, \"0\")")
    {
        string pql_query = "assign a; variable v; Select v pattern a(v, \"0\")";
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause and one pattern clause")
{
    SECTION("Uses(a, v) pattern a(v, _)")
    {
        string pql_query = "assign a; variable v; Select v such that Uses(a, v) pattern a(v, _)";
        unordered_set<string> expected_result {"count", "cenX", "cenY"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }


}