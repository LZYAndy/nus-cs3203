#include <sstream>
#include <algorithm>
#include <StringUtil.cpp>

#include "PQLParser.h"
#include "StringUtil.h"
#include "PQLValidator.h"

std::string whitespace = " \f\n\r\t\v";

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

    /// Validates the declaration string
    size_t last_semi_colon = query.find_last_of(';');
    error = parse_declaration_clause(query.substr(0, last_semi_colon), declaration_clause, declared_variables);
    if (!error.empty())
    {
        return error;
    }

    /// Validates the select string
    std::string select_clause_query = query.substr(last_semi_colon + 1);
    std::string condition_query;

    error = parse_select_clause(select_clause_query, select_clause, declared_variables, condition_query);
    if (!error.empty())
    {
        return error;
    }

    return error;
}

std::string PQLParser::parse_declaration_clause(const std::string& query, std::vector<pql_dto::Entity>& declaration_clause,
    std::unordered_map<string, string>& declared_variables)
{
    std::vector<std::string> split_declaration_clause = StringUtil::split(query, ';');
    for (std::string declaration : split_declaration_clause)
    {
        /// Split declaration clause in the form "design-entity synonym (‘,’ synonym)*"
        declaration = StringUtil::trim(declaration, whitespace);
        std::string entity_type = declaration.substr(0, declaration.find_first_of(whitespace) - 1);
        std::string entity_names = declaration.substr(declaration.find_first_of(whitespace));
        std::vector<std::string> entity_names_list = StringUtil::split(entity_names, ',');

        if (entity_names_list.size() == 0)
        {
            return "Invalid Query! Missing synonym.";
        }

        for (string name : entity_names_list)
        {
            pql_dto::Entity entity;
            name = StringUtil::trim(name, whitespace);
            try
            {
                entity = pql_dto::Entity(entity_type, name, true);
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
    std::unordered_map<string, string>& declared_variables, std::string& condition_query)
{
    std::string trimmed_query = StringUtil::trim(query, whitespace);
    int select_index = trimmed_query.find("Select");
    if (select_index != 0)
    {
        return "Invalid query! Syntax Error.";
    }

    std::string select_query = StringUtil::trim(trimmed_query.substr(trimmed_query.find_first_of(whitespace)), whitespace);
    std::string select_variable = StringUtil::trim(trimmed_query.substr(select_query.find_first_of(whitespace)), whitespace);

    /// Checks if variable in select clause exists
    if (declared_variables.find(select_variable) == declared_variables.end())
    {
        return "No such variable exists!";
    }

    string entity_type = declared_variables.at(select_variable);
    try
    {
        pql_dto::Entity entity = pql_dto::Entity(entity_type, select_variable, true);
        select_clause.push_back(entity);
    }
    catch (const std::exception& e)
    {
        return e.what();
    }

    /// Sets the condition query after the select clause
    condition_query = select_query.substr(select_query.find_first_of(whitespace));
    return "";
}
