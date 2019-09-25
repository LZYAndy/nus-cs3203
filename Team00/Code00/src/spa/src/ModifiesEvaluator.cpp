#include "ModifiesEvaluator.h"

unordered_map<string, vector<string>> ModifiesEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.is_entity_declared())
    {
        if (QueryUtility::is_statement_num(first_param))
        {
            // e.g. Modifies(1, v)
            vector<string> str_vec = PKB.get_modified_by_statement(stoi(first_name));
            result = QueryUtility::mapping(second_param, str_vec);
        }
        else if (QueryUtility::is_proc_name(first_param))
        {
            // e.g. Modifies("main", v)
            vector<string> str_vec = PKB.get_modified_by_procedure(first_name);
            result = QueryUtility::mapping(second_param, str_vec);
        }
        else if (QueryUtility::is_proc_declared(first_param))
        {
            // e.g. Modifies(p, v)
            unordered_map<string, vector<string>> str_map = PKB.get_all_modifies_procedures_relationship();
            result = QueryUtility::mapping(first_param, second_param, str_map);
        }
        else
        {
            // e.g. Modifies(s, v)
            unordered_map<int, vector<string>> int_str_vec = PKB.get_all_modifies_statements_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_str_vec, PKB);
        }
    }
    else if (QueryUtility::is_proc_declared(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Modifies(p, _)
            vector<string> str_vec = PKB.get_all_modifies_procedures();
            result = QueryUtility::mapping(first_param, str_vec);
        }
        else if (QueryUtility::is_var_name(second_param))
        {
            // e.g. Modifies(p, "x")
            vector<string> str_vec = PKB.get_procedures_modifies(second_name);
            result = QueryUtility::mapping(first_param, str_vec);
        }
    }
    else
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Modifies(s, _)
            vector<int> int_vec = PKB.get_all_modifies_statements();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_var_name(second_param))
        {
            // e.g. Modifies(s, "x")
            vector<int> int_vec = PKB.get_statements_modifies(second_name);
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
    }
    return result;
}

bool ModifiesEvaluator::evaluate_trivial(pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (QueryUtility::is_statement_num(first_param))
    {
        if (QueryUtility::is_var_name(second_param))
        {
            // e.g. Modifies(1, "x")
            result = PKB.is_modifies(stoi(first_name), second_name);
        }
        else if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Modifies(1, _)
            result = !PKB.get_modified_by_statement(stoi(first_name)).empty();
        }
    }
    else if (QueryUtility::is_proc_name(first_param))
    {
        if (QueryUtility::is_var_name(second_param))
        {
            // e.g. Modifies("main", "x")
            result = PKB.is_modifies(first_name, second_name);
        }
        else if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Modifies("main", _)
            result = !PKB.get_modified_by_procedure(first_name).empty();
        }
    }
    return result;
}
