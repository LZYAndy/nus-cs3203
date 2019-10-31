#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <pql_dto/Relationships.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/With.h>
#include <pql_dto/Constraint.h>
#include <QueryUtility.h>

using namespace std;

class Cache
{
private:
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> follows_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> follows_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> parent_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> parent_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> uses_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> modifies_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> calls_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> calls_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> next_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> next_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> next_bip_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> next_bip_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> affects_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> affects_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> affects_bip_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> affects_bip_star_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> assign_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> while_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> if_cache;
//    unordered_map<pair<string, string>, unordered_map<string, vector<string>>> with_cache;

    unordered_map<string, unordered_map<string, vector<string>>> explicit_relation_cache;
    unordered_map<string, unordered_map<string, vector<string>>> explicit_pattern_cache;
    unordered_map<string, unordered_map<string, vector<string>>> explicit_with_cache;

    unordered_map<string, unordered_map<string, vector<string>>> implicit_relation_cache;
    unordered_map<string, unordered_map<string, vector<string>>> implicit_pattern_cache;
    unordered_map<string, unordered_map<string, vector<string>>> implicit_with_cache;

public:
    bool insert_clause(pql_dto::Relationships &relation, pql_dto::Entity &first_param, pql_dto::Entity &second_param,
            unordered_map<string, vector<string>> &intermediary_map);
    bool insert_clause(pql_dto::Pattern &pattern, pql_dto::Entity &first_param, pql_dto::Entity &second_param,
            unordered_map<string, vector<string>> &intermediary_map);
    bool insert_clause(pql_dto::With &with, pql_dto::Entity &first_param, pql_dto::Entity &second_param,
            unordered_map<string, vector<string>> &intermediary_map);
    unordered_map<string, vector<string>> get_similar_clause_map(pql_dto::Constraint &clause);
    unordered_map<string, vector<string>> get_clause_map(pql_dto::Constraint &clause);
    int get_clause_size(pql_dto::Constraint &clause);
};