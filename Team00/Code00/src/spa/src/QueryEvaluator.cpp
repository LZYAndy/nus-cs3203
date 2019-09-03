#pragma once

#include "QueryEvaluator.h"

vector<string> QueryEvaluator::get_result(string query) {

    string error_msg;
    vector<string> result;
    vector<string> empty_vec;

    vector<string> select_list;
    vector<string> such_that_list;
    vector<string> pattern_list;

    vector<pql_dto::Entity> declaration_clause;
    vector<pql_dto::Entity> select_clause;
    vector<pql_dto::Relationships> such_that_clause;
    vector<pql_dto::Pattern> pattern_clause;

    /*
     * parse the PQL query
     */
    error_msg = PQLParser::pql_parse_query(query, declaration_clause, select_clause, such_that_clause, pattern_clause);
    if (error_msg.empty()) {
        return empty_vec;
    }

    pql_dto::Entity select_entity = select_clause.front();
    pql_dto::Relationships relation = such_that_clause.front();
    pql_dto::Pattern pattern = pattern_clause.front();

    if (!select_clause.empty()) { // has select
        string select_type = select_entity.get_entity_type();
        select_list = QueryUtility::get_certain_type_list(select_type);
    }

    if (!such_that_clause.empty()) { // has such that
        RelationshipTypes relation_type = relation.get_relationship();
        pql_dto::Entity first_param = relation.get_first_param();
        pql_dto::Entity second_param = relation.get_second_param();

        if (relation_type == RelationshipTypes::FOLLOWS && !relation.is_relationship_star()) {
            if (!first_param.is_entity_declared() && !second_param.is_entity_declared()) {
                such_that_list = FollowsEvaluator::evaluate_trivial(first_param, second_param, select_entity);
            } else {
                such_that_list = FollowsEvaluator::evaluate_non_trivial(first_param, second_param, select_entity);
            }
        }

        if (relation_name == "Uses") {

        }

        if (relation_name == "Parent") {

        }

        if (relation_name == "Modifies") {

        }
    }

    if (!pattern_clause.empty()) { // has pattern
        string pattern_type = pql_dto::Pattern::get_pattern_type();
        string first_param = pql_dto::Pattern::get_first_param();
        string second_param = pql_dto::Pattern::get_second_param();
        if (pattern_type == "assign") {
            pattern_list = {}; // get_stmt_list_matching_pattern(first_param, second_param);
        }
    }

    // Merge three lists
    result = QueryEvaluator::take_common_part(selectList, suchThatList, patternList);
    return result;
}

vector<string> QueryEvaluator::take_common_part(
        vector<string> select_list,
        vector<string> such_that_list,
        vector<string> pattern_list) {

}
