#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>

/*!
Parses and validates the query. If validation succeeds, stores query in clause pointers.
@param query The user's query statement.
@param declaration_clause The pointer to the declaration clause vector.
@param select_clause The pointer to the select clause vector.
@param such_that_clause The pointer to the such that clause vector.
@param pattern_clause The pointer to the pattern clause vector.
*/
string pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause,
	vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause, vector<pql_dto::Pattern>& pattern_clause);