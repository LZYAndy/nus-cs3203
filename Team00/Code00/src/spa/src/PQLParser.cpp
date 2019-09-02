#include <sstream>

#include "PQLParser.h"
#include "PQLValidator.h"

std::string PQLParser::pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause,
	vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause, 
	vector<pql_dto::Pattern>& pattern_clause) 
{
	std::string error;

	// Validates if query meets the basic grammer of select-cl
	error = PQLValidator::pql_validate_initial_query(query);
	if (!error.empty())
	{
		return error;
	}

	// Validates the declaration string
	std::vector<std::string> split_declaration_query = split(query, "Select");
	error = PQLValidator::pql_validate_declaration_clause(split_declaration_query.front());
	if (!error.empty())
	{
		return error;
	}

}

std::vector<std::string> PQLParser::split(const std::string& query, std::string delimiter)
{
	std::vector<std::string> split_query;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;

	while ((pos_end = query.find(delimiter, pos_start)) != std::string::npos) 
	{
		token = query.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		split_query.push_back(token);
	}

	split_query.push_back(query.substr(pos_start));
	return split_query;
}

std::vector<std::string> PQLParser::split(const std::string& query, char delimiter)
{
	std::vector<std::string> split_query;
	std::istringstream iss(query);
	std::string token;

	while (std::getline(iss, token, delimiter))
	{
		split_query.push_back(token);
	}

	return split_query;
}
