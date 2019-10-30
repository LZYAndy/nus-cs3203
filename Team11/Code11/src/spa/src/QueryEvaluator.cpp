#include "QueryEvaluator.h"

unordered_set<string> QueryEvaluator::get_result(string &query, PKB &PKB)
{
    string error_msg;
    Cache cache;
    bool is_select_bool = false;
    unordered_set<string> result;
    unordered_set<string> empty_set;

    map<string, vector<string>> select_map;
    unordered_map<string, vector<string>> have_synonym_in_select_map;
    unordered_map<string, vector<string>> final_map;
    unordered_map<string, vector<string>> intermediary_map;

    vector<pql_dto::Entity> select_clause;
    vector<pql_dto::Relationships> such_that_clause;
    vector<pql_dto::Pattern> pattern_clause;
    vector<pql_dto::With> with_clause;
    deque<pql_dto::Constraint> no_synonym_clauses;
    deque<pql_dto::Constraint> synonym_clauses;
    vector<vector<pql_dto::Constraint>> synonyms_not_in_select_clauses;
    vector<vector<pql_dto::Constraint>> synonyms_in_select_clauses;

    /*
     * parse the PQL query
     */
    error_msg = PQLParser::pql_parse_query(move(query), select_clause, such_that_clause, pattern_clause, with_clause);

    // syntactic or symmetric errors
    if (!error_msg.empty())
    {
        if (select_clause.at(0).get_entity_type() == EntityType::BOOLEAN)
        {
            return unordered_set<string> {"FALSE"};
        }
        return empty_set;
    }

    // pass to optimizer
    error_msg = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

    // evaluate select clause
    if (!select_clause.empty())
    {
        // has select
        for (auto select_entity : select_clause)
        {
            string select_name = select_entity.get_entity_name();
            EntityType select_type = select_entity.get_entity_type();
            if (select_type == EntityType::BOOLEAN)
            {
                is_select_bool = true;
            }
            else if (select_type == EntityType::FIX)
            {
                select_map[select_name] = vector<string> {select_entity.get_solution()};
            }
            else if (select_type == EntityType::VARIABLE || select_type == EntityType::PROCEDURE || select_type == EntityType::CONSTANT || select_type == EntityType::BOOLEAN)
            {
                select_map[select_name] = QueryUtility::get_certain_type_str_list(select_type, PKB);
            }
            else
            {
                select_map[select_name] = QueryUtility::get_certain_type_int_list(select_type, PKB);
            }
        }
    }

    // have clauses with no synonym
    if (!no_synonym_clauses.empty())
    {
        bool bool_clauses_result = QueryEvaluator::evaluateBoolGroup(no_synonym_clauses, PKB, cache);
        if (!bool_clauses_result)
        {
            return QueryEvaluator::evaluateEmptyMap(is_select_bool);
        }
    }

    // have clauses with synonym(s)
    if (!synonym_clauses.empty())
    {
        error_msg = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clauses, synonyms_not_in_select_clauses);
    }

    // have clauses with synonym(s) and synonym(s) are not in select clause
    if (!synonyms_not_in_select_clauses.empty())
    {
        bool is_satisfy;
        for (vector<pql_dto::Constraint> group : synonyms_not_in_select_clauses)
        {
            is_satisfy = QueryEvaluator::evaluateGroup(group, PKB, cache);
            if (!is_satisfy)
            {
                return QueryEvaluator::evaluateEmptyMap(is_select_bool);
            }
        }
    }
    // sort
    // merge

    // have clauses with synonym(s) and synonym(s) are in select clause
    if (!synonyms_in_select_clauses.empty())
    {
        bool is_satisfy;
        for (vector<pql_dto::Constraint> group : synonyms_in_select_clauses)
        {
            is_satisfy = QueryEvaluator::evaluateGroup(group, PKB, cache);
            if (!is_satisfy)
            {
                return QueryEvaluator::evaluateEmptyMap(is_select_bool);
            }
        }
    }
    // sort
    // merge

    // Select synonyms
    result = QueryEvaluator::select(select_clause, select_map, final_map, PKB);
    return result;
}

unordered_set<string> QueryEvaluator::select(vector<pql_dto::Entity> &select_clause,
        map<string, vector<string>> &select_map,
        unordered_map<string, vector<string>> &final_map,
        PKB &PKB)
{
    unordered_set<string> result;
    vector<vector<string>> result_vec;
    unordered_map<string, vector<string>> result_map;

    if (select_clause.at(0).get_entity_type() == EntityType::BOOLEAN)
    { // if the select type is BOOLEAN
        if (QueryEvaluator::is_empty_map(final_map))
        {
            return unordered_set<string> ({"TRUE"});
        }
    }
    // if the select type is tuple
    unordered_set<string> common_select_synonyms = QueryEvaluator::get_common_synonyms(final_map, select_map);
    unordered_map<string, vector<string>> acc_map;

    if (!common_select_synonyms.empty())
    { // select_map and final_map get common synonyms
        for (const auto& common : common_select_synonyms)
        {
            select_map[common] = final_map[common];
        }
    }

    // cross product
    bool is_first_common_synonym = true;
    for (const auto& synonym : select_map)
    {
        unordered_map<string, vector<string>> temp_map;
        if (common_select_synonyms.find(synonym.first) != common_select_synonyms.end() && is_first_common_synonym)
        {
            is_first_common_synonym = false;
            for (const auto& cs : common_select_synonyms)
            {
                temp_map[cs] = QueryUtility::change_to_attributes(select_clause.at(QueryEvaluator::get_element_index_in_map(select_map, cs)), select_map.at(cs), PKB);
            }
        }
        else if (common_select_synonyms.find(synonym.first) != common_select_synonyms.end())
        {
            continue;
        }
        else
        {
            temp_map[synonym.first] = QueryUtility::change_to_attributes(select_clause.at(QueryEvaluator::get_element_index_in_map(select_map, synonym.first)), synonym.second, PKB);
        }
        acc_map = QueryEvaluator::merge_two_maps(temp_map, acc_map, QueryEvaluator::get_common_synonyms(temp_map, acc_map));
    }
    result_vec.reserve(select_clause.size());
    for (auto entity : select_clause)
    {
        result_vec.push_back(acc_map.at(entity.get_entity_name()));
    }
    int height = result_vec.at(0).size();
    int width = result_vec.size();
    vector<string> temp_vec;
    temp_vec.reserve(height);
    for (int i = 0; i < height; i++)
    {
        temp_vec.emplace_back("");
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (temp_vec.at(i).empty())
            {
                temp_vec.at(i) = temp_vec.at(i) + result_vec.at(j).at(i);
            }
            else
            {
                temp_vec.at(i) = temp_vec.at(i) + " " + result_vec.at(j).at(i);
            }
        }
    }
    std::copy(temp_vec.begin(),temp_vec.end(),std::inserter(result, result.end()));
    return result;
}

unordered_map<string, vector<string>> QueryEvaluator::mergeGroup(vector<pql_dto::Constraint> &group, Cache &cache)
{
    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> empty_map;
    unordered_map<string, vector<string>> intermediary_map;

    for (pql_dto::Constraint clause : group)
    {
        intermediary_map = cache.get_clause_map(clause);
        unordered_set<string> common_synonyms = QueryEvaluator::get_common_synonyms(result, intermediary_map);
        result = QueryEvaluator::merge_two_maps(result, intermediary_map, common_synonyms);
        if (QueryEvaluator::is_empty_map(result))
        {
            return empty_map;
        }
    }

    return result;
}

bool QueryEvaluator::evaluateBoolGroup(deque<pql_dto::Constraint> &group, PKB &PKB, Cache &cache)
{
    // can only be such that clauses
    bool result;
    for (pql_dto::Constraint clause : group)
    {
        pql_dto::Relationships relation = clause.get_relationship();
        result = QueryEvaluator::evaluateSuchThat(relation, PKB, cache).first;
        if (!result)
        {
            return false;
        }
    }
    return true;
}

bool QueryEvaluator::evaluateGroup(vector<pql_dto::Constraint> &group, PKB &PKB, Cache &cache)
{
    unordered_map<string, vector<string>> empty_map;
    unordered_map<string, vector<string>> intermediary_map;
    unordered_map<string, vector<string>> merged_map;

    for (pql_dto::Constraint clause : group)
    {
        if (!cache.get_similar_clause_map(clause).empty())
        {
            intermediary_map = cache.get_similar_clause_map(clause);
        }
        else if (clause.is_relationship())
        {
            pql_dto::Relationships relation = clause.get_relationship();
            intermediary_map = QueryEvaluator::evaluateSuchThat(relation, PKB, cache).second;
        }
        else if (clause.is_pattern())
        {
            pql_dto::Pattern pattern = clause.get_pattern();
            intermediary_map = QueryEvaluator::evaluatePattern(pattern, PKB, cache);
        }
        else if (clause.is_with())
        {
            pql_dto::With with = clause.get_with();
            intermediary_map = QueryEvaluator::evaluateWith(with, PKB, cache);
        }
        if (QueryEvaluator::is_empty_map(intermediary_map))
        {
            return false;
        }
    }

    return true;
}

unordered_set<string> QueryEvaluator::evaluateEmptyMap(bool is_select_bool)
{
    if (is_select_bool)
    {
        return unordered_set<string> {"FALSE"};
    }
    else
    {
        return unordered_set<string> {};
    }
}

pair<bool, unordered_map<string, vector<string>>> QueryEvaluator::evaluateSuchThat(pql_dto::Relationships &relation, PKB &PKB, Cache &cache)
{
    unordered_map<string, vector<string>> empty_map;
    unordered_map<string, vector<string>> intermediary_map;
    bool trivial_result = false;

    RelationshipType relation_type = relation.get_relationship_type();
    pql_dto::Entity first_param = relation.get_first_param();
    pql_dto::Entity second_param = relation.get_second_param();

    if (relation_type == RelationshipType::FOLLOWS)
    {
        if (!relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = FollowsEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = FollowsEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
        else
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = FollowsStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = FollowsStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    if (relation_type == RelationshipType::USES)
    {
        if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
        {
            trivial_result = UsesEvaluator::evaluate_trivial(first_param, second_param, PKB);
            return make_pair(trivial_result, empty_map);
        }
        else
        {
            intermediary_map = UsesEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
        }
    }

    if (relation_type == RelationshipType::PARENT)
    {
        if (!relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = ParentEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = ParentEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
        else
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = ParentStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = ParentStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    if (relation_type == RelationshipType::MODIFIES)
    {
        if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
        {
            trivial_result = ModifiesEvaluator::evaluate_trivial(first_param, second_param, PKB);
            return make_pair(trivial_result, empty_map);
        }
        else
        {
            intermediary_map = ModifiesEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
        }
    }

    if (relation_type == RelationshipType::CALLS)
    {
        if (!relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = CallsEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = CallsEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
        else
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = CallsStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = CallsStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    if (relation_type == RelationshipType::NEXT)
    {
        if (!relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = NextEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = NextEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
        else
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = NextStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = NextStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    if (relation_type == RelationshipType::AFFECTS)
    {
        if (!relation.is_relationship_star())
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = AffectsEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = AffectsEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
        else
        {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared())
            {
                trivial_result = AffectsStarEvaluator::evaluate_trivial(first_param, second_param, PKB);
                return make_pair(trivial_result, empty_map);
            }
            else
            {
                intermediary_map = AffectsStarEvaluator::evaluate_non_trivial(first_param, second_param, PKB);
            }
        }
    }

    cache.insert_clause(relation, first_param, second_param, intermediary_map);
    return make_pair(trivial_result, empty_map);
}

unordered_map<string, vector<string>> QueryEvaluator::evaluatePattern(pql_dto::Pattern &pattern, PKB &PKB, Cache &cache)
{
    unordered_map<string, vector<string>> intermediary_map;

    EntityType pattern_type = pattern.get_pattern_entity().get_entity_type();
    pql_dto::Entity first_param = pattern.get_first_param();
    pql_dto::Entity second_param = pattern.get_second_param();
    if (pattern_type == EntityType::ASSIGN)
    {
        intermediary_map = AssignEvaluator::evaluate(pattern, first_param, second_param, PKB);
    }
    if (pattern_type == EntityType::IF)
    {
        intermediary_map = IfEvaluator::evaluate(pattern, first_param, second_param, PKB);
    }
    if (pattern_type == EntityType::WHILE)
    {
        intermediary_map = WhileEvaluator::evaluate(pattern, first_param, second_param, PKB);
    }

    cache.insert_clause(pattern, first_param, second_param, intermediary_map);
    return intermediary_map;
}

unordered_map<string, vector<string>> QueryEvaluator::evaluateWith(pql_dto::With &with, PKB &PKB, Cache &cache)
{
    unordered_map<string, vector<string>> intermediary_map;
    pql_dto::Entity first_param = with.get_first_param();
    pql_dto::Entity second_param = with.get_second_param();
    intermediary_map = WithEvaluator::evaluate(first_param, second_param, PKB);
    cache.insert_clause(with, first_param, second_param, intermediary_map);
    return intermediary_map;
}

int QueryEvaluator::get_element_index_in_map(map<string, vector<string>> &map, string key)
{
    int i = 0;
    int result = 0;
    for (const auto &iter : map)
    {
        if (key == iter.first)
        {
            result = i;
        }
        i++;
    }
    return result;
}

bool QueryEvaluator::is_empty_map(unordered_map<string, vector<string>> &map)
{
    if (map.empty())
    {
        return true;
    }
    for (const auto &iter : map)
    {
        if (iter.second.empty())
        {
            return true;
        }
    }
    return false;
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

unordered_set<string> QueryEvaluator::get_common_synonyms(unordered_map<string, vector<string>> &map_1,
        map<string, vector<string>> &map_2)
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

unordered_map<string, vector<string>> QueryEvaluator::merge_two_maps(unordered_map<string, vector<string>> map_1,
        unordered_map<string, vector<string>> map_2, unordered_set<string> common_part)
{
    unordered_map<string, vector<string>> result;
    vector<string> common_synonyms(common_part.size());
    copy(common_part.begin(), common_part.end(), common_synonyms.begin());
    vector<pair<int, int>> position;
    vector<string> map_sample_1;
    vector<string> map_sample_2;
    if (common_synonyms.empty())
    { // no common synonyms, cross product
        if (QueryEvaluator::is_empty_map(map_1))
        {
            return map_2;
        }
        if (QueryEvaluator::is_empty_map(map_2))
        {
            return map_1;
        }
        for (const auto &sample_1 : map_1)
        {
            map_sample_1 = sample_1.second;
            break;
        }
        for (const auto &sample_2 : map_2)
        {
            map_sample_2 = sample_2.second;
            break;
        }
        int i = 0;
        for (const auto &element_1 : map_sample_1)
        {
            int j = 0;
            for (const auto &element_2 : map_sample_2)
            {
                pair<int, int> int_pair (i, j);
                position.push_back(int_pair);
                j++;
            }
            i++;
        }
    }
    else
    { // with common synonyms, get the common lines
        int i = 0;
        for (const auto &element_1 : map_1.at(common_synonyms[0]))
        {
            int j = 0;
            for (const auto &element_2 : map_2.at(common_synonyms[0]))
            {
                bool is_same = true;
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
    }

    for (const auto &iter : map_1)
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
    for (const auto &iter : map_2)
    {
        string synonym_name = iter.first;
        if (result.find(synonym_name) != result.end())
        {
            // presented
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
