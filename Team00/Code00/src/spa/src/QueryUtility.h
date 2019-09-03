#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <pql_dto/Entity.h>


class QueryUtility {
public:
    static vector<std::string> get_certain_type_list(EntityType type);
    static bool is_integer(string s);
};

