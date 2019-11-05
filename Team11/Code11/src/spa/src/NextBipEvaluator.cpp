#include "NextBipEvaluator.h"

unordered_map<string, vector<string>> NextBipEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
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
            // e.g. NextBip(n, _)
            vector<int> int_vec = PKB.get_all_previous_bip();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_program_line(second_param))
        {
            // e.g. NextBip(n, 2)
            vector<int> int_vec = PKB.get_previous_bip(stoi(second_name));
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (first_param.equals(second_param))
        {
            // e.g. NextBip(n, n)
            return empty_map;
        }
        else
        {
            // e.g. NextBip(n1, n2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_next_bip_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. NextBip(_, n)
            vector<int> int_vec = PKB.get_all_next_bip();
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
        else if (QueryUtility::is_program_line(first_param))
        {
            // e.g. NextBip(1, n)
            vector<int> int_vec = PKB.get_next_bip(stoi(first_name));
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
    }
    return result;
}

bool NextBipEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. NextBip(_, _)
            result = PKB.does_next_bip_exists();
        }
        else if (QueryUtility::is_program_line(second_param))
        {
            // e.g. NextBip(_, 2)
            result = !PKB.get_previous_bip(stoi(second_name)).empty();
        }
    }

    if (QueryUtility::is_program_line(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Next(1, _)
            result = !PKB.get_next_bip(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_program_line(second_param))
        {
            // e.g. Next(1, 2)
            result = PKB.is_next_bip(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}
