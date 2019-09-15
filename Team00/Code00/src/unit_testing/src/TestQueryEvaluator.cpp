#include "catch.hpp"
#include "QueryEvaluator.h"

TEST_CASE("Whether merge function can work correctly")
{
    pql_dto::Entity select_entity = pql_dto::Entity("stmt", "s", true);
    unordered_map<string, vector<string>> select_list;
    unordered_map<string, vector<string>> such_that_list;
    unordered_map<string, vector<string>> pattern_list;
    vector<string> select_vec {"4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"};
    vector<string> such_that_vec_1 {"4", "4", "5", "4", "5", "6", "4", "5", "6", "7", "12", "12", "13", "12", "13", "14"};
    vector<string> such_that_vec_2 {"5", "6", "6", "7", "7", "7", "9", "9", "9", "9", "13", "14", "14", "15", "15", "15"};
    vector<string> pattern_vec {"9", "16"};
    select_list["s"] = select_vec;
    such_that_list["s"] = such_that_vec_1;
    such_that_list["a"] = such_that_vec_2;
    pattern_list["a"] = pattern_vec;
    vector<string> expected_result {"4", "5", "6", "7"};
    REQUIRE(QueryEvaluator::merge(select_entity, select_list, such_that_list, pattern_list) == expected_result);
}
