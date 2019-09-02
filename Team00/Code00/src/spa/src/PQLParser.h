#pragma once

#include <string>
#include <vector>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

class PQLParser
{
public:
	/*!
	Parses and validates the query. If validation succeeds, stores query in clause pointers.
	@param query The user's query statement.
	@param declaration_clause The pointer to the declaration clause vector.
	@param select_clause The pointer to the select clause vector.
	@param such_that_clause The pointer to the such that clause vector.
	@param pattern_clause The pointer to the pattern clause vector.
	*/
	static std::string pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause,
		vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause, vector<pql_dto::Pattern>& pattern_clause);

	/*!
	Splits the query using a string delimiter.
	@param query The query string to be split.
	@param delimiter The string that is used to split the query.
	@return The vector of string split by the delimiter.
	*/
	static std::vector<std::string> split(const std::string& query, std::string delimiter);

	/*!
	Splits the query using a char delimiter.
	@param query The query string to be split.
	@param delimiter The char that is used to split the query.
	@return The vector of string split by the delimiter.
	*/
	static std::vector<std::string> split(const std::string& query, char delimiter);
};
