#include "ParentStarEvaluator.h"

unordered_map<string, vector<string>> ParentStarEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared()) {
        if (second_name == "_") { // e.g. Parent*(s, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_parent());
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Parent*(s, 3)
            result = QueryUtility::mapping(first_param, PKB::get_parent_star(stoi(second_name)))
        } else if (first_name == second_name) { // e.g. Parent*(s, s)
            result[first_name] = empty_vec;
        } else { // e.g. Parent*(s1, s2)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_parent_star_relationship())
        }
    }

    if (second_param.is_entity_declared()) {
        if (first_name == "_") { // e.g. Parent*(_, s)
            result = QueryUtility::mapping(second_param, PKB::get_all_children());
        } else if (QueryUtility::is_integer(first_name)) { // e.g. Parent*(1, s)
            result = QueryUtility::mapping(second_param, PKB::get_children_star(stoi(first_name)));
        }
    }

    return result;
}

bool ParentStarEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_name == "_") {
        if (second_name == "_") { // e.g. Parent*(_, _)
            return PKB::does_parent_star_exist();
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Parent*(_, 2)
            return !PKB::get_parent_star(stoi(second_name)).empty();
        }
    }

    if (QueryUtility::is_integer(first_name)) {
        if (second_name == "_") { // e.g. Parent*(1, _)
            return !PKB::get_children_star(stoi(first_name)).empty();
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Parent*(1, 2)
            return PKB::is_parent_star(stoi(first_name), stoi(second_name));
        }
    }
}
