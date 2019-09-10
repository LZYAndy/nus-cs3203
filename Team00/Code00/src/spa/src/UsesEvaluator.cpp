#include "UsesEvaluator.h"

unordered_map<string, vector<string>> UsesEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.is_entity_declared())
    {
        if (QueryUtility::is_integer(first_name))
        { // e.g. Uses(1, v)

        }
        else if (QueryUtility::is_proc_name(first_param))
        { // e.g. Uses("main", v)

        }
        else if (QueryUtility::is_proc_declared(first_param))
        { // e.g. Uses(p, v)

        }
        else
        { // e.g. Uses(s, v)

        }
    }
    else if (QueryUtility::is_proc_declared(first_param))
    {
        if (second_name == "_")
        { // e.g. Uses(p, _)

        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(p, "x")

        }
    }
    else
    {
        if (second_name == "_")
        { // e.g. Uses(s, _)

        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(s, "x")

        }
    }

    return result;
}

bool UsesEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (QueryUtility::is_integer(first_name))
    {
        if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(1, "x")

        }
        else if (second_name == "_")
        { // e.g. Uses(1, _)

        }
    }
    else if (QueryUtility::is_proc_name(first_param))
    {
        if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses("main", "x")

        }
        else if (second_name == "_")
        { // e.g. Uses("main", _)

        }
    }
}
