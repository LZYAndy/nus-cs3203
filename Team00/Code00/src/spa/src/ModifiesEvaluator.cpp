#include "ModifiesEvaluator.h"

unordered_map<string, vector<string>> ModifiesEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.is_entity_declared()) {
        if (QueryUtility::is_integer(first_name)) { // e.g. Modifies(1, v)
            result = QueryUtility::mapping(second_param, PKB::get_modified_by_statement(stoi(first_name)));
        } else if (QueryUtility::is_proc_name(first_param)) { // e.g. Modifies("main", v)
            result = QueryUtility::mapping(second_param, PKB::get_modified_by_procedure(first_name));
        } else if (QueryUtility::is_proc_declared(first_param)) { // e.g. Modifies(p, v)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_modifies_procedure_relationship());
        } else { // e.g. Modifies(s, v)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_modifies_statement_relationship());
        }
    } else if (QueryUtility::is_proc_declared(first_param)) {
        if (second_name == "_") { // e.g. Modifies(p, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_modifies_procedure());
        } else if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(p, "x")
            result = QueryUtility::mapping(first_param, PKB::get_procedures_modifies(second_name));
        }
    } else {
        if (second_name == "_") { // e.g. Modifies(s, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_modifies_statement());
        } else if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(s, "x")
            result = QueryUtility::mapping(first_param, PKB::get_statements_modifies(second_name));
        }
    }

    return result;
}

bool ModifiesEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (QueryUtility::is_integer(first_name)) {
        if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(1, "x")
            return PKB::is_modifies(stoi(first_name), second_name);
        } else if (second_name == "_") { // e.g. Modifies(1, _)
            return !PKB::get_modified_by_statement(stoi(first_name)).empty();
        }
    } else if (QueryUtility::is_proc_name(first_param)) {
        if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies("main", "x")
            return PKB::is_modifies(first_name, second_name);
        } else if (second_name == "_") { // e.g. Modifies("main", _)
            return !PKB::get_modified_by_procedure().empty(first_name);
        }
    }
}
