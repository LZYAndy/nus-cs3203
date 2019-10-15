#pragma once

#include "PQLParserHelper.h"

class PQLParser
{
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
            std::vector<pql_dto::Relationships> &such_that_clause, std::vector<pql_dto::Pattern> &pattern_clause,
            std::vector<pql_dto::With>& with_clause);
};
