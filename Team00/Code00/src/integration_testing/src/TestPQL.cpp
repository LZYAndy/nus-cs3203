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
        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("assign")
    {
        string pql_query = "assign a; Select a";
        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(my_result == expected_result);
    }
}

TEST_CASE("One such that clause: Follows and Follows*")
{
    SECTION("Follows(a, _)")
    {
        string pql_query_1 = "assign a; Select a such that Follows(a, _)";
        string pql_query_2 = "assign a; variable v; Select v such that Follows(a, _)";
        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1, PKB);
        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2, PKB);
        unordered_set<string> expected_result_1 {"1", "10", "11", "12", "15", "16", "17", "21"};
        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(my_result_1 == expected_result_1);
        REQUIRE(my_result_2 == expected_result_2);
    }

    SECTION("Follows(s, 12)")
    {
        string pql_query_1 = "stmt s; Select s such that Follows(s, 12)";
        string pql_query_2 = "stmt s; variable v; Select v such that Follows(s, 12)";
        string pql_query_3 = "stmt s; Select s such that Follows(s, 15)";
        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1, PKB);
        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2, PKB);
        unordered_set<string> my_result_3 = QueryEvaluator::get_result(pql_query_3, PKB);
        unordered_set<string> expected_result_1 {"11"};
        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        unordered_set<string> expected_result_3 {};
        REQUIRE(my_result_1 == expected_result_1);
        REQUIRE(my_result_2 == expected_result_2);
        REQUIRE(my_result_3 == expected_result_3);
    }

//    SECTION("Follows(s, s)")
//    {
//        string pql_query = "stmt s; Select s such that Follows(s, s)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows(s, cl)")
//    {
//        string pql_query_1 = "call cl; stmt s; Select s such that Follows(s, cl)";
//        string pql_query_2 = "call cl; stmt s; variable v; Select v such that Follows(cl, w)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1, PKB);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2, PKB);
//        unordered_set<string> expected_result_1 {"12", "17"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//    SECTION("Follows(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Follows(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows(_, 2)")
//    {
//        string pql_query = "call cl; Select cl such that Follows(_, 2)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(s, 12)")
//    {
//        string pql_query = "stmt s; Select s such that Follows*(s, 12)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"10", "11"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(s, cl)")
//    {
//        string pql_query = "call cl; stmt s; Select s such that Follows*(s, cl)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"10", "11", "12", "15", "16", "17"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Follows*(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(_, 12)")
//    {
//        string pql_query = "call cl; Select cl such that Follows*(_, 12)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//}
//
//TEST_CASE("One such that clause: Parent and Parent*")
//{
//    SECTION("Parent(s, _)")
//    {
//        string pql_query = "stmt s; Select s such that Parent(s, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"14", "19"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent(s, 15)")
//    {
//        string pql_query = "stmt s; Select s such that Parent(s, 15)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"14"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent(s, s)")
//    {
//        string pql_query = "stmt s; Select s such that Parent(s, s)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent(s, a)")
//    {
//        string pql_query = "assign a; stmt s; Select s such that Parent(s, a)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"14", "19"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Parent(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent(_, 2)")
//    {
//        string pql_query_1 = "call cl; Select cl such that Parent(_, 2)";
//        string pql_query_2 = "call cl; Select cl such that Parent(_, 22)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1, PKB);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2, PKB);
//        unordered_set<string> expected_result_1 {};
//        unordered_set<string> expected_result_2 {"2", "3", "13", "18"};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//    SECTION("Parent*(s, 18)")
//    {
//        string pql_query = "stmt s; Select s such that Parent*(s, 18)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"14"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent*(19, s)")
//    {
//        string pql_query = "stmt s; Select s such that Parent*(19, s)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"20", "21", "22"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent*(s, cl)")
//    {
//        string pql_query = "call cl; stmt s; Select s such that Parent*(s, cl)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"14"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent*(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Parent*(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Parent*(_, 12)")
//    {
//        string pql_query = "assign a; Select a such that Parent*(_, 12)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
//        REQUIRE(my_result == expected_result);
//    }
//}
//
//TEST_CASE("One such that clause: Modifies")
//{
//    SECTION("Modifies(1, v)")
//    {
//        string pql_query = "variable v; Select v such that Modifies(1, v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"flag"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Modifies(\"main\", v)")
//    {
//        string pql_query = "variable v; Select v such that Modifies(\"main\", v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Modifies(p, v)")
//    {
//        string pql_query = "procedure p; Select p such that Modifies(p, v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Modifies(s, v)")
//    {
//        string pql_query = "variable v; stmt s; Select s such that Modifies(s, v)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"1", "2", "4", "5", "10", "11", "12", "13", "14", "15", "16", "17",
//                                               "18", "19", "20", "21", "22", "23"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Modifies(p, _)")
//    {
//        string pql_query = "procedure p; Select p such that Modifies(p, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//        unordered_set<string> expected_result {"main", "readPoint", "computeCentroid"};
//        REQUIRE(my_result == expected_result);
//    }






//SECTION("Parent(_, 2)")
//{
//string pql_query_1 = "call cl; Select cl such that Parent(_, 2)";
//string pql_query_2 = "call cl; Select cl such that Parent(_, 22)";
//unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1, PKB);
//unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2, PKB);
//unordered_set<string> expected_result_1 {};
//unordered_set<string> expected_result_2 {"2", "3", "13", "18"};
//REQUIRE(my_result_1 == expected_result_1);
//REQUIRE(my_result_2 == expected_result_2);
//}
//
//SECTION("Parent*(s, 18)")
//{
//string pql_query = "stmt s; Select s such that Parent*(s, 18)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//unordered_set<string> expected_result {"14"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Parent*(19, s)")
//{
//string pql_query = "stmt s; Select s such that Parent*(19, s)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//unordered_set<string> expected_result {"20", "21", "22"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Parent*(s, cl)")
//{
//string pql_query = "call cl; stmt s; Select s such that Parent*(s, cl)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//unordered_set<string> expected_result {"14"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Parent*(_, _)")
//{
//string pql_query = "call cl; Select cl such that Parent*(_, _)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//unordered_set<string> expected_result {"2", "3", "13", "18"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Parent*(_, 12)")
//{
//string pql_query = "assign a; Select a such that Parent*(_, 12)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query, PKB);
//unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
//REQUIRE(my_result == expected_result);
//}
}