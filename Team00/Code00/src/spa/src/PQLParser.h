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
    /*!
    Parses and validates the declaration clause. If validation succeeds, stores query in clause pointers.
    @param query The declaration clause.
    @param declaration_clause The pointer to the declaration clause vector.
    @param declared_variables The pointer to the variables unordered map.
    */
    static std::string parse_declaration_clause(const std::string& query, std::vector<pql_dto::Entity>& declaration_clause,
        std::unordered_map<string, string>& declared_variables);

    /*!
    Parses and validates the declaration clause. If validation succeeds, stores query in clause pointers.
    @param query The declaration clause.
    @param declaration_clause The pointer to the declaration clause vector.
    @param declared_variables The pointer to the variables unordered map.
    */
    static std::string parse_select_clause(const std::string& query, std::vector<pql_dto::Entity>& select_clause,
        std::unordered_map<string, string>& declared_variables, std::string& condition_query);

    static std::string parse_such_that_clause(const std::string& query, std::vector<pql_dto::Relationships>& such_that_clause,
        std::unordered_map<string, string>& declared_variables);

    static std::string parse_pattern_clause(const std::string& query, std::vector<pql_dto::Pattern>& pattern_clause,
        std::unordered_map<string, string>& declared_variables);

    static pql_dto::Entity create_entity(std::string& var_name, std::unordered_map<string, string>& declared_variables);

    static pql_dto::Relationships create_relationship(std::string& relationship_type, pql_dto::Entity first_param, pql_dto::Entity second_param);

public:
    /*!
    Parses and validates the query. If validation succeeds, stores query in clause pointers.
    @param query The user's query statement.
    @param declaration_clause The pointer to the declaration clause vector.
    @param select_clause The pointer to the select clause vector.
    @param such_that_clause The pointer to the such that clause vector.
    @param pattern_clause The pointer to the pattern clause vector.
    */
    static std::string pql_parse_query(std::string query, std::vector<pql_dto::Entity>& declaration_clause,
        std::vector<pql_dto::Entity>& select_clause, std::vector<pql_dto::Relationships>& such_that_clause,
        std::vector<pql_dto::Pattern>& pattern_clause);
};
