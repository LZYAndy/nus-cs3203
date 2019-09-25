#include "ParentStarEvaluator.h"

unordered_map<string, vector<string>> ParentStarEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> empty_map;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared())
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Parent*(s, _)
            vector<int> int_vec = PKB.get_all_parent();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Parent*(s, 3)
            vector<int> int_vec = PKB.get_parent_star(stoi(second_name));
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (first_param.equals(second_param))
        {
            // e.g. Parent*(s, s)
            return empty_map;
        }
        else
        {
            // e.g. Parent*(s1, s2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_parent_star_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Parent*(_, s)
            vector<int> int_vec = PKB.get_all_children();
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(first_param))
        {
            // e.g. Parent*(1, s)
            vector<int> int_vec = PKB.get_children_star(stoi(first_name));
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
    }
    return result;
}

bool ParentStarEvaluator::evaluate_trivial(pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Parent*(_, _)
            result = PKB.does_parent_star_exist();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Parent*(_, 2)
            result = !PKB.get_parent_star(stoi(second_name)).empty();
        }
    }

    if (QueryUtility::is_statement_num(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Parent*(1, _)
            result = !PKB.get_children_star(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Parent*(1, 2)
            result = PKB.is_parent_star(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}
