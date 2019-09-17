#include "QueryEvaluator.h"

#include <utility>

vector<string> QueryEvaluator::get_result(string query)
{

    string error_msg;
    vector<string> result;
    vector<string> empty_vec;

    unordered_map<string, vector<string>> select_list = unordered_map<string, vector<string>>();
    unordered_map<string, vector<string>> such_that_list = unordered_map<string, vector<string>>();
    unordered_map<string, vector<string>> pattern_list = unordered_map<string, vector<string>>();

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
        return empty_vec;
    }

    pql_dto::Entity select_entity = select_clause.front();
    string select_name = select_entity.get_entity_name();
    pql_dto::Relationships relation = such_that_clause.front();
    pql_dto::Pattern pattern = pattern_clause.front();

    if (!select_clause.empty())
    { // has select
        EntityType select_type = select_entity.get_entity_type();
        if (select_type == EntityType::VARIABLE || select_type == EntityType::PROCEDURE)
        {
            select_list[select_name] = QueryUtility::get_certain_type_str_list(select_type);
        }
        else
        {
            select_list[select_name] = QueryUtility::get_certain_type_int_list(select_type);
        }
    }

    such_that_list = select_list; // initialize such_that_list
    pattern_list = select_list; // initialize pattern_list

    if (!such_that_clause.empty())
    { // has such that
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
                    trivial_result = FollowsEvaluator::evaluate_trivial(first_param, second_param);
                    if(!trivial_result)
                    {
                        such_that_list[select_name] = empty_vec;
                    }
                }
                else
                {
                    such_that_list = FollowsEvaluator::evaluate_non_trivial(first_param, second_param);
                }
            }
            else
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = FollowsStarEvaluator::evaluate_trivial(first_param, second_param);
                    if(!trivial_result)
                    {
                        such_that_list[select_name] = empty_vec;
                    }
                }
                else
                {
                    such_that_list = FollowsStarEvaluator::evaluate_non_trivial(first_param, second_param);
                }
            }
        }

        if (relation_type == RelationshipType::USES && !relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = UsesEvaluator::evaluate_trivial(first_param, second_param);
                if(!trivial_result)
                {
                    such_that_list[select_name] = empty_vec;
                }
            }
            else
            {
                such_that_list = UsesEvaluator::evaluate_non_trivial(first_param, second_param);
            }
        }

        if (relation_type == RelationshipType::PARENT && !relation.is_relationship_star())
        {
            if (!relation.is_relationship_star())
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = ParentEvaluator::evaluate_trivial(first_param, second_param);
                    if(!trivial_result)
                    {
                        such_that_list[select_name] = empty_vec;
                    }
                }
                else
                {
                    such_that_list = ParentEvaluator::evaluate_non_trivial(first_param, second_param);
                }
            }
            else
            {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
                {
                    trivial_result = ParentStarEvaluator::evaluate_trivial(first_param, second_param);
                    if(!trivial_result)
                    {
                        such_that_list[select_name] = empty_vec;
                    }
                }
                else
                {
                    such_that_list = ParentStarEvaluator::evaluate_non_trivial(first_param, second_param);
                }
            }
        }

        if (relation_type == RelationshipType::MODIFIES && !relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = ModifiesEvaluator::evaluate_trivial(first_param, second_param);
                if(!trivial_result)
                {
                    such_that_list[select_name] = empty_vec;
                }
            }
            else
            {
                such_that_list = ModifiesEvaluator::evaluate_non_trivial(first_param, second_param);
            }
        }
    }

    if (!pattern_clause.empty())
    { // has pattern
        EntityType pattern_type = pattern.get_pattern_entity().get_entity_type();
        pql_dto::Entity first_param = pattern.get_first_param();
        pql_dto::Entity second_param = pattern.get_second_param();
        if (pattern_type == EntityType::ASSIGN)
        {
            pattern_list = AssignEvaluator::evaluate(pattern, first_param, second_param);
        }
    }

    // Merge three lists
    result = QueryEvaluator::merge(select_entity, select_list, such_that_list, pattern_list);
    return result;
}

vector<string> QueryEvaluator::merge(pql_dto::Entity select_entity,
        unordered_map<string, vector<string>> select_list,
        unordered_map<string, vector<string>> such_that_list,
        unordered_map<string, vector<string>> pattern_list)
{
    vector<string> result;
    string select_name = select_entity.get_entity_name();
    unordered_map<string, vector<string>> final_list;
    vector<string> common_synonyms = QueryEvaluator::get_common_synonyms(such_that_list, pattern_list);
    if (!common_synonyms.empty())
    {
        final_list = QueryEvaluator::get_final_list(such_that_list, pattern_list, common_synonyms);
        for (const auto& iter : final_list)
        {
            string name = iter.first;
            vector<string> str_vec = iter.second;
            if (str_vec.empty())
            {
                return vector<string>();
            }
            if (name == select_name)
            {
                return QueryEvaluator::get_common_part(str_vec, select_list.at(select_name));
            }
        }
        result = select_list.at(select_name);
    }
    else
    {
        if (such_that_list.empty() || pattern_list.empty())
        {
            result = vector<string>();
        }
        else
        {
            if (such_that_list.find(select_name) != such_that_list.end())
            {
                result = QueryEvaluator::get_common_part(such_that_list.at(select_name), select_list.at(select_name));
            }
            else if (pattern_list.find(select_name) != pattern_list.end())
            {
                result = QueryEvaluator::get_common_part(pattern_list.at(select_name), select_list.at(select_name));
            }
            else
            {
                result = select_list.at(select_name);
            }
        }
    }
    return result;
}

vector<string> QueryEvaluator::get_common_synonyms(const unordered_map<string, vector<string>>& map_1,
        unordered_map<string, vector<string>> map_2)
{
    vector<string> result;
    for (const auto& iter : map_1)
    {
        string synonym_name = iter.first;
        if (map_2.find(synonym_name) == map_2.end())
        { // does not present
            continue;
        }
        else
        {
            result.push_back(synonym_name);
        }
    }
    return result;
}

unordered_map<string, vector<string>> QueryEvaluator::get_final_list(unordered_map<string, vector<string>> map_1,
        unordered_map<string, vector<string>> map_2, vector<string> common_synonyms)
{
    unordered_map<string, vector<string>> result = unordered_map<string, vector<string>>();
    vector<pair<int, int>> position;
    int i = 0;
    for (const auto& element_1 : map_1.at(common_synonyms[0]))
    {
        int j = 0;
        bool is_same = true;
        for (const auto& element_2 : map_2.at(common_synonyms[0]))
        {
            if (element_1 == element_2)
            {
                for (const auto& synonym : common_synonyms)
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
    for (const auto& iter : map_1)
    {
        string synonym_name = iter.first;
        vector<string> list_1 = iter.second;
        vector<string> key_value;
        for (auto p : position)
        {
            int pos = p.first;
            key_value.push_back(list_1[pos]);
        }
        result[synonym_name] = key_value;
    }
    for (const auto& iter : map_2)
    {
        string synonym_name = iter.first;
        if (result.find(synonym_name) != result.end())
        { // presented
            continue;
        }
        vector<string> list_2 = iter.second;
        vector<string> key_value;
        for (auto p : position)
        {
            int pos = p.second;
            key_value.push_back(list_2[pos]);
        }
        result[synonym_name] = key_value;
    }
    return result;
}

vector<string> QueryEvaluator::get_common_part(const vector<string>& str_vec_1, vector<string> str_vec_2)
{
    vector<string> result;
    int i = 0;
    for (const auto& iter : str_vec_1)
    {
        if (count(str_vec_2.begin(), str_vec_2.end(), iter))
        {
            result.push_back(iter);
        }
        i++;
    }
    return result;
}
