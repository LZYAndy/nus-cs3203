#pragma once

#include "FollowsEvaluator.h"

vector<string> FollowsEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
                                                      pql_dto::Entity second_param, pql_dto::Entity select_entity) {
    vector<string> result;
    vector<string> empty_vec;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared()) {
        if (second_name == "_") {

        }
    }







//    if (first_param == select_entity) {
//        if (QueryUtility::is_integer(second_param)) {
//            int stmt_no = PKB().get_stmt_before(stoi(second_param));
//            if (stmt_no > 0) {
//                string stmt_type = PKB().get_stmt_type(stmt_no);
//                if (stmt_type == first_param_type) {
//                    result.insert(result.end(), to_string(stmt_no));
//                }
//            }
//        } else if (second_param == "_") {
//            vector<int> stmt_list = QueryUtility::get_certain_type_list()
//                                            = PKB().get_
//        } else if (first_param == second_param){
//            result.insert(result.end(), empty_vec);
//        } else {
//
//        }
//    }
//
//    if (second_param == select_entity) {

//    }
}

vector<string> FollowsEvaluator::evaluate_trivial(pql_dto::Entity first_param,
                                                  pql_dto::Entity second_param, pql_dto::Entity select_entity) {
    vector<string> result;
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
