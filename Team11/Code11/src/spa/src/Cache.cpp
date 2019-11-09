#include "Cache.h"

bool Cache::insert_clause(pql_dto::Relationships &relation, pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, unordered_map<string, vector<string>> intermediary_map)
{
    vector<vector<string>> order_vec;
    vector<vector<string>> order_same_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    string first_type_name = QueryUtility::get_entity_type_name(first_param);
    string second_type_name = QueryUtility::get_entity_type_name(second_param);
    string clause_name = QueryUtility::get_clause_type_name(relation);
    string explicit_key = clause_name + " " + first_name + " " + second_name;
    string implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name != second_name)
    {
        order_vec.push_back(intermediary_map[first_name]);
        order_vec.push_back(intermediary_map[second_name]);
    }
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name == second_name)
    {
        order_same_vec.push_back(intermediary_map[first_name]);
        order_same_vec.push_back(intermediary_map[second_name]);
    }
    explicit_relation_cache[explicit_key] = intermediary_map;
    implicit_relation_cache[implicit_key] = order_vec;
    implicit_same_relation_cache[implicit_key] = order_same_vec;

    return true;
}

bool Cache::insert_clause(pql_dto::Pattern &pattern, pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, unordered_map<string, vector<string>> intermediary_map)
{
    vector<vector<string>> order_vec;
    vector<vector<string>> order_same_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    string first_type_name = QueryUtility::get_entity_type_name(first_param);
    string second_type_name = QueryUtility::get_entity_type_name(second_param);
    string clause_name = QueryUtility::get_clause_type_name(pattern);
    string explicit_key = clause_name + " " + first_name + " " + second_name;
    string implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name != second_name)
    {
        order_vec.push_back(intermediary_map[first_name]);
        order_vec.push_back(intermediary_map[second_name]);
    }
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name == second_name)
    {
        order_same_vec.push_back(intermediary_map[first_name]);
        order_same_vec.push_back(intermediary_map[second_name]);
    }
    explicit_pattern_cache[explicit_key] = intermediary_map;
    implicit_pattern_cache[implicit_key] = order_vec;
    implicit_same_pattern_cache[implicit_key] = order_same_vec;

    return true;
}

bool Cache::insert_clause(pql_dto::With &with, pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, unordered_map<string, vector<string>> intermediary_map)
{
    vector<vector<string>> order_vec;
    vector<vector<string>> order_same_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    string first_type_name = QueryUtility::get_entity_type_name(first_param);
    string second_type_name = QueryUtility::get_entity_type_name(second_param);
    string clause_name = QueryUtility::get_clause_type_name(with);
    string explicit_key = clause_name + " " + first_name + " " + second_name;
    string implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name != second_name)
    {
        order_vec.push_back(intermediary_map[first_name]);
        order_vec.push_back(intermediary_map[second_name]);
    }
    if (first_param.is_entity_declared() && second_param.is_entity_declared() && first_name == second_name)
    {
        order_same_vec.push_back(intermediary_map[first_name]);
        order_same_vec.push_back(intermediary_map[second_name]);
    }
    explicit_with_cache[explicit_key] = intermediary_map;
    implicit_with_cache[implicit_key] = order_vec;
    implicit_same_with_cache[implicit_key] = order_same_vec;

    return true;
}

unordered_map<string, vector<string>> Cache::get_similar_clause_map(pql_dto::Constraint &clause)
{
    vector<vector<string>> temp_vec;
    unordered_map<string, vector<string>> result;
    pql_dto::Entity first_param;
    pql_dto::Entity second_param;
    string first_type_name;
    string second_type_name;
    string clause_name;
    string implicit_key;

    if (clause.is_relationship())
    {
        pql_dto::Relationships relation = clause.get_relationship();
        first_param = relation.get_first_param();
        second_param = relation.get_second_param();
        first_type_name = QueryUtility::get_entity_type_name(first_param);
        second_type_name = QueryUtility::get_entity_type_name(second_param);
        clause_name = QueryUtility::get_clause_type_name(relation);
        implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
        if (first_param.get_entity_name() == second_param.get_entity_name())
        {
            temp_vec = implicit_same_relation_cache[implicit_key];
        }
        else
        {
            temp_vec = implicit_relation_cache[implicit_key];
        }
        bool is_first = true;
        for (const auto& iter : temp_vec)
        {
            if (is_first)
            {
                result[first_param.get_entity_name()] = iter;
                is_first = false;
            }
            else
            {
                result[second_param.get_entity_name()] = iter;
            }
        }
    }
    if (clause.is_pattern())
    {
        pql_dto::Pattern pattern = clause.get_pattern();
        first_param = pattern.get_first_param();
        second_param = pattern.get_second_param();
        first_type_name = QueryUtility::get_entity_type_name(first_param);
        second_type_name = QueryUtility::get_entity_type_name(second_param);
        clause_name = QueryUtility::get_clause_type_name(pattern);
        implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
        if (first_param.get_entity_name() == second_param.get_entity_name())
        {
            temp_vec = implicit_same_pattern_cache[implicit_key];
        }
        else
        {
            temp_vec = implicit_pattern_cache[implicit_key];
        }
        bool is_first = true;
        for (const auto& iter : temp_vec)
        {
            if (is_first)
            {
                result[first_param.get_entity_name()] = iter;
                is_first = false;
            }
            else
            {
                result[second_param.get_entity_name()] = iter;
            }
        }
    }
    if (clause.is_with())
    {
        pql_dto::With with = clause.get_with();
        first_param = with.get_first_param();
        second_param = with.get_second_param();
        first_type_name = QueryUtility::get_entity_type_name(first_param);
        second_type_name = QueryUtility::get_entity_type_name(second_param);
        clause_name = QueryUtility::get_clause_type_name(with);
        implicit_key = clause_name + " " + first_type_name + " " + second_type_name;
        if (first_param.get_entity_name() == second_param.get_entity_name())
        {
            temp_vec = implicit_same_with_cache[implicit_key];
        }
        else
        {
            temp_vec = implicit_with_cache[implicit_key];
        }
        bool is_first = true;
        for (const auto& iter : temp_vec)
        {
            if (is_first)
            {
                result[first_param.get_entity_name()] = iter;
                is_first = false;
            }
            else
            {
                result[second_param.get_entity_name()] = iter;
            }
        }
    }

    return result;
}

unordered_map<string, vector<string>> Cache::get_clause_map(pql_dto::Constraint &clause)
{
    pql_dto::Entity first_param;
    pql_dto::Entity second_param;
    string first_name;
    string second_name;
    string clause_name;
    string explicit_key;

    if (clause.is_relationship())
    {
        pql_dto::Relationships relation = clause.get_relationship();
        first_param = relation.get_first_param();
        second_param = relation.get_second_param();
        first_name = first_param.get_entity_name();
        second_name = second_param.get_entity_name();
        clause_name = QueryUtility::get_clause_type_name(relation);
        explicit_key = clause_name + " " + first_name + " " + second_name;
        return explicit_relation_cache[explicit_key];
    }
    if (clause.is_pattern())
    {
        pql_dto::Pattern pattern = clause.get_pattern();
        first_param = pattern.get_first_param();
        second_param = pattern.get_second_param();
        first_name = first_param.get_entity_name();
        second_name = second_param.get_entity_name();
        clause_name = QueryUtility::get_clause_type_name(pattern);
        explicit_key = clause_name + " " + first_name + " " + second_name;
        return explicit_pattern_cache[explicit_key];
    }
    if (clause.is_with())
    {
        pql_dto::With with = clause.get_with();
        first_param = with.get_first_param();
        second_param = with.get_second_param();
        first_name = first_param.get_entity_name();
        second_name = second_param.get_entity_name();
        clause_name = QueryUtility::get_clause_type_name(with);
        explicit_key = clause_name + " " + first_name + " " + second_name;
        return explicit_with_cache[explicit_key];
    }

    return unordered_map<string, vector<string>>();
}

int Cache::get_clause_size(pql_dto::Constraint &clause)
{
    int size = 0;
    unordered_map<string, vector<string>> clause_map = Cache::get_clause_map(clause);
    for (auto iter : clause_map)
    {
        size = iter.second.size();
        break;
    }
    return size;
}
