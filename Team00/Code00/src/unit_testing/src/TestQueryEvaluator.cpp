#include "catch.hpp"
#include "QueryEvaluator.h"

TEST_CASE("Test get_final_list function")
{
    unordered_map<string, vector<string>> such_that_list;
    unordered_map<string, vector<string>> pattern_list;
    vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
    vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
    vector<string> pattern_vec {"9", "16"};
    such_that_list["s"] = such_that_vec_1;
    such_that_list["a"] = such_that_vec_2;
    pattern_list["a"] = pattern_vec;
    unordered_set<string> common_synonyms = {"a"};
    unordered_map<string, unordered_set<string>> my_map = QueryEvaluator::get_final_list(such_that_list, pattern_list, common_synonyms);
    unordered_map<string, unordered_set<string>> expected_result;
    expected_result["s"] = unordered_set<string> {"4", "5", "6", "7"};
    expected_result["a"] = unordered_set<string> {"9"};
    REQUIRE(my_map == expected_result);
}

TEST_CASE("Test merge function")
{
    pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
    unordered_map<string, vector<string>> select_list;
    unordered_map<string, vector<string>> such_that_list;
    unordered_map<string, vector<string>> pattern_list;
    SECTION("have no such that and pattern clauses")
    {
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        select_list["s"];
    }

    SECTION("have both such that and pattern clauses")
    {
        vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
        vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
        vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
        vector<string> pattern_vec {"9", "16"};
        select_list["s"] = select_vec;
        such_that_list["s"] = such_that_vec_1;
        such_that_list["a"] = such_that_vec_2;
        pattern_list["a"] = pattern_vec;
        unordered_set<string> expected_result {"4", "5", "6", "7"};
        unordered_set<string> my_str_vec = QueryEvaluator::merge(select_entity, select_list, such_that_list, pattern_list);
        unordered_set<string> my_result(my_str_vec.begin(), my_str_vec.end());
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

