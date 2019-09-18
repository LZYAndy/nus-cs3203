#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <PKB.h>
#include <PQLParser.h>
#include <QueryUtility.h>
#include <FollowsEvaluator.h>
#include <FollowsStarEvaluator.h>
#include <ParentEvaluator.h>
#include <ParentStarEvaluator.h>
#include <ModifiesEvaluator.h>
#include <UsesEvaluator.h>
#include <AssignEvaluator.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class QueryEvaluator
{
public:
    static unordered_set<string> get_result(string query);
    static unordered_set<string> merge(pql_dto::Entity select_entity,
            unordered_map<string, vector<string>> select_list,
            unordered_map<string, vector<string>> such_that_list,
            unordered_map<string, vector<string>> pattern_list);
    static unordered_set<string> get_common_synonyms(const unordered_map<string, vector<string>>& map_1,
            unordered_map<string, vector<string>> map_2);
    static unordered_map<string, unordered_set<string>> get_final_list(unordered_map<string, vector<string>> map_1,
            unordered_map<string, vector<string>> map_2, unordered_set<string> common_synonym);
    static unordered_set<string> get_common_part(const vector<string>& str_vec_1, vector<string> str_vec_2);
};
