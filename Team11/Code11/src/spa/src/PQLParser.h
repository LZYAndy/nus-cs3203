#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class PQLParser
{
private:
    /**
     * Validates the inital query.
     * @param query The pointer to user's query statement.
     * @return The user's query string.
     */
    static std::string pql_validate_initial_query(std::string &query);

    /**
     * Creates the entity object for the clauses and relationships.
     * @param var_name The name of the entity.
     * @param declared_variables The pointer to the declared_variables map.
     * @param is_pattern_expr The boolean to check if its a pattern expression.
     * @return The Entity object that is initialised.
     */
    static pql_dto::Entity create_entity(std::string &var_name, std::unordered_map<std::string, std::string> &declared_variables,
                                         bool is_pattern_expr);

    /**
     * Creates the relationship object for the clauses.
     * @param relationship_type The type of the relationship.
     * @param first_param The first param entity of the relationship.
     * @param second_param The second param entity of the relationship.
     * @return The Relationship object that is initialised.
     */
    static pql_dto::Relationships create_relationship(std::string &relationship_type, pql_dto::Entity first_param,
            pql_dto::Entity second_param);

public:
    /**
     * Parses and validates the query. If validation succeeds, stores query in clause pointers.
     * @param query The user's query statement.
     * @param select_clause The pointer to the select clause vector.
     * @param such_that_clause The pointer to the such that clause vector.
     * @param pattern_clause The pointer to the pattern clause vector.
     * @return The error string if the query is invalid.
     */
    static std::string pql_parse_query(std::string query, std::vector<pql_dto::Entity> &select_clause,
            std::vector<pql_dto::Relationships> &such_that_clause, std::vector<pql_dto::Pattern> &pattern_clause);

    /**
     * Parses and validates the query. If validation succeeds, stores query in clause pointers.
     * @param query The user's query statement.
     * @param select_clause The pointer to the select clause map.
     * @param such_that_clause The pointer to the such that clause vector.
     * @param pattern_clause The pointer to the pattern clause vector.
     * @return The error string if the query is invalid.
     */
    static std::string pql_parse_query(std::string query, std::unordered_map<std::string, EntityType>& select_clause,
        std::vector<pql_dto::Relationships>& such_that_clause, std::vector<pql_dto::Pattern>& pattern_clause);

    /**
     * Parses and validates the declaration clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the user's query. String contains start of string to the last semi-colon.
     * @param declaration_clause The pointer to the declaration clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_declaration_clause(const std::string &query, std::unordered_map<std::string, std::string> &declared_variables);

    /**
     * Parses and validates the select clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the select query. String contains everything after the last semi-colon.
     * @param select_clause The pointer to the select clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @param condition_query The pointer to the string of condition in the param @query. The condition query is trimmed.
     * @return The error string if the query is invalid.
     */
    static std::string parse_select_clause(const std::string &query, std::vector<pql_dto::Entity> &select_clause,
                                           std::unordered_map<std::string, std::string> &declared_variables, std::string &condition_query);

    /**
     * Parses and validates the select clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the select query. String contains everything after the last semi-colon.
     * @param select_clause The pointer to the select clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @param condition_query The pointer to the string of condition in the param @query. The condition query is trimmed.
     * @return The error string if the query is invalid.
     */
    static std::string parse_select_clause(const std::string& query, std::unordered_map<std::string, EntityType>& select_clause,
        std::unordered_map<std::string, std::string>& declared_variables, std::string& condition_query);

    /**
     * Parses and validates the such that clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the such that query.
     * @param declaration_clause The pointer to the such that clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_such_that_clause(const std::string &query, std::vector<pql_dto::Relationships> &such_that_clause,
            std::unordered_map<std::string, std::string> &declared_variables);

    /**
     * Parses and validates the pattern clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the pattern query.
     * @param declaration_clause The pointer to the pattern clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_pattern_clause(const std::string &query, std::vector<pql_dto::Pattern> &pattern_clause,
                                            std::unordered_map<std::string, std::string> &declared_variables);
};
