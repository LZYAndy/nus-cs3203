#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <QueryUtility.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>

class AssignEvaluator
{
public:
    static unordered_map<string, vector<string>> evaluate(pql_dto::Pattern pattern,
        pql_dto::Entity first_param, pql_dto::Entity second_param);
};
