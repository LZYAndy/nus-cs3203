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
            result = QueryUtility::mapping(second_param, PKB::get_used_by_statement(stoi(first_name)));
        }
        else if (QueryUtility::is_proc_name(first_param))
        { // e.g. Uses("main", v)
            result = QueryUtility::mapping(second_param, PKB::get_used_by_procedure(first_name));
        }
        else if (QueryUtility::is_proc_declared(first_param))
        { // e.g. Uses(p, v)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_uses_procedure_relationship());
        }
        else
        { // e.g. Uses(s, v)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_uses_statement_relationship());
        }
    }
    else if (QueryUtility::is_proc_declared(first_param))
    {
        if (second_name == "_")
        { // e.g. Uses(p, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_uses_procedure());
        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(p, "x")
            result = QueryUtility::mapping(first_param, PKB::get_procedures_uses(second_name));
        }
    }
    else
    {
        if (second_name == "_")
        { // e.g. Uses(s, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_uses_statement());
        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(s, "x")
            result = QueryUtility::mapping(first_param, PKB::get_statements_uses(second_name));
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
            return PKB::is_uses(stoi(first_name), second_name);
        }
        else if (second_name == "_")
        { // e.g. Uses(1, _)
            return !PKB::get_used_by_statement(stoi(first_name)).empty();
        }
    }
    else if (QueryUtility::is_proc_name(first_param))
    {
        if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses("main", "x")
            return PKB::is_uses(first_name, second_name);
        }
        else if (second_name == "_")
        { // e.g. Uses("main", _)
            return !PKB::get_used_by_procedure().empty(first_name);
        }
    }
}
