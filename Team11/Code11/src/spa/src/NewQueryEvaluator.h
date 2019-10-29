#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

#include <PKB.h>
#include <PQLParser.h>
#include <Optimizer.h>
#include <QueryUtility.h>
#include <FollowsEvaluator.h>
#include <FollowsStarEvaluator.h>
#include <ParentEvaluator.h>
#include <ParentStarEvaluator.h>
#include <ModifiesEvaluator.h>
#include <UsesEvaluator.h>
#include <AssignEvaluator.h>
#include <CallsEvaluator.h>
#include <CallsStarEvaluator.h>
#include <NextEvaluator.h>
#include <NextStarEvaluator.h>
#include <AffectsEvaluator.h>
#include <AffectsStarEvaluator.h>
#include <WhileEvaluator.h>
#include <IfEvaluator.h>
#include <Cache.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/With.h>

class NewQueryEvaluator
{
public:
    static unordered_set<string> get_result(string &query, PKB &PKB);
    static unordered_set<string> select(vector<pql_dto::Entity> &select_clause,
            map<string, vector<string>> &select_map,
            unordered_map<string, vector<string>> &final_map,
            PKB &PKB);
    static unordered_map<string, vector<string>> mergeGroup(vector<pql_dto::Constraint> &group, Cache &cache);
    static bool evaluateBoolGroup(deque<pql_dto::Constraint> group, PKB &PKB);
    static bool evaluateGroup(deque<pql_dto::Constraint> group, PKB &PKB, Cache &cache);
    static unordered_set<string> evaluateEmptyMap(bool is_select_bool);
    static vector<bool, unordered_map<string, vector<string>>> evaluateSuchThat(Relationships &relation, PKB &PKB, Cache &cache);
    static unordered_map<string, vector<string>> evaluatePattern(Pattern &pattern, PKB &PKB, Cache &cache);
    static unordered_map<string, vector<string>> evaluateWith(With &with, PKB &PKB, Cache &cache);
    static unordered_set<string> get_common_synonyms(unordered_map<string, vector<string>> &map_1,
            unordered_map<string, vector<string>> &map_2);
    static unordered_set<string> get_common_synonyms(unordered_map<string, vector<string>> &map_1,
            map<string, vector<string>> &map_2);
    static int get_element_index_in_map(map<string, vector<string>> &map, string key);
    static bool is_empty_map(unordered_map<string, vector<string>> &map);
    static unordered_map<string, vector<string>> merge_two_maps(unordered_map<string, vector<string>> map_1,
            unordered_map<string, vector<string>> map_2, unordered_set<string> common_synonym);
    static unordered_set<string> get_common_part(vector<string> &str_vec_1, vector<string> &str_vec_2);
};
