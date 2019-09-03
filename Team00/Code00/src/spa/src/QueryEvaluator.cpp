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
    error_msg = PQLParser::pql_parse_query(query, declaration_clause, select_clause,
            such_that_clause, pattern_clause);
    if (error_msg.empty()) {
        return empty_vec;
    }

    pql_dto::Entity select_entity = select_clause.front();
    pql_dto::Relationships & relation = such_that_clause.front();
    pql_dto::Pattern pattern = pattern_clause.front();

    if (!select_clause.empty()) { // has select
        EntityType select_type = select_entity.get_entity_type();
        select_list = QueryUtility::get_certain_type_list(select_type);
    }

    if (!such_that_clause.empty()) { // has such that
        RelationshipType relation_type = relation.get_relationship();
        pql_dto::Entity first_param = relation.get_first_param();
        pql_dto::Entity second_param = relation.get_second_param();

        if (relation_type == RelationshipType::FOLLOWS) {
            if (!relation.is_relationship_star()) {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared()) {
                    such_that_list = FollowsEvaluator::evaluate_trivial(first_param, second_param, select_entity);
                } else {
                    such_that_list = FollowsEvaluator::evaluate_non_trivial(first_param, second_param, select_entity);
                }
            } else {
                if (!first_param.is_entity_declared() && !second_param.is_entity_declared()) {
                    such_that_list = FollowsStarEvaluator::evaluate_trivial(first_param, second_param, select_entity);
                } else {
                    such_that_list = FollowsStarEvaluator::evaluate_non_trivial(first_param, second_param, select_entity);
                }
            }

        }

        if (relation_type == RelationshipType::USES && !relation.is_relationship_star()) {
            if (!relation.is_relationship_star()) {

            } else {

            }
        }

        if (relation_type == RelationshipType::PARENT && !relation.is_relationship_star()) {
            if (!relation.is_relationship_star()) {

            } else {

            }
        }

        if (relation_type == RelationshipType::MODIFIES && !relation.is_relationship_star()) {
            if (!relation.is_relationship_star()) {

            } else {

            }
        }
    }

    if (!pattern_clause.empty()) { // has pattern
        EntityType pattern_type = pattern.get_pattern_entity().get_entity_type();
        pql_dto::Entity first_param = pattern.get_first_param();
        pql_dto::Entity second_param = pattern.get_second_param();
        if (pattern_type == EntityType::ASSIGN) {
            pattern_list = {}; // get_stmt_list_matching_pattern(first_param, second_param);
        }
    }

    // Merge three lists
    result = QueryEvaluator::take_common_part(select_list, such_that_list, pattern_list);
    return result;
}

vector<string> QueryEvaluator::take_common_part(
        vector<string> select_list,
        vector<string> such_that_list,
        vector<string> pattern_list) {
    vector<string> vector_1;
    vector<string> vector_2;
    set_intersection(select_list.begin(), select_list.end(), such_that_list.begin(),
            such_that_list.end(), back_inserter(vector_1));
    set_intersection(vector_1.begin(), vector_1.end(), pattern_list.begin(),
                     pattern_list.end(), back_inserter(vector_2));
    return vector_2;
}
