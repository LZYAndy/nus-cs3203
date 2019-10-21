#pragma once

#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/With.h>

/// string constant for whitespace characters
const std::string whitespace = " \n\t\r\f\v";

/// string constant for select keywords
const std::string select_keyword = "Select";
const std::string select_keyword_with_space = "Select ";

/// string constant for relationship keywords
const std::string follows_keyword = "Follows";
const std::string follows_star_keyword = "Follows*";
const std::string parent_keyword = "Parent";
const std::string parent_star_keyword = "Parent*";
const std::string uses_keyword = "Uses";
const std::string modifies_keyword = "Modifies";
const std::string next_keyword = "Next";
const std::string next_star_keyword = "Next*";
const std::string calls_keyword = "Calls";
const std::string calls_star_keyword = "Calls*";
const std::string affects_keyword = "Affects";
const std::string affects_star_keyword = "Affects*";

/// string constant for clauses keywords
const std::string such_that_keyword = "such that ";
const std::string pattern_keyword = "pattern ";
const std::string with_keyword = "with ";
const std::string and_keyword = "and ";

class PQLParserHelper
{
private:
    /**
     * Creates the entity object from the given variable.
     * @param var_name The name of the entity.
     * @param declared_variables The pointer to the declared_variables map.
     * @return The Entity object that is initialised.
     */
    static pql_dto::Entity parse_variable_to_entity(std::string& var_name, std::unordered_map<std::string, std::string>& declared_variables);

    /**
     * Creates the entity object for the clauses and relationships.
     * @param var_name The name of the entity.
     * @param declared_variables The pointer to the declared_variables map.
     * @param is_pattern_expr The boolean to check if its a pattern expression.
     * @return The Entity object that is initialised.
     */
    static pql_dto::Entity create_entity(std::string& var_name, std::unordered_map<std::string, std::string>& declared_variables,
        bool is_pattern_expr);

    /**
     * Creates the entity object for the with clause.
     * @param var_name The name of the entity.
     * @param declared_variables The pointer to the declared_variables map.
     * @return The Entity object that is initialised.
     */
    static pql_dto::Entity create_with_entity(std::string& var_name, std::unordered_map<std::string, std::string>& declared_variables);

    /**
     * Creates the relationship object for the clauses.
     * @param relationship_type The type of the relationship.
     * @param first_param The first param entity of the relationship.
     * @param second_param The second param entity of the relationship.
     * @return The Relationship object that is initialised.
     */
    static pql_dto::Relationships create_relationship(std::string& relationship_type, pql_dto::Entity first_param,
        pql_dto::Entity second_param);

public:
    /**
     * Validates the inital query string.
     * @param query The pointer to user's query statement.
     * @return The user's query string.
     */
    static std::string pql_validate_initial_query(std::string& query);

    /**
     * Parses and validates the declaration clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the user's query. String contains start of string to the last semi-colon.
     * @param declaration_clause The pointer to the declaration clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_declaration_clause(const std::string& query, std::unordered_map<std::string, std::string>& declared_variables);

    /**
     * Parses and validates the select clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the select query. String contains everything after the last semi-colon.
     * @param select_clause The pointer to the select clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @param condition_query The pointer to the string of condition in the param @query. The condition query is trimmed.
     * @return The error string if the query is invalid.
     */
    static std::string parse_select_clause(const std::string& query, std::vector<pql_dto::Entity>& select_clause,
        std::unordered_map<std::string, std::string>& declared_variables, std::string& condition_query);

    /**
     * Parses and validates the such that clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the such that query.
     * @param declaration_clause The pointer to the such that clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_such_that_clause(const std::string& query, std::vector<pql_dto::Relationships>& such_that_clause,
        std::unordered_map<std::string, std::string>& declared_variables);

    /**
     * Parses and validates the pattern clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the pattern query.
     * @param declaration_clause The pointer to the pattern clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_pattern_clause(std::string& query, std::vector<pql_dto::Pattern>& pattern_clause,
        std::unordered_map<std::string, std::string>& declared_variables);

    /**
     * Parses and validates the with clause. If validation succeeds, stores query in clause pointers.
     * @param query The pointer to the with query.
     * @param declaration_clause The pointer to the with clause vector.
     * @param declared_variables The pointer to the variables unordered map.
     * @return The error string if the query is invalid.
     */
    static std::string parse_with_clause(std::string& query, std::vector<pql_dto::With>& with_clause,
        std::unordered_map<std::string, std::string>& declared_variables);
};
