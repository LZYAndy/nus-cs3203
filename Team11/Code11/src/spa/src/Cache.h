#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Cache
{
private:
    map<vector<pql_dto::Relationships, pql_dto::Entity, pql_dto::Entity>, unordered_map<string, vector<string>>>> explicit_relation_cache;
    map<vector<pql_dto::Pattern, pql_dto::Entity, pql_dto::Entity>, unordered_map<string, vector<string>>> explicit_pattern_cache;
    map<vector<pql_dto::With, pql_dto::Entity, pql_dto::Entity>, unordered_map<string, vector<string>>> explicit_with_cache;

    map<vector<pql_dto::Relationships, EntityType, EntityType>, unordered_map<string, vector<string>>>> implicit_relation_cache;
    map<vector<pql_dto::Pattern, EntityType, EntityType>, unordered_map<string, vector<string>>> implicit_pattern_cache;
    map<vector<pql_dto::With, EntityType, EntityType>, unordered_map<string, vector<string>>> implicit_with_cache;

//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> FollowsCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> FollowsStarCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> ParentCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> ParentStarCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> UsesCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> ModifiesCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> FollowsCache;
//    map<pair<pql_dto::Entity, pql_dto::Entity>, pair<bool, unordered_map<string, vector<string>>>> FollowsStarCache;

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