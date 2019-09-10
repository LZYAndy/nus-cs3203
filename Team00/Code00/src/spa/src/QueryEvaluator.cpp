#include "QueryEvaluator.h"

vector<string> QueryEvaluator::get_result(string query)
{

    string error_msg;
    vector<string> result;
    vector<string> empty_vec;

    unordered_map<string, vector<string>> select_list;
    unordered_map<string, vector<string>> such_that_list;
    unordered_map<string, vector<string>> pattern_list;

    vector<pql_dto::Entity> declaration_clause;
    vector<pql_dto::Entity> select_clause;
    vector<pql_dto::Relationships> such_that_clause;
    vector<pql_dto::Pattern> pattern_clause;

    /*
     * parse the PQL query
     */
    error_msg = PQLParser::pql_parse_query(query, declaration_clause, select_clause,
            such_that_clause, pattern_clause);
    if (error_msg.empty())
    {
        return empty_vec;
    }

    pql_dto::Entity select_entity = select_clause.front();
    string select_name = select_entity.get_entity_name();
    pql_dto::Relationships & relation = such_that_clause.front();
    pql_dto::Pattern pattern = pattern_clause.front();

    if (!select_clause.empty())
    { // has select
        EntityType select_type = select_entity.get_entity_type();
        select_list[select_name] = QueryUtility::get_certain_type_list(select_type);
    }

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

        }
    }

    // Merge three lists
    result = QueryEvaluator::take_common_part(select_entity, select_list, such_that_list, pattern_list);
    return result;
}

vector<string> QueryEvaluator::take_common_part(pql_dto::Entity select_entity,
        unordered_map<string, vector<string>> select_list,
        unordered_map<string, vector<string>> such_that_list,
        unordered_map<string, vector<string>> pattern_list)
{

    string select_name = select_entity.get_entity_name();
    vector<string> vector_1;
    vector<string> vector_2;
    vector<string> select = select_list[select_name];
    vector<string> such_that;
    vector<string> pattern;

    if (such_that_list.find(select_name) == such_that_list.end())
    {
        such_that = select;
    }
    else
    {
        such_that = such_that_list[select_name];
    }

    if (pattern_list.find(select_name) == pattern_list.end())
    {
        pattern = select;
    }
    else
    {
        pattern = pattern_list[select_name];
    }

    set_intersection(select.begin(), select.end(), such_that.begin(),
            such_that.end(), back_inserter(vector_1));
    set_intersection(vector_1.begin(), vector_1.end(), pattern.begin(),
            pattern.end(), back_inserter(vector_2));

    return vector_2;
}
