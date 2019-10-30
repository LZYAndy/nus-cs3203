#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <PKB.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/With.h>

class QueryUtility
{
public:
    static vector<string> get_certain_type_str_list(EntityType &type, PKB &PKB);
    static vector<string> get_certain_type_int_list(EntityType &type, PKB &PKB);
    static bool is_same_type(EntityType type_1, EntityType type_2);
    static bool is_statement_num(pql_dto::Entity &entity);
    static bool is_program_line(pql_dto::Entity &entity);
    static bool is_proc_name(pql_dto::Entity &entity);
    static bool is_proc_declared(pql_dto::Entity &entity);
    static bool is_var_name(pql_dto::Entity &entity);
    static string get_entity_type_name(pql_dto::Entity entity);
    static string get_clause_type_name(pql_dto::Relationships relation);
    static string get_clause_type_name(pql_dto::Pattern pattern);
    static string get_clause_type_name(pql_dto::With with);
    static vector<string> change_to_attributes(pql_dto::Entity &select_entity,
            vector<string> temp_vec, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key, vector<int> &int_vec, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key, vector<string> &str_vec);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key, int n, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
            unordered_map<int, vector<int>> &int_map, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
            unordered_map<string, vector<string>> &str_map);
    static unordered_map<string, vector<string>> mapping(pql_dto::Entity &key_1, pql_dto::Entity &key_2,
            unordered_map<int, vector<string>> &int_str_map, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(string &str, vector<int> &int_vec);
    static unordered_map<string, vector<string>> mapping(string &str_1, string &str_2, vector<int> &int_vec, PKB &PKB);
    static unordered_map<string, vector<string>> mapping(string &str, pql_dto::Entity &key, vector<int> &int_vec, PKB &PKB);
};
