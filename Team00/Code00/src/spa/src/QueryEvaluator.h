#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <PQLParser.h>
#include <QueryUtility.h>
#include <FollowsEvaluator.h>
#include <FollowsStarEvaluator.h>
#include <ParentEvaluator.h>
#include <ParentStarEvaluator.h>
#include <ModifiesEvaluator.h>
#include <UsesEvaluator.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class QueryEvaluator {
public:
    static vector<string> get_result(string query);

private:
    static vector<string> take_common_part(pql_dto::Entity select_entity,
            unordered_map<string, vector<string>> select_list,
            unordered_map<string, vector<string>> such_that_list,
            unordered_map<string, vector<string>> pattern_list);
};

