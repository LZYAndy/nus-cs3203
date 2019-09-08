#include <sstream>

#include "PQLParser.h"
#include "PQLValidator.h"

std::string PQLParser::pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause,
    vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause, 
    vector<pql_dto::Pattern>& pattern_clause) 
{
    std::string error;
    std::unordered_map<string, string> declared_variables; // Maps variables' name to to entity type

    // Validates if query meets the basic grammer of select-cl
    error = PQLValidator::pql_validate_initial_query(query);
    if (!error.empty())
    {
        return error;
    }

    // Validates the declaration string
    std::vector<std::string> split_query_by_select = split(query, "Select");
    error = parse_declaration_clause(split_query_by_select.front(), declaration_clause, declared_variables);
    if (!error.empty())
    {
        return error;
    }

    // Validates the declaration string
    std::vector<std::string> split_query_by_such_that = split(query, "such that");
    std::vector<std::string> split_query_by_pattern = split(split_query_by_such_that.front(), "pattern");
    error = parse_select_clause(split_query_by_pattern.front(), select_clause, declared_variables);
    if (!error.empty())
    {
        return error;
    }

    return error;
}

std::string PQLParser::parse_declaration_clause(const std::string& query, std::vector<pql_dto::Entity>& declaration_clause, 
    std::unordered_map<string, string>& declared_variables)
{
    std::vector<std::string> split_declaration_clause = split(query, ';');
    for each (std::string declaration in split_declaration_clause)
    {
        // Split declaration clause in the form "design-entity synonym (�,� synonym)*"
        std::string entity_type = declaration.substr(0, declaration.find(' '));
        std::string entity_names = declaration.substr(declaration.find(' '), declaration.length());
        std::vector<std::string> entity_names_list = split(entity_names, ',');

        if (entity_names_list.size() == 0)
        {
            return "Invalid Query! Missing synonym.";
        }

        for each (string name in entity_names_list)
        {
            pql_dto::Entity entity;
            try 
            {
                entity = pql_dto::Entity(entity_type, name);
                declaration_clause.push_back(entity);
                declared_variables[name] = entity_type;
            }
            catch (const std::exception& e)
            {
                return e.what();
            }
        }
    }

    return "";
}

std::string PQLParser::parse_select_clause(const std::string& query, std::vector<pql_dto::Entity>& select_clause,
    std::unordered_map<string, string>& declared_variables)
{
    // Checks if variable in select clause exists
    if (declared_variables.find(query) == declared_variables.end())
    {
        return "No such variable exists!";
    }

    string entity_type = declared_variables.at(query);
    pql_dto::Entity entity = pql_dto::Entity(entity_type, query);
    select_clause.push_back(entity);

    return "";
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
