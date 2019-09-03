#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <PQLParser.h>
#include <QueryUtility.h>
#include <FollowsEvaluator.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class QueryEvaluator {
public:
    static vector<string> QueryEvaluator::get_result(string query);

private:
    static vector<string> QueryEvaluator::take_common_part(vector<string> select_list,
                                                           vector<string> such_that_list,
                                                           vector<string> pattern_list);
};

#endif
