#include <sstream>
#include <algorithm>
#include <StringUtil.cpp>

#include "PQLParser.h"
#include "StringUtil.h"
#include "PQLValidator.h"

#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"

std::string whitespace = " \n\t\r\f\v";

std::string PQLParser::pql_parse_query(std::string query, vector<pql_dto::Entity>& declaration_clause,
    vector<pql_dto::Entity>& select_clause, vector<pql_dto::Relationships>& such_that_clause,
    vector<pql_dto::Pattern>& pattern_clause)
{
    std::string error;
    std::unordered_map<string, string> declared_variables; // Maps variables' name to to entity type

    /// Validates if query meets the basic grammer of select-cl
    error = PQLValidator::pql_validate_initial_query(query);
    if (!error.empty())
    {
        return error;
    }

    /// Normalise the query for parsing
    query = StringUtil::replace_all_white_spaces(query);

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

    /// Checks if there are any conditions for query
    if (condition_query.empty())
    {
        return "";
    }
    
    size_t such_that_index = condition_query.find("such that ");
    size_t pattern_index = condition_query.find("pattern ");

    /// Checks if non-empty string has such that and pattern clause
    if (such_that_index == std::string::npos && pattern_index == std::string::npos)
    {
        return "Invalid Syntax! Additional string after \"Select v\" with no conditions.";
    }

    std::string such_that_query, pattern_query;
    size_t closing_bracket_index = condition_query.find_first_of(')');

    if (such_that_index == 0)
    {
        such_that_query = condition_query.substr(0, closing_bracket_index + 1);
        pattern_query = condition_query.substr(closing_bracket_index + 1);
    }
    else if (pattern_index == 0)
    {
        pattern_query = condition_query.substr(0, closing_bracket_index + 1);
        such_that_query = condition_query.substr(closing_bracket_index + 1);
    }
    else
    {
        return "Invalid Syntax! Missing closing bracket.";
    }

    /// Validates the such that string
    error = parse_such_that_clause(such_that_query, such_that_clause, declared_variables);
    if (!error.empty())
    {
        return error;
    }

    /// Validates the pattern string
    error = parse_pattern_clause(pattern_query, pattern_clause, declared_variables);
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
        std::string entity_type = declaration.substr(0, declaration.find_first_of(whitespace));
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
            if (declared_variables.find(name) != declared_variables.end())
            {
                return "Invalid Query! Duplicate Names for entities in Declaration Clause.";
            }
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
    int select_index = trimmed_query.find("Select ");
    if (select_index != 0)
    {
        return "Invalid query! Syntax Error.";
    }

    std::string select_query = StringUtil::trim(trimmed_query.substr(trimmed_query.find_first_of(whitespace)), whitespace);
    std::string select_variable = StringUtil::trim(trimmed_query.substr(0, select_query.find_first_of(whitespace)), whitespace);

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
    condition_query = StringUtil::trim(select_query.substr(select_query.find_first_of(whitespace)), whitespace);
    return "";
}

std::string PQLParser::parse_such_that_clause(const std::string& query, std::vector<pql_dto::Relationships>& such_that_clause,
    std::unordered_map<string, string>& declared_variables)
{
    /// Checks if query exists
    if (query.length() == 0)
    {
        return "";
    }

    std::string trimmed_query = StringUtil::trim(query, whitespace);
    if (trimmed_query.find("such that ") != 0)
    {
        return "Invalid Syntax! Such that clause syntax error.";
    }

    /// Get relationship query
    std::string relationship_query = trimmed_query.substr(10);
    size_t open_parentheses_index = relationship_query.find_first_of('(');
    size_t close_parentheses_index = relationship_query.find_first_of(')');

    if (open_parentheses_index != std::string::npos && close_parentheses_index != std::string::npos
        && open_parentheses_index < close_parentheses_index && relationship_query.back() == ')')
    {
        std::string relationship_type = StringUtil::trim(relationship_query.substr(0, open_parentheses_index), whitespace);
        std::string relationship_params = relationship_query.substr(open_parentheses_index);

        size_t comma_index = relationship_params.find_first_of(',');
        std::string first_param_string = StringUtil::trim(relationship_params.substr(1, comma_index - 1), whitespace);
        std::string second_param_string = StringUtil::trim(relationship_params.substr(comma_index + 1,
            relationship_params.length() - comma_index - 2), whitespace);

        try
        {
            pql_dto::Entity first_param = create_entity(first_param_string, declared_variables);
            pql_dto::Entity second_param = create_entity(second_param_string, declared_variables);
            pql_dto::Relationships& relationship = create_relationship(relationship_type, first_param, second_param);
            such_that_clause.push_back(relationship);
        }
        catch (std::exception& e)
        {
            return e.what();
        }
    }
    else
    {
        return "Invalid Relationship Format!";
    }

    return "";
}

std::string PQLParser::parse_pattern_clause(const std::string& query, std::vector<pql_dto::Pattern>& pattern_clause,
    std::unordered_map<string, string>& declared_variables)
{
    /// Checks if query exists
    if (query.length() == 0)
    {
        return "";
    }

    std::string trimmed_query = StringUtil::trim(query, whitespace);
    if (trimmed_query.find("pattern ") != 0)
    {
        return "Invalid Syntax! Pattern clause syntax error.";
    }

    /// Get pattern query
    std::string pattern_query = trimmed_query.substr(8);
    size_t open_parentheses_index = pattern_query.find_first_of('(');
    size_t close_parentheses_index = pattern_query.find_first_of(')');

    if (open_parentheses_index != std::string::npos && close_parentheses_index != std::string::npos
        && open_parentheses_index < close_parentheses_index && pattern_query.back() == ')')
    {
        /// Check if pattern has correct entity
        std::string entity_name = StringUtil::trim(pattern_query.substr(0, open_parentheses_index), whitespace);
        if (declared_variables.find(entity_name) == declared_variables.end() || declared_variables.at(entity_name) != "assign")
        {
            return "Invalid Syntax! Invalid Entity for pattern.";
        }

        std::string pattern_params = pattern_query.substr(open_parentheses_index);

        size_t comma_index = pattern_params.find_first_of(',');
        std::string first_param_string = StringUtil::trim(pattern_params.substr(1, comma_index - 1), whitespace);
        std::string second_param_string = StringUtil::trim(pattern_params.substr(comma_index + 1,
            pattern_params.length() - comma_index - 2), whitespace);

        try
        {
            pql_dto::Entity pattern_entity = pql_dto::Entity(entity_name, entity_name, true);
            pql_dto::Entity first_param = create_entity(first_param_string, declared_variables);
            pql_dto::Entity second_param = create_entity(second_param_string, declared_variables);
            pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param, second_param);
            pattern_clause.push_back(pattern);
        }
        catch (std::exception& e)
        {
            return e.what();
        }
    }
    else
    {
        return "Invalid Pattern Format!";
    }

    return "";
}

pql_dto::Entity PQLParser::create_entity(std::string& var_name, std::unordered_map<string, string>& declared_variables)
{
    pql_dto::Entity entity;

    if (var_name.find_first_of('"') == std::string::npos)
    {
        /// Checks if variable name is an INTEGER
        if (!var_name.empty() && std::all_of(var_name.begin(), var_name.end(), ::isdigit))
        {
            entity = pql_dto::Entity("stmt", var_name, false);
        }
        else if (var_name == "_")
        {
            entity = pql_dto::Entity("any", var_name, false);
        }
        else if (declared_variables.find(var_name) != declared_variables.end())
        {
            string entity_type = declared_variables.at(var_name);
            entity = pql_dto::Entity(entity_type, var_name, true);
        }
        else
        {
            throw std::runtime_error("No such variable exists!");
        }
    }
    else
    {
        if (var_name.front() == '"' && var_name.back() == '"' && var_name.length() != 1)
        {
            entity = pql_dto::Entity("string", var_name.substr(1, var_name.length() - 2), false);
        }
        else if (var_name.front() == '_' && var_name.back() == '_' && var_name.length() != 1)
        {
            entity = pql_dto::Entity("pattexpr", var_name, false);
        }
        else
        {
            throw std::runtime_error("Invalid Syntax! C");
        }
    }

    return entity;
}

pql_dto::Relationships PQLParser::create_relationship(std::string& relationship_type, pql_dto::Entity first_param, pql_dto::Entity second_param)
{
    if (relationship_type == "Follows")
    {
        return pql_dto::FollowsRelationship(first_param, second_param, false);
    }
    else if (relationship_type == "Follows*")
    {
        return pql_dto::FollowsRelationship(first_param, second_param, true);
    }
    else if (relationship_type == "Parent")
    {
        return pql_dto::ParentRelationship(first_param, second_param, false);
    }
    else if (relationship_type == "Parent*")
    {
        return pql_dto::ParentRelationship(first_param, second_param, true);
    }
    else if (relationship_type == "Uses")
    {
        return pql_dto::UsesRelationship(first_param, second_param, false);
    }
    else if (relationship_type == "Modifies")
    {
        return pql_dto::ModifiesRelationship(first_param, second_param, false);
    }
    else
    {
        throw std::runtime_error("Invalid name for relationship type!");
    }
}