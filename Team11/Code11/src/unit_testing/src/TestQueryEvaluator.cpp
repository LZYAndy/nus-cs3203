#include "catch.hpp"
#include "PKB.h"
#include "QueryEvaluator.h"

PKB PKB;

TEST_CASE("Test get_final_list function")
{
    unordered_map<string, vector<string>> such_that_map;
    unordered_map<string, vector<string>> pattern_map;
    vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
    vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
    vector<string> pattern_vec {"9", "16"};
    such_that_map["s"] = such_that_vec_1;
    such_that_map["a"] = such_that_vec_2;
    pattern_map["a"] = pattern_vec;
    unordered_set<string> common_synonyms = {"a"};
    unordered_map<string, vector<string>> my_map = QueryEvaluator::merge_two_maps(such_that_map, pattern_map, common_synonyms);
    unordered_map<string, vector<string>> expected_result;
    expected_result["s"] = vector<string> {"4", "5", "6", "7"};
    expected_result["a"] = vector<string> {"9", "9", "9", "9"};
    REQUIRE(my_map == expected_result);
}

TEST_CASE("Test merge_two_maps function")
{
    unordered_map<string, vector<string>> such_that_map;
    unordered_map<string, vector<string>> pattern_map;
    vector<string> such_that_vec {"4", "5", "6", "7", "12", "13", "14"};
    vector<string> pattern_vec {"9"};
    such_that_map["s"] = such_that_vec;
    pattern_map["a"] = pattern_vec;
    unordered_set<string> common_synonyms = {};
    unordered_map<string, vector<string>> my_map = QueryEvaluator::merge_two_maps(such_that_map, pattern_map, common_synonyms);
    unordered_map<string, vector<string>> expected_result;
    expected_result["s"] = vector<string> {"4", "5", "6", "7", "12", "13", "14"};
    expected_result["a"] = vector<string> {"9", "9", "9", "9", "9", "9", "9"};
    REQUIRE(my_map == expected_result);
}

TEST_CASE("Test merge function")
{
    map<string, vector<string>> select_map;
    unordered_map<string, vector<string>> such_that_map;
    unordered_map<string, vector<string>> pattern_map;
    SECTION("have no such that and pattern clauses")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        select_map["s"] = select_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, false, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only such that clause with one synonym same as select but no pattern clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec {"4", "5", "6", "17"};
        select_map["s"] = select_vec;
        such_that_map["s"] = such_that_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only such that clause with one synonym not the same as select but no pattern clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec {"4", "5", "6", "17", "18"};
        select_map["s"] = select_vec;
        such_that_map["a"] = such_that_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only such that clause with two synonyms with one same as select but no pattern clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
        vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
        select_map["s"] = select_vec;
        such_that_map["s"] = such_that_vec_1;
        such_that_map["a"] = such_that_vec_2;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "12", "13", "14"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only such that clause with two synonyms with none same as select but no pattern clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
        vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
        select_map["s"] = select_vec;
        such_that_map["s1"] = such_that_vec_1;
        such_that_map["a"] = such_that_vec_2;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only pattern clause with one synonyms same as select but no such that clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("assign", "a", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> pattern_vec {"9", "16"};
        select_map["a"] = select_vec;
        pattern_map["a"] = pattern_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, false, PKB);
        unordered_set<string> expected_result {"9", "16"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only pattern clause with one synonyms not same as select but no such that clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> pattern_vec {"9", "16"};
        select_map["s"] = select_vec;
        pattern_map["a"] = pattern_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, false, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only pattern clause with two synonyms one same as select but no such that clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("assign", "a", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> pattern_vec_1 {"9", "16"};
        vector<string> pattern_vec_2 {"x", "y"};
        select_map["a"] = select_vec;
        pattern_map["a"] = pattern_vec_1;
        pattern_map["v"] = pattern_vec_2;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, false, PKB);
        unordered_set<string> expected_result {"9", "16"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have only pattern clause with two synonyms none same as select but no such that clause")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> pattern_vec_1 {"9", "16"};
        vector<string> pattern_vec_2 {"x", "y"};
        select_map["s"] = select_vec;
        pattern_map["a"] = pattern_vec_1;
        pattern_map["v"] = pattern_vec_2;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, false, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have both such that and pattern clauses")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
        vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
        vector<string> pattern_vec {"9", "16"};
        select_map["s"] = select_vec;
        such_that_map["s"] = such_that_vec_1;
        such_that_map["a"] = such_that_vec_2;
        pattern_map["a"] = pattern_vec;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"4", "5", "6", "7"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("have both such that and pattern clauses")
    {
        pql_dto::Entity select_entity = pql_dto::Entity("variable", "v", true);
        vector<pql_dto::Entity> select_clause;
        select_clause.push_back(select_entity);
        vector<string> select_vec {"x", "y", "z", "a", "b", "c", "i"};
        vector<string> such_that_vec_1 {"x", "y", "z", "x", "a", "b", "i", "x", "z", "b", "z", "a", "b", "x", "y", "c"};
        vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
        vector<string> pattern_vec_1 {"9", "13", "16"};
        vector<string> pattern_vec_2 {"x", "z", "i"};
        select_map["v"] = select_vec;
        such_that_map["v"] = such_that_vec_1;
        such_that_map["a"] = such_that_vec_2;
        pattern_map["a"] = pattern_vec_1;
        pattern_map["v"] = pattern_vec_2;
        unordered_set<string> my_result = QueryEvaluator::merge(select_clause, select_map, such_that_map, pattern_map, true, PKB);
        unordered_set<string> expected_result {"x", "z"};
        REQUIRE(my_result == expected_result);
    }
}

TEST_CASE("Test get_common_synonyms function")
{
    unordered_map<string, vector<string>> map_1;
    unordered_map<string, vector<string>> map_2;
    vector<string> str_vec_1 = {"1", "2", "3"};
    vector<string> str_vec_2 = {"x", "y"};
    map_1["s1"] = str_vec_1;
    map_1["s2"] = str_vec_1;
    map_1["a1"] = str_vec_1;
    map_1["a2"] = str_vec_1;
    map_1["a3"] = str_vec_1;
    map_1["v1"] = str_vec_2;
    map_1["v2"] = str_vec_2;
    map_2["s2"] = str_vec_1;
    map_2["s3"] = str_vec_1;
    map_2["a3"] = str_vec_1;
    map_2["v1"] = str_vec_2;
    map_2["v2"] = str_vec_2;
    unordered_set<string> expected_result = {"s2", "a3", "v1", "v2"};
    unordered_set<string> my_result = QueryEvaluator::get_common_synonyms(map_1, map_2);
    REQUIRE(my_result == expected_result);
}

TEST_CASE("Test get_common_part function")
{
    vector<string> str_vec_1 = {"1", "2", "3", "7", "9"};
    vector<string> str_vec_2 = {"1", "3", "7", "15", "20"};
    vector<string> str_vec_3 = {"6", "8", "10", "15", "20"};
    unordered_set<string> my_result_1 = QueryEvaluator::get_common_part(str_vec_1, str_vec_2);
    unordered_set<string> my_result_2 = QueryEvaluator::get_common_part(str_vec_1, str_vec_3);
    unordered_set<string> expected_result_1 = {"1", "3", "7"};
    unordered_set<string> expected_result_2 = {};
    REQUIRE(my_result_1 == expected_result_1);
    REQUIRE(my_result_2 == expected_result_2);
}

TEST_CASE("Test is_emtpy_map function")
{
    unordered_map<string, vector<string>> empty_map;
    bool expected_result = true;
    REQUIRE(QueryEvaluator::is_empty_map(empty_map) == expected_result);
}
