#include "UsesEvaluator.h"

unordered_map<string, vector<string>> UsesEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    PKB PKB;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.is_entity_declared())
    {
        if (CheckerUtil::is_const_valid(first_name))
        { // e.g. Uses(1, v)
            vector<string> str_vec = PKB.get_used_by_statement(stoi(first_name));
            result = QueryUtility::mapping(second_param, str_vec);
        }
        else if (QueryUtility::is_proc_name(first_param))
        { // e.g. Uses("main", v)
            vector<string> str_vec = PKB.get_used_by_procedure(first_name);
            result = QueryUtility::mapping(second_param, str_vec);
        }
        else if (QueryUtility::is_proc_declared(first_param))
        { // e.g. Uses(p, v)
            unordered_map<string, vector<string>> str_map = PKB.get_all_uses_procedures_relationship();
            result = QueryUtility::mapping(first_param, second_param, str_map);
        }
        else
        { // e.g. Uses(s, v)
            unordered_map<int, vector<string>> int_str_map = PKB.get_all_uses_statements_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_str_map);
        }
    }
    else if (QueryUtility::is_proc_declared(first_param))
    {
        if (second_name == "_")
        { // e.g. Uses(p, _)
            vector<string> str_vec = PKB.get_all_uses_procedures();
            result = QueryUtility::mapping(first_param, str_vec);
        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(p, "x")
            vector<string> str_vec = PKB.get_procedures_uses(second_name);
            result = QueryUtility::mapping(first_param, str_vec);
        }
    }
    else
    {
        if (second_name == "_")
        { // e.g. Uses(s, _)
            vector<int> int_vec = PKB.get_all_uses_statements();
            result = QueryUtility::mapping(first_param, int_vec);
        }
        else if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(s, "x")
            vector<int> int_vec = PKB.get_statements_uses(second_name);
            result = QueryUtility::mapping(first_param, int_vec);
        }
    }

    return result;
}

bool UsesEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    vector<string> empty_vec;
    bool result = false;
    PKB PKB;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (CheckerUtil::is_const_valid(first_name))
    {
        if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses(1, "x")
            result = PKB.is_uses(stoi(first_name), second_name);
        }
        else if (second_name == "_")
        { // e.g. Uses(1, _)
            result = !PKB.get_used_by_statement(stoi(first_name)).empty();
        }
    }
    else if (QueryUtility::is_proc_name(first_param))
    {
        if (QueryUtility::is_var_name(second_param))
        { // e.g. Uses("main", "x")
            result = PKB.is_uses(first_name, second_name);
        }
        else if (second_name == "_")
        { // e.g. Uses("main", _)
            result = !PKB.get_used_by_procedure(first_name).empty();
        }
    }
    return result;
}
