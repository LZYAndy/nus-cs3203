#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <pql_dto/Entity.h>


class QueryUtility
{
public:
    static vector<string> get_certain_type_str_list(EntityType type);
    static vector<int> get_certain_type_int_list(EntityType type);
    static bool is_integer(string s);
    static bool is_proc_name(pql_dto::Entity entity);
    static bool is_proc_declared(pql_dto::Entity entity);
    static bool is_var_name(pql_dto::Entity entity);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key, const vector<int>& int_vec);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key, const vector<string>& str_vec);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key, int n);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
            const unordered_map<int, int>& int_map);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
            const unordered_map<string, string>& str_map);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
            const unordered_map<int, string>& int_str_map);
    static unordered_map<string, vector<string>> mapping(string str, vector<int>& int_vec);
    static unordered_map<string, vector<string>> mapping(string str1, string str2, vector<int>& int_vec);
    static unordered_map<string, vector<string>> mapping(string str1, pql_dto::Entity key, vector<int>& int_vec);
};

