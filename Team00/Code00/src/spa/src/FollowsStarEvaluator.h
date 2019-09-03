#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <QueryUtility.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>

class FollowsStarEvaluator {
public:
    static vector<string> evaluate_non_trivial(pql_dto::Entity first_param,
            pql_dto::Entity second_param, pql_dto::Entity select_entity);
    static vector<string> evaluate_trivial(pql_dto::Entity first_param,
            pql_dto::Entity second_param, pql_dto::Entity select_entity)
};

