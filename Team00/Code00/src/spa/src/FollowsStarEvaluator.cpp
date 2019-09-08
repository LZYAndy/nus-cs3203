#pragma once

#include "FollowsStarEvaluator.h"

unordered_map<string, vector<string>> FollowsStarEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();
    string select_name = select_entity.get_entity_name();

    if (first_param.is_entity_declared()) {
        if (second_name == "_") {

        } else if (QueryUtility::is_integer(second_name)) {

        } else if (first_name == second_name) { // two SEs or two OTs

        } else { // one SE and one OT
            if (first_name == select_name) {

            } else {

            }
        }
    }

    if (second_param.is_entity_declared()) {
        if (first_name == "_") {

        } else if (QueryUtility::is_integer(first_name)) {

        }
    }

    return result;
}

string FollowsStarEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param) {
    string result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_name == "_") {
        if (second_name == "_") {

        } else if (QueryUtility::is_integer(second_name)) {

        }
    }

    if (QueryUtility::is_integer(first_name)) {
        if (second_name == "_") {

        } else if (QueryUtility::is_integer(second_name)) {

        }
    }

    return result;
}
