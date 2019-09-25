#include "QueryEvaluator.h"

#include <utility>

unordered_set<string> QueryEvaluator::get_result(string &query, PKB &PKB)
{
    string error_msg;
    unordered_set<string> result;
    unordered_set<string> empty_set;
    pql_dto::Entity select_entity;

    unordered_map<string, vector<string>> select_map;
    unordered_map<string, vector<string>> such_that_map;
    unordered_map<string, vector<string>> pattern_map;

    vector<pql_dto::Entity> declaration_clause;
    vector<pql_dto::Entity> select_clause;
    vector<pql_dto::Relationships> such_that_clause;
    vector<pql_dto::Pattern> pattern_clause;

    /*
     * parse the PQL query
     */
    error_msg = PQLParser::pql_parse_query(move(query), declaration_clause, select_clause,
                                           such_that_clause, pattern_clause);
    if (!error_msg.empty())
    {
        return empty_set;
    }

    if (!select_clause.empty())
    {
        // has select
        select_entity = select_clause.front();
        string select_name = select_entity.get_entity_name();
        EntityType select_type = select_entity.get_entity_type();
        if (select_type == EntityType::VARIABLE || select_type == EntityType::PROCEDURE || select_type == EntityType::CONSTANT)
        {
            select_map[select_name] = QueryUtility::get_certain_type_str_list(select_type, PKB);
        }
        else
        {
            select_map[select_name] = QueryUtility::get_certain_type_int_list(select_type, PKB);
        }
    }

    such_that_map = select_map; // initialize such_that_map
    pattern_map = select_map; // initialize pattern_map

    if (!such_that_clause.empty())
    {
        // has such that
        pql_dto::Relationships relation = such_that_clause.front();
        RelationshipType relation_type = relation.get_relationship();
        pql_dto::Entity first_param = relation.get_first_param();
        pql_dto::Entity second_param = relation.get_second_param();
        bool trivial_result;

        if (relation_type == RelationshipType::FOLLOWS)
        {
            if (!relation.is_relationship_star())
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = FollowsEvaluator::evaluate_trivial(first_param, second_param, PKB);
                    if(!trivial_result)
                    {
                        return empty_set;
                    }
                }
                else
                {
                    such_that_map = FollowsEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
                }
            }
            else
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = FollowsStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                    if(!trivial_result)
                    {
                        return empty_set;
                    }
                }
                else
                {
                    such_that_map = FollowsStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
                }
            }
        }

        if (relation_type == RelationshipType::USES)
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = UsesEvaluator::evaluate_trivial(first_param, second_param, PKB);
                if(!trivial_result)
                {
                    return empty_set;
                }
            }
            else
            {
                such_that_map = UsesEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }

        if (relation_type == RelationshipType::PARENT)
        {
            if (!relation.is_relationship_star())
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = ParentEvaluator::evaluate_trivial(first_param, second_param, PKB);
                    if(!trivial_result)
                    {
                        return empty_set;
                    }
                }
                else
                {
                    such_that_map = ParentEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
                }
            }
            else
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = ParentStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                    if(!trivial_result)
                    {
                        return empty_set;
                    }
                }
                else
                {
                    such_that_map = ParentStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
                }
            }
        }

        if (relation_type == RelationshipType::MODIFIES)
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = ModifiesEvaluator::evaluate_trivial(first_param, second_param, PKB);
                if(!trivial_result)
                {
                    return empty_set;
                }
            }
            else
            {
                such_that_map = ModifiesEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    if (!pattern_clause.empty())
    {
        // has pattern
        pql_dto::Pattern pattern = pattern_clause.front();
        EntityType pattern_type = pattern.get_pattern_entity().get_entity_type();
        pql_dto::Entity first_param = pattern.get_first_param();
        pql_dto::Entity second_param = pattern.get_second_param();
        if (pattern_type == EntityType::ASSIGN)
        {
            pattern_map = AssignEvaluator::evaluate(pattern, first_param, second_param, PKB);
        }
    }

    // Merge three lists
    result = QueryEvaluator::merge(select_entity, select_map, such_that_map, pattern_map);
    return result;
}

unordered_set<string> QueryEvaluator::merge(pql_dto::Entity &select_entity,
        unordered_map<string, vector<string>> &select_map,
        unordered_map<string, vector<string>> &such_that_map,
        unordered_map<string, vector<string>> &pattern_map)
{
    unordered_set<string> result;
    string select_name = select_entity.get_entity_name();
    unordered_map<string, unordered_set<string>> final_list;
    unordered_set<string> common_synonyms = QueryEvaluator::get_common_synonyms(such_that_map, pattern_map);
    if (!common_synonyms.empty())
    {
        final_list = QueryEvaluator::get_final_list(such_that_map, pattern_map, common_synonyms);
        for (const auto &iter : final_list)
        {
            string name = iter.first;
            unordered_set<string> str_set = iter.second;
            vector<string> str_vec(str_set.size());
            copy(str_set.begin(), str_set.end(), str_vec.begin());
            if (str_vec.empty())
            {
                return unordered_set<string>();
            }
            if (name == select_name)
            {
                return QueryEvaluator::get_common_part(str_vec, select_map.at(select_name));
            }
        }
        vector<string> result_vec = select_map.at(select_name);
        for (const auto &iter : result_vec)
        {
            result.insert(iter);
        }
    }
    else
    {
        if (such_that_map.empty() || pattern_map.empty())
        {
            return unordered_set<string>();
        }
        else
        {
            for (const auto &iter : such_that_map)
            {
                if (iter.second.empty())
                {
                    return unordered_set<string>();
                }
            }
            for (const auto &iter : pattern_map)
            {
                if (iter.second.empty())
                {
                    return unordered_set<string>();
                }
            }
            if (such_that_map.find(select_name) != such_that_map.end())
            {
                result = QueryEvaluator::get_common_part(such_that_map.at(select_name), select_map.at(select_name));
            }
            else if (pattern_map.find(select_name) != pattern_map.end())
            {
                result = QueryEvaluator::get_common_part(pattern_map.at(select_name), select_map.at(select_name));
            }
            else
            {
                vector<string> result_vec = select_map.at(select_name);
                for (const auto &iter : result_vec)
                {
                    result.insert(iter);
                }
            }
        }
    }
    return result;
}

unordered_set<string> QueryEvaluator::get_common_synonyms(unordered_map<string, vector<string>> &map_1,
        unordered_map<string, vector<string>> &map_2)
{
    unordered_set<string> result;
    for (const auto &iter : map_1)
    {
        string synonym_name = iter.first;
        if (map_2.find(synonym_name) == map_2.end())
        {
            // does not present
            continue;
        }
        else
        {
            result.insert(synonym_name);
        }
    }
    return result;
}

unordered_map<string, unordered_set<string>> QueryEvaluator::get_final_list(unordered_map<string, vector<string>> &map_1,
        unordered_map<string, vector<string>> &map_2, unordered_set<string> &common_part)
{
    unordered_map<string, unordered_set<string>> result;
    vector<string> common_synonyms(common_part.size());
    copy(common_part.begin(), common_part.end(), common_synonyms.begin());
    vector<pair<int, int>> position;
    int i = 0;
    for (const auto &element_1 : map_1.at(common_synonyms[0]))
    {
        int j = 0;
        bool is_same = true;
        for (const auto &element_2 : map_2.at(common_synonyms[0]))
        {
            if (element_1 == element_2)
            {
                for (const auto &synonym : common_synonyms)
                {
                    if (map_1.at(synonym).at(i) != map_2.at(synonym).at(j))
                    {
                        is_same = false;
                        break;
                    }
                }
                if (is_same)
                {
                    pair<int, int> int_pair (i, j);
                    position.push_back(int_pair);
                }
            }
            j++;
        }
        i++;
    }
    for (const auto &iter : map_1)
    {
        string synonym_name = iter.first;
        vector<string> list_1 = iter.second;
        unordered_set<string> key_value;
        for (auto p : position)
        {
            int pos = p.first;
            key_value.insert(list_1[pos]);
        }
        result[synonym_name] = key_value;
    }
    for (const auto &iter : map_2)
    {
        string synonym_name = iter.first;
        if (result.find(synonym_name) != result.end())
        {
            // presented
            continue;
        }
        vector<string> list_2 = iter.second;
        unordered_set<string> key_value;
        for (auto p : position)
        {
            int pos = p.second;
            key_value.insert(list_2[pos]);
        }
        result[synonym_name] = key_value;
    }
    return result;
}

unordered_set<string> QueryEvaluator::get_common_part(vector<string> &str_vec_1, vector<string> &str_vec_2)
{
    unordered_set<string> result;
    for (const auto &iter : str_vec_1)
    {
        if (count(str_vec_2.begin(), str_vec_2.end(), iter))
        {
            result.insert(iter);
        }
    }
    return result;
}
