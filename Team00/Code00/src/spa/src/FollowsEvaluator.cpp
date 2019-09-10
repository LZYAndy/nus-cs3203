#include <unordered_map>
#include "FollowsEvaluator.h"

unordered_map<string, vector<string>> FollowsEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared()) {
        if (second_name == "_") { // e.g. Follows(s, _)
            result = QueryUtility::mapping(first_param, PKB::get_all_followed());
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Follows(s, 2)
            int first_stmt_num = PKB::get_followed_by(stoi(second_name));
            if (first_stmt_num > 0) {
                result = QueryUtility::mapping(first_param, first_stmt_num);
            } else {
                result[first_name] = empty_vec;
            }
        } else if (first_name == second_name) { // e.g. Follows(s, s)
            result[first_name] = empty_vec;
        } else { // e.g. Follows(s1, s2)
            result = QueryUtility::mapping(first_param, second_param, PKB::get_all_follows_relationship());
        }
    }

    if (second_param.is_entity_declared()) {
        if (first_name == "_") { // e.g. Follows(_, s)
            result = QueryUtility::mapping(second_param, PKB::get_all_follows());
        } else if (QueryUtility::is_integer(first_name)) { // e.g. Follows(1, s)
            int second_stmt_num = PKB::get_follows(stoi(first_name));
            if (second_stmt_num > 0) {
                result = QueryUtility::mapping(second_param, second_stmt_num);
            } else {
                result[second_name] = empty_vec;
            }
        }
    }

    return result;
}

bool FollowsEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_name == "_") {
        if (second_name == "_") { // e.g. Follows(_, _)
            return PKB::does_follows_exist();
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Follows(_, 2)
            return PKB::get_followed_by(stoi(second_name)) > 0;
        }
    }

    if (QueryUtility::is_integer(first_name)) {
        if (second_name == "_") { // e.g. Follows(1, _)
            return PKB::get_follows(stoi(first_name)) > 0;
        } else if (QueryUtility::is_integer(second_name)) { // e.g. Follows(1, 2)
            return PKB::is_follows(stoi(first_name), stoi(second_name));
        }
    }
}
