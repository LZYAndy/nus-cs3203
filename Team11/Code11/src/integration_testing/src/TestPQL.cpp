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
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23", "28", "29", "30", "31", "32"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("constant")
    {
        string pql_query = "constant c; Select c";
        unordered_set<string> expected_result {"0", "1", "2", "24"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Follows and Follows*")
{
    SECTION("Follows(a, _)")
    {
        string pql_query_1 = "assign a; Select a such that Follows(a, _)";
        string pql_query_2 = "assign a; variable v; Select v such that Follows(a, _)";
        unordered_set<string> expected_result_1 {"1", "10", "11", "12", "15", "16", "17", "21", "29", "31"};
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

    SECTION("Edge case: Follows(s, 100)")
    {
        string pql_query_1 = "stmt s; Select s such that Follows(s, 100)";
        unordered_set<string> expected_result_1 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
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
        unordered_set<string> expected_result {"14", "19", "24", "25", "26", "27"};
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
        string pql_query = "stmt s; if ifs; Select s such that Parent*(ifs, ifs)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(w, ifs)")
    {
        string pql_query = "while w; if ifs; Select w such that Parent(w, ifs)";
        unordered_set<string> expected_result {"24", "26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent(s, a)")
    {
        string pql_query = "assign a; stmt s; Select s such that Parent(s, a)";
        unordered_set<string> expected_result {"14", "19", "25", "27"};
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

    SECTION("Parent*(s, 28)")
    {
        string pql_query = "stmt s; Select s such that Parent*(s, 28)";
        unordered_set<string> expected_result {"24", "25", "26", "27"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(24, s)")
    {
        string pql_query = "stmt s; Select s such that Parent*(24, s)";
        unordered_set<string> expected_result {"25", "26", "27", "28", "29", "30", "31", "32"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Parent*(ifs, s)")
    {
        string pql_query = "if ifs; stmt s; Select s such that Parent*(ifs, s)";
        unordered_set<string> expected_result {"20", "21", "22", "26", "27", "28", "29", "30", "31", "32"};
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
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23", "28", "29", "30", "31", "32"};
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

    SECTION("Modifies(\"whileIfProc\", v)")
    {
        string pql_query = "variable v; Select v such that Modifies(\"whileIfProc\", v)";
        unordered_set<string> expected_result {"x", "y", "count"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(p, v)")
    {
        string pql_query = "procedure p; variable v; Select p such that Modifies(p, v)";
        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid", "whileIfProc"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(r, v)")
    {
        string pql_query = "variable v; read r; Select r such that Modifies(r, v)";
        unordered_set<string> expected_result {"4", "5"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(p, _)")
    {
        string pql_query = "procedure p; Select p such that Modifies(p, _)";
        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid", "whileIfProc"};
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
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23", "28", "29", "30", "31", "32"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(s, \"x\")")
    {
        string pql_query = "stmt s; Select s such that Modifies(s, \"x\")";
        unordered_set<string> expected_result {"2", "4", "24", "25", "26", "27", "30", "13", "18", "14"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Modifies(14, \"x\")")
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

    SECTION("Uses(p, v)")
    {
        // since no call implemented yet, so just regard procedure main first
        string pql_query = "procedure p; variable v; Select p such that Uses(p, v)";
        unordered_set<string> expected_result {"printResults", "computeCentroid", "main"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(a, v)")
    {
        string pql_query = "variable v; assign a; Select a such that Uses(a, v)";
        unordered_set<string> expected_result {"15", "16", "17", "20", "21", "22", "23", "28"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(w, _)")
    {
        string pql_query = "while w; Select w such that Uses(w, _)";
        unordered_set<string> expected_result {"14", "24", "26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(p, \"normSq\")")
    {
        string pql_query = "procedure p; Select p such that Uses(p, \"normSq\")";
        unordered_set<string> expected_result {"printResults", "main"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Uses(a, _)")
    {
        string pql_query = "assign a; Select a such that Uses(a, _)";
        unordered_set<string> expected_result {"15", "16", "17", "20", "21", "22", "23", "28"};
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

TEST_CASE("One such that clause: Calls and Calls*")
{
    SECTION("Calls(p, _)")
    {
        string pql_query_1 = "procedure p; Select p such that Calls(p, _)";
        unordered_set<string> expected_result_1 {"main", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Calls(p, _)")
    {
        string pql_query_1 = "procedure p; Select p such that Calls(_, p)";
        unordered_set<string> expected_result_1 {"readPoint", "printResults", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Calls(p, \"readPoint\")")
    {
        string pql_query_1 = "procedure p; Select p such that Calls(p, \"readPoint\")";
        unordered_set<string> expected_result_1 {"computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Edge case: Calls(p, \"fakeProc\")")
    {
        string pql_query_1 = "procedure p; Select p such that Calls(p, \"fakeProc\")";
        unordered_set<string> expected_result_1 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }


    SECTION("Calls(p, p)")
    {
        string pql_query = "procedure p; Select p such that Calls(p, p)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Calls(p1, p2)")
    {
        string pql_query_1 = "procedure p1; procedure p2; Select <p1, p2> such that Calls(p1, p2)";
        unordered_set<string> expected_result_1 {"main computeCentroid", "main printResults", "computeCentroid readPoint"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Calls(_, _)")
    {
        string pql_query = "Select BOOLEAN such that Calls(_, _)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Calls(_, \"computeCentroid\")")
    {
        string pql_query_1 = "Select BOOLEAN such that Calls(_, \"computeCentroid\")";
        string pql_query_2 = "Select BOOLEAN such that Calls(_, \"whileIfProc\")";
        unordered_set<string> expected_result_1 {"TRUE"};
        unordered_set<string> expected_result_2 {"FALSE"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Calls(\"main\", \"computeCentroid\")")
    {
        string pql_query_1 = R"(Select BOOLEAN such that Calls("main", "computeCentroid"))";
        string pql_query_2 = R"(Select BOOLEAN such that Calls("main", "whileIfProc"))";
        unordered_set<string> expected_result_1 {"TRUE"};
        unordered_set<string> expected_result_2 {"FALSE"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Calls*(p, \"readPoint\")")
    {
        string pql_query = "procedure p; Select p such that Calls*(p, \"readPoint\")";
        unordered_set<string> expected_result {"main", "computeCentroid"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Calls*(p1, p2)")
    {
        string pql_query = "procedure p1; procedure p2; Select <p1, p2> such that Calls*(p1, p2)";
        unordered_set<string> expected_result {"main computeCentroid", "main printResults", "computeCentroid readPoint", "main readPoint"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Calls*(_, _)")
    {
        string pql_query = "Select BOOLEAN such that Calls*(_, _)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Calls*(\"main\", \"readPoint\")")
    {
        string pql_query_1 = R"(Select BOOLEAN such that Calls*("main", "computeCentroid"))";
        unordered_set<string> expected_result_1 {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Calls*(\"main\", p)")
    {
        string pql_query = "procedure p; Select p such that Calls*(\"main\", p)";
        unordered_set<string> expected_result {"computeCentroid", "printResults", "readPoint"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause: Next and Next*")
{
    SECTION("Next(cl, _)")
    {
        string pql_query_1 = "call cl; Select cl such that Next(cl, _)";
        unordered_set<string> expected_result_1 {"2", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Next(_, cl)")
    {
        string pql_query_1 = "call cl; Select cl such that Next(_, cl)";
        unordered_set<string> expected_result_1 {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Next(s, 15)")
    {
        string pql_query_1 = "stmt s; Select s such that Next(s, 15)";
        string pql_query_2 = "stmt s; Select s such that Next(s, 1)";
        unordered_set<string> expected_result_1 {"14"};
        unordered_set<string> expected_result_2 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Next(14, s)")
    {
        string pql_query_1 = "stmt s; Select s such that Next(14, s)";
        string pql_query_2 = "stmt s; Select s such that Next(23, s)";
        unordered_set<string> expected_result_1 {"15", "19"};
        unordered_set<string> expected_result_2 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
        REQUIRE(QueryEvaluator::get_result(pql_query_2, PKB) == expected_result_2);
    }

    SECTION("Edge case: Next(s, 100)")
    {
        string pql_query_1 = "stmt s; Select s such that Next(s, 100)";
        unordered_set<string> expected_result_1 {};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }


    SECTION("Next(s, s)")
    {
        string pql_query = "stmt s; Select s such that Next(s, s)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next(ifs, s)")
    {
        string pql_query_1 = "if ifs; stmt s; Select <ifs, s> such that Next(ifs, s)";
        unordered_set<string> expected_result_1 {"19 20", "19 21", "25 26", "25 31", "27 28", "27 29"};
        REQUIRE(QueryEvaluator::get_result(pql_query_1, PKB) == expected_result_1);
    }

    SECTION("Next(_, _)")
    {
        string pql_query = "call cl; Select cl such that Next(_, _)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next(_, 2)")
    {
        string pql_query = "call cl; Select cl such that Next(_, 2)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next(26, 24)")
    {
        string pql_query = "call cl; Select cl such that Next(26, 24)";
        unordered_set<string> expected_result {"2", "3", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(cl, 24)")
    {
        string pql_query = "call cl; Select cl such that Next*(cl, 22)";
        unordered_set<string> expected_result {"13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(cl, cl)")
    {
        string pql_query = "call cl; Select cl such that Next*(cl, cl)";
        unordered_set<string> expected_result {"18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(cl1, cl2)")
    {
        string pql_query = "call cl1; call cl2; Select cl1 such that Next*(cl1, cl2)";
        unordered_set<string> expected_result {"2", "13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(10, cl)")
    {
        string pql_query = "call cl; Select cl such that Next*(10, cl)";
        unordered_set<string> expected_result {"13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(10, cl)")
    {
        string pql_query = "call cl; Select cl such that Next*(10, cl)";
        unordered_set<string> expected_result {"13", "18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(_, _)")
    {
        string pql_query = "call cl; Select BOOLEAN such that Next*(_, _)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Next*(10, 15)")
    {
        string pql_query = "call cl; Select BOOLEAN such that Next*(10, 15)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("Affects clause")
{
    SECTION("Affects(a, _)")
    {
        string pql_query = "assign a; Select a such that Affects(a, _)";
        unordered_set<string> expected_result {"10", "11", "12", "15", "16", "17", "21", "22", "32"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(a, 15)")
    {
        string pql_query = "assign a; Select a such that Affects(a, 15)";
        unordered_set<string> expected_result {"10", "15"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(a, a)")
    {
        string pql_query = "assign a; Select a such that Affects(a, a)";
        unordered_set<string> expected_result {"15", "16", "17"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(_, a)")
    {
        string pql_query = "assign a; Select a such that Affects(_, a)";
        unordered_set<string> expected_result {"15", "16", "17", "20", "21", "22", "23", "28"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(21, a)")
    {
        string pql_query = "assign a; Select a such that Affects(21, a)";
        unordered_set<string> expected_result {"23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(_, _)")
    {
        string pql_query = "assign a; Select BOOLEAN such that Affects(_, _)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(10, 15)")
    {
        string pql_query = "assign a; Select BOOLEAN such that Affects(10, 15)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects*(a, 23)")
    {
        string pql_query = "assign a; Select a such that Affects*(a, 23)";
        unordered_set<string> expected_result {"10", "11", "12", "15", "16", "17", "21", "22"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects*(a, a)")
    {
        string pql_query = "assign a; Select a such that Affects*(a, a)";
        unordered_set<string> expected_result {"15", "16", "17"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects*(11, a)")
    {
        string pql_query = "assign a; Select a such that Affects*(11, a)";
        unordered_set<string> expected_result {"16", "20", "21", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects*(_, _)")
    {
        string pql_query = "assign a; Select BOOLEAN such that Affects*(_, _)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("Affects(11, 23)")
    {
        string pql_query = "assign a; Select BOOLEAN such that Affects(11, 23)";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("With clause")
{
    SECTION("with c.value = cl.stmt#")
    {
        string pql_query = "constant c; call cl; Select cl with c.value = cl.stmt#";
        unordered_set<string> expected_result {"2"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }


    SECTION("with p.procName = cl.procName")
    {
        string pql_query = "procedure p; call cl; Select cl.procName with p.procName = cl.procName";
        unordered_set<string> expected_result {"computeCentroid", "printResults", "readPoint"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with cl.procName = \"printResults\"")
    {
        string pql_query = "call cl; Select cl with cl.procName = \"printResults\"";
        unordered_set<string> expected_result {"3"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with cl.procName = \"printResults\"")
    {
        string pql_query = "call cl; Select cl.procName with cl.procName = \"printResults\"";
        unordered_set<string> expected_result {"printResults"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with cl.procName = \"printResults\"")
    {
        string pql_query = "call cl; Select BOOLEAN with cl.procName = \"printResults\"";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with \"printResults\" = cl.procName")
    {
        string pql_query = "call cl; Select cl with \"printResults\" = cl.procName";
        unordered_set<string> expected_result {"3"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with cl.stmt# = 18")
    {
        string pql_query = "call cl; Select cl with cl.stmt# = 18";
        unordered_set<string> expected_result {"18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with 18 = cl.stmt#")
    {
        string pql_query = "call cl; Select cl with 18 = cl.stmt#";
        unordered_set<string> expected_result {"18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with n = 16")
    {
        string pql_query = "prog_line n; Select BOOLEAN with n = 16";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with \"x\" = r.varName")
    {
        string pql_query = "read r; Select r with \"x\" = r.varName";
        unordered_set<string> expected_result {"4"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("with 0 = c.value")
    {
        string pql_query = "constant c; Select c.value with 0 = c.value";
        unordered_set<string> expected_result {"0"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One pattern clause: Assign")
{
    SECTION("pattern a(_, _)")
    {
        string pql_query = "assign a; Select a pattern a(_, _)";
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23", "28", "29", "30", "31", "32"};
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
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "normSq", "x", "y"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(_, _\"x\"_)")
    {
        string pql_query = "assign a; Select a pattern a(_, _\"cenX\"_)";
        unordered_set<string> expected_result {"16", "20", "21", "23"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(_, _\"cenX/count\"_)")
    {
        string pql_query = R"(assign a; Select a pattern a(_, _"cenX/count"_))";
        unordered_set<string> expected_result {"21"};
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
        unordered_set<string> expected_result {"1", "10", "11", "12", "29"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(\"count\", \"0\")")
    {
        string pql_query = R"(assign a; Select a pattern a("count", "0"))";
        unordered_set<string> expected_result {"10", "29"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(v, \"0\")")
    {
        string pql_query = "assign a; variable v; Select a pattern a(_, \"t\")";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One pattern clause: If")
{
    SECTION("pattern ifs(_, _, _)")
    {
        string pql_query = "if ifs; Select ifs pattern ifs(_, _, _)";
        unordered_set<string> expected_result {"19", "25", "27"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern ifs(\"count\", _, _)")
    {
        string pql_query = "if ifs; Select ifs pattern ifs(\"count\", _, _)";
        unordered_set<string> expected_result {"19"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern ifs(v, _, _)")
    {
        string pql_query = "if ifs; variable v; Select <ifs, v> pattern ifs(v, _, _)";
        unordered_set<string> expected_result {"19 count", "25 y", "27 cenX"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One pattern clause: While")
{
    SECTION("pattern w(_, _)")
    {
        string pql_query = "while w; Select w pattern w(_, _)";
        unordered_set<string> expected_result {"14", "24", "26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern w(\"x\", _)")
    {
        string pql_query = "while w; Select w pattern w(\"x\", _)";
        unordered_set<string> expected_result {"14", "24"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern w(v, _)")
    {
        string pql_query = "while w; variable v; Select <w, v> pattern w(v, _)";
        unordered_set<string> expected_result {"14 x", "14 y", "24 x", "26 count"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("One such that clause and one pattern clause")
{
    SECTION("such that Modifies(a, _) pattern a(\"cenX\", _\"x \"_)")
    {
        string pql_query = R"(assign a; stmt s; variable v; if ifs; Select v such that Parent*(ifs, a) pattern a(v, _"y"_))";
        unordered_set<string> expected_result {"count"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("pattern a(\"count\", _) such that Parent*(w, a)")
    {
        string pql_query = "assign a; while w; Select a pattern a(\"count\", _) such that Parent*(w, a)";
        unordered_set<string> expected_result {"15", "28", "29", "31"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("such that Uses(a, \"x\") pattern a(\"x\", _)")
    {
        string pql_query = R"(assign a; Select a pattern such that Uses(a, "x") pattern a("x", _))";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}

TEST_CASE("Multiple select, such that, and pattern")
{
    SECTION("select tuple")
    {
        string pql_query = "assign a; while w; variable v; Select <a,w> pattern a(\"count\", _) such that Parent*(w, a)";
        unordered_set<string> expected_result {"15 14", "28 24", "28 26", "29 24", "29 26", "31 24"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "assign a; while w; variable v; Select <a,w> pattern a(\"count\", _) such that Parent*(w, a) and Uses(a, v)";
        unordered_set<string> expected_result {"15 14", "28 24", "28 26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    { // v = "count", "cenX", "cenY", "x", "y"; s = 24, 25, 26, 27
        string pql_query = "variable v; stmt s; Select <v, s> such that Modifies(14, v) and Parent*(s, 28)";
        unordered_set<string> expected_result {"count 24", "count 25", "count 26", "count 27", "cenX 24", "cenX 25", "cenX 26", "cenX 27", "cenY 24", "cenY 25", "cenY 26", "cenY 27",  "x 24", "x 25", "x 26", "x 27", "y 24", "y 25", "y 26", "y 27"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple with attr, multiple clauses")
    {
        string pql_query = "call cl; Select <cl, cl.procName, cl.stmt#>";
        unordered_set<string> expected_result {"2 computeCentroid 2", "3 printResults 3", "13 readPoint 13", "18 readPoint 18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple with attr, multiple clauses")
    {
        string pql_query = "call cl; assign a; Select <cl, cl.procName, a> such that Follows(a, cl) ";
        unordered_set<string> expected_result {"2 computeCentroid 1", "13 readPoint 12", "18 readPoint 17"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "assign a; Select a such that Follows*(a, 1) and Follows*(a, 2) ";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "procedure p; call cl; Select <p, cl> such that Next(1, 2)";
        unordered_set<string> expected_result {"main 2", "main 3", "main 13", "main 18", "readPoint 2", "readPoint 3", "readPoint 13", "readPoint 18", "printResults 2", "printResults 3", "printResults 13", "printResults 18", "computeCentroid 2", "computeCentroid 3", "computeCentroid 13", "computeCentroid 18", "whileIfProc 2", "whileIfProc 3", "whileIfProc 13", "whileIfProc 18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "call cl; Select <cl, cl, cl> such that Follows*(_, _)";
        unordered_set<string> expected_result {"2 2 2", "3 3 3", "13 13 13", "18 18 18"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "constant c; Select c.value with c.value = 0";
        unordered_set<string> expected_result {"0"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "variable v; if ifs; assign a; Select v pattern ifs(v, _,_) and a(v, _\"cenX\"_)";
        unordered_set<string> expected_result {"cenX"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "variable v; if ifs; assign a; Select v pattern ifs(v, _,_) and a(v, _\"cenX\"_)";
        unordered_set<string> expected_result {"cenX"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("error")
    {
        string pql_query = "procedure p; stmt s; Select s such that Affects(s, p)";
        unordered_set<string> expected_result {};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "assign a, a1; Select BOOLEAN with a.stmt# = a1.stmt# and a1.stmt# = a1.stmt# and a.stmt# = a.stmt#";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select BOOLEAN, multiple clauses")
    {
        string pql_query = R"(procedure pcd1; stmt sd1; assign ad1; call cd1; while wd1; if ifsd1; read rd1; print pd1; variable vd1; procedure pc1; stmt s1; assign a1; call c1; while w1; if ifs1; read r1; print p1; variable v1; procedure pc2; stmt s2; assign a2; call c2; while w2; if ifs2; read r2; print p2; variable v2; procedure pc3; stmt s3; assign a3; call c3; while w3; if ifs3; read r3; print p3; variable v3; procedure pc4; stmt s4; assign a4; call c4; while w4; if ifs4; read r4; print p4; variable v4; Select BOOLEAN such that Calls*("main", pc1) with pc1.procName = "readPoint")";
        unordered_set<string> expected_result {"TRUE"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "while w; if ifs; assign a; variable v; Select <a, ifs, w> pattern ifs(v, _, _) and a(v, _) and w(v, _) with v.varName = \"count\"";
        unordered_set<string> expected_result {"29 19 26", "31 19 26", "28 19 26", "15 19 26", "10 19 26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "assign a1, a2, a3; Select <a1, a2, a3> such that Affects(a1, a2) and Affects(a2, a3) and Affects(a3, a1)";
        unordered_set<string> expected_result {"16 16 16", "15 15 15", "17 17 17"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = "while w; Select w with 05 = 0005";
        unordered_set<string> expected_result {"14", "24", "26"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }

    SECTION("select tuple, multiple clauses")
    {
        string pql_query = R"(while w1, w2; if ifs; assign a1,a2; constant c; Select <ifs, a2> such that Parent(w1, ifs) and Next*(w1, a1) pattern a1(_, _"y"_) such that Next*(a1, a2) pattern a2(_, _"y"_) with w1.stmt# = c.value)";
        unordered_set<string> expected_result {"25 28"};
        REQUIRE(QueryEvaluator::get_result(pql_query, PKB) == expected_result);
    }
}
