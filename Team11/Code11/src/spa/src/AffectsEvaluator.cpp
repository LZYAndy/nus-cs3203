#include "AffectsEvaluator.h"

unordered_map<string, vector<string>> AffectsEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
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
            // e.g. Affects(a, _)
            vector<int> int_vec = PKB.get_all_assigns_affect();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Affects(a, 2)
            vector<int> int_vec = PKB.get_assigns_affect(stoi(second_name));
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (first_param.equals(second_param))
        {
            // e.g. Affects(a, a)
            unordered_map<int, vector<int>> int_map = PKB.get_all_affects_relationship();
            result = QueryUtility::mapping(first_param, second_param, first_name, second_name, int_map, PKB);
        }
        else
        {
            // e.g. Affects(a1, a2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_affects_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Affects(_, a)
            vector<int> int_vec = PKB.get_all_assigns_affected();
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(first_param))
        {
            // e.g. Affects(1, a)
            vector<int> int_vec = PKB.get_assigns_affected_by(stoi(first_name));
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
    }
    return result;
}

bool AffectsEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Affects(_, _)
            result = PKB.does_affects_exist();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Affects(_, 2)
            result = !PKB.get_assigns_affect(stoi(second_name)).empty();
        }
    }

    if (QueryUtility::is_statement_num(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Affects(1, _)
            result = !PKB.get_assigns_affected_by(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Affects(1, 2)
            result = PKB.is_affects(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}
