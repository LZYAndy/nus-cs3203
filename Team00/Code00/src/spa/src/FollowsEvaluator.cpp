#pragma once

#include <unordered_map>
#include "FollowsEvaluator.h"

unordered_map<string, vector<string>> FollowsEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    EntityType first_type = first_param.get_entity_type();
    EntityType second_type = second_param.get_entity_type();
    unordered_map<int, int> all_follows = PKB::get_all_follows();
    unordered_map<int, int>::iterator iter;

    if (first_param.is_entity_declared()) {
        if (second_name == "_") {
            if (all_follows.empty()) {
                result[first_name] = empty_vec;
            } else {
                vector<string> first_param_vector;
                for (iter=all_follows.begin();iter!=all_follows.end();iter++) {
                    int first_stmt_num = iter->first;
                    if (PKB::get_statement_type(first_stmt_num) == first_type) {
                        first_param_vector.push_back(to_string(first_stmt_num));
                    }
                }
                result[first_name] = first_param_vector;
            }
        } else if (QueryUtility::is_integer(second_name)) {
            int first_stmt_num = PKB::get_followed_by(stoi(second_name));
            if (first_stmt_num > 0) {
                vector<string> first_param_vector;
                if (PKB::get_statement_type(first_stmt_num) == first_type) {
                    first_param_vector.push_back(to_string(first_stmt_num));
                }
                result[first_name] = first_param_vector;
            } else {
                result[first_name] = empty_vec;
            }
        } else if (first_name == second_name) { // e.g. Follows(s, s)
            result[first_name] = empty_vec;
        } else { // e.g. Follows(s1, s2)
            vector<string> first_param_vector;
            vector<string> second_param_vector;
            for (iter=all_follows.begin();iter!=all_follows.end();iter++) {
                int first_stmt_num = iter->first;
                int second_stmt_num = iter->second;
                if (PKB::get_statement_type(first_stmt_num) == first_type &&
                PKB::get_statement_type(second_stmt_num) == second_type) {
                    first_param_vector.push_back(to_string(first_stmt_num));
                    second_param_vector.push_back(to_string(second_stmt_num));
                }
            }
            result[first_name] = first_param_vector;
            result[second_name] = second_param_vector;
        }
    }

    if (second_param.is_entity_declared()) {
        if (first_name == "_") {
            if (all_follows.empty()) {
                result[second_name] = empty_vec;
            } else {
                vector<string> second_param_vector;
                for (iter=all_follows.begin();iter!=all_follows.end();iter++) {
                    int second_stmt_num = iter->second;
                    if (PKB::get_statement_type(second_stmt_num) == second_type) {
                        second_param_vector.push_back(to_string(second_stmt_num));
                    }
                }
                result[second_name] = second_param_vector;
            }
        } else if (QueryUtility::is_integer(first_name)) {
            int second_stmt_num = PKB::get_follows(stoi(first_name));
            if (second_stmt_num > 0) {
                vector<string> second_param_vector;
                if (PKB::get_statement_type(second_stmt_num) == second_type) {
                    second_param_vector.push_back(to_string(second_stmt_num));
                }
                result[second_name] = second_param_vector;
            } else {
                result[second_name] = empty_vec;
            }
        }
    }

    return result;
}

string FollowsEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {

    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    unordered_map<int, int> all_follows = PKB::get_all_follows();

    if (all_follows.empty()) {
        return "False";
    }

    if (first_name == "_") {
        if (second_name == "_") {
            return "True";
        } else if (QueryUtility::is_integer(second_name)) {
            if (PKB::get_followed_by(stoi(second_name)) > 0) {
                return "True";
            } else {
                return "False";
            }
        }
    }

    if (QueryUtility::is_integer(first_name)) {
        if (second_name == "_") {
            if (PKB::get_follows(stoi(first_name)) > 0) {
                return "True";
            } else {
                return "False";
            }
        } else if (QueryUtility::is_integer(second_name)) {
            if (PKB::get_follows(stoi(first_name)) == stoi(second_name)) {
                return "True";
            } else {
                return "False";
            }
        }
    }
}
