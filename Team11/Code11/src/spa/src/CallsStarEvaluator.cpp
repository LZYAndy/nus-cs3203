#include "CallsStarEvaluator.h"

unordered_map<string, vector<string>> CallsStarEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
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
            // e.g. Calls*(p, _)
            vector<string> str_vec = PKB.get_all_procedures_calls();
            result = QueryUtility::mapping(first_param, str_vec);
        }
        else if (QueryUtility::is_proc_name(second_param))
        {
            // e.g. Calls*(p, "main")
            vector<string> str_vec = PKB.get_procedures_calls_star(second_name);
            result = QueryUtility::mapping(first_param, str_vec);
        }
        else if (first_param.equals(second_param))
        {
            // e.g. Calls*(p, p)
            return empty_map;
        }
        else
        {
            // e.g. Calls*(p, q)
            unordered_map<string, vector<string>> str_map = PKB.get_all_calls_star_relationship();
            result = QueryUtility::mapping(first_param, second_param, str_map);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Calls*(_, q)
            vector<string> str_vec = PKB.get_all_procedures_called();
            result = QueryUtility::mapping(second_param, str_vec);
        }
        else if (QueryUtility::is_proc_name(first_param))
        {
            // e.g. Calls*("main", q)
            vector<string> str_vec = PKB.get_procedures_called_star_by(first_name);
            result = QueryUtility::mapping(second_param, str_vec);
        }
    }
    return result;
}

bool CallsStarEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Calls*(_, _)
            result = PKB.does_calls_star_exist();
        }
        else if (QueryUtility::is_proc_name(second_param))
        {
            // e.g. Calls*(_, "main")
            result = !PKB.get_procedures_calls_star(second_name).empty();
        }
    }

    if (QueryUtility::is_proc_name(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Calls*("main", _)
            result = !PKB.get_procedures_called_star_by(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_proc_name(second_param))
        {
            // e.g. Calls("main", "sub")
            result = PKB.is_calls_star(first_name, second_name);
        }
    }
    return result;
}
