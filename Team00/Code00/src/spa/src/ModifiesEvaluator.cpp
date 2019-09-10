#include "ModifiesEvaluator.h"

unordered_map<string, vector<string>> ModifiesEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.is_entity_declared()) {
        if (QueryUtility::is_integer(first_name)) { // e.g. Modifies(1, v)

        } else if (QueryUtility::is_proc_name(first_param)) { // e.g. Modifies("main", v)

        } else if (QueryUtility::is_proc_declared(first_param)) { // e.g. Modifies(p, v)

        } else { // e.g. Modifies(s, v)

        }
    } else if (QueryUtility::is_proc_declared(first_param)) {
        if (second_name == "_") { // e.g. Modifies(p, _)

        } else if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(p, "x")

        }
    } else {
        if (second_name == "_") { // e.g. Modifies(s, _)

        } else if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(s, "x")

        }
    }

    return result;
}

bool ModifiesEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    string result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (QueryUtility::is_integer(first_name)) {
        if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies(1, "x")

        } else if (second_name == "_") { // e.g. Modifies(1, _)

        }
    } else if (QueryUtility::is_proc_name(first_param)) {
        if (QueryUtility::is_var_name(second_param)) { // e.g. Modifies("main", "x")

        } else if (second_name == "_") { // e.g. Modifies("main", _)

        }
    }
}
