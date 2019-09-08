#pragma once

#include <stdio.h>
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
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class QueryEvaluator {
public:
    static vector<string> get_result(string query);

private:
    static vector<string> take_common_part(vector<string> select_list,
                                                           vector<string> such_that_list,
                                                           vector<string> pattern_list);
};

