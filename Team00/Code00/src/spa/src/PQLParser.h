#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <pql_dto\Entity.h>
#include <pql_dto\Relationships.h>
#include <pql_dto\Pattern.h>

void pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause, 
	vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause, vector<pql_dto::Pattern>& pattern_clause);