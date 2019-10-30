#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

class Cache
{
private:
    map<pair<pql_dto::Relationships, vector<pql_dto::Entity>>, unordered_map<string, vector<string>>> explicit_relation_cache;
    map<pair<pql_dto::Relationships, vector<pql_dto::Entity>>, unordered_map<string, vector<string>>> explicit_pattern_cache;
    map<pair<pql_dto::Relationships, vector<pql_dto::Entity>>, unordered_map<string, vector<string>>> explicit_with_cache;

    map<pair<pql_dto::Relationships, vector<EntityType>>, unordered_map<string, vector<string>>> implicit_relation_cache;
    map<pair<pql_dto::Relationships, vector<EntityType>>, unordered_map<string, vector<string>>> implicit_pattern_cache;
    map<pair<pql_dto::Relationships, vector<EntityType>>, unordered_map<string, vector<string>>> implicit_with_cache;

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