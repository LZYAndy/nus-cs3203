#include <sstream>
#include <algorithm>

#include "PQLParser.h"
#include "StringUtil.h"
#include "ErrorMessages.h"

#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"
#include "pql_dto/NextRelationship.cpp"
#include "pql_dto/CallsRelationship.cpp"
#include "pql_dto/AffectsRelationship.cpp"

/// string constant for whitespace characters
const std::string whitespace = " \n\t\r\f\v";

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

std::string PQLParser::pql_parse_query(std::string query, std::vector<pql_dto::Entity> &select_clause,
        std::vector<pql_dto::Relationships> &such_that_clause, std::vector<pql_dto::Pattern> &pattern_clause,
        std::vector<pql_dto::With> &with_clause)
{
    std::string error;
    std::unordered_map<std::string, std::string> declared_variables; // Maps variables' name to to entity type

    /// Validates if query meets the basic grammer of select-cl
    error = pql_validate_initial_query(query);
    if (!error.empty())
    {
        return error;
    }

    /// Normalise the query for parsing
    query = StringUtil::replace_all_white_spaces(query);

    /// Validates the declaration string
    size_t last_semi_colon = query.find_last_of(';');
    error = parse_declaration_clause(query.substr(0, last_semi_colon), declared_variables);
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


    while (!condition_query.empty())
    {
        /// Find first occurence of such that
        size_t such_that_index = condition_query.find(such_that_keyword);
        if (such_that_index == 0)
        {
            size_t closing_bracket_index = condition_query.find_first_of(')');
            if (closing_bracket_index == std::string::npos)
            {
                return error_messages::invalid_query_mismatch_brackets;
            }

            std::string such_that_query = condition_query.substr(0, closing_bracket_index + 1);
            /// Validates the such that string
            error = parse_such_that_clause(such_that_query, such_that_clause, declared_variables);
            if (!error.empty())
            {
                return error;
            }

            condition_query = StringUtil::trim(condition_query.substr(closing_bracket_index + 1), whitespace);
            while (!condition_query.empty())
            {
                size_t and_index = condition_query.find(and_keyword);
                if (and_index != 0)
                {
                    break;
                }

                size_t closing_bracket_index = condition_query.find_first_of(')');
                if (closing_bracket_index == std::string::npos)
                {
                    return error_messages::invalid_query_mismatch_brackets;
                }

                std::string such_that_query = condition_query.substr(0, closing_bracket_index + 1);
                /// Validates the such that string
                error = parse_such_that_clause(such_that_query, such_that_clause, declared_variables);
                if (!error.empty())
                {
                    return error;
                }

                condition_query = StringUtil::trim(condition_query.substr(closing_bracket_index + 1), whitespace);
            }
            continue;
        }

        /// Find first occurence of such that
        size_t pattern_index = condition_query.find(pattern_keyword);
        if (pattern_index == 0)
        {
            size_t closing_bracket_index = condition_query.find_first_of(')');
            if (closing_bracket_index == std::string::npos)
            {
                return error_messages::invalid_query_mismatch_brackets;
            }

            std::string pattern_query = condition_query.substr(0, closing_bracket_index + 1);
            /// Validates the pattern string
            error = parse_pattern_clause(pattern_query, pattern_clause, declared_variables);
            if (!error.empty())
            {
                return error;
            }

            condition_query = StringUtil::trim(condition_query.substr(closing_bracket_index + 1), whitespace);
            while (!condition_query.empty())
            {
                size_t and_index = condition_query.find(and_keyword);
                if (and_index != 0)
                {
                    break;
                }

                size_t closing_bracket_index = condition_query.find_first_of(')');
                if (closing_bracket_index == std::string::npos)
                {
                    return error_messages::invalid_query_mismatch_brackets;
                }

                std::string pattern_query = condition_query.substr(0, closing_bracket_index + 1);
                /// Validates the pattern string
                error = parse_pattern_clause(pattern_query, pattern_clause, declared_variables);
                if (!error.empty())
                {
                    return error;
                }

                condition_query = StringUtil::trim(condition_query.substr(closing_bracket_index + 1), whitespace);
            }

            continue;
        }

        /// Find first occurence of such that
        size_t with_index = condition_query.find(with_keyword);
        if (with_index == 0)
        {

            continue;
        }

        /// if condition does not start with clauses keywords
        return error_messages::invalid_query_extra_string_end;
    }

   /* size_t such_that_index = condition_query.find("such that ");
    size_t pattern_index = condition_query.find("pattern ");

    /// Checks if non-empty string has such that and pattern clause
    if (such_that_index == std::string::npos && pattern_index == std::string::npos)
    {
        return error_messages::invalid_query_extra_string_end;
    }

    std::string such_that_query, pattern_query;
    size_t closing_bracket_index = condition_query.find_first_of(')');

    if (closing_bracket_index == std::string::npos)
    {
        return error_messages::invalid_query_mismatch_brackets;
    }

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
        return error_messages::invalid_query_select_clause_syntax;
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
    }*/

    return "";
}

std::string PQLParser::parse_declaration_clause(const std::string &query, std::unordered_map<std::string, std::string> &declared_variables)
{
    std::vector<std::string> split_declaration_clause = StringUtil::split(query, ';');

    for (std::string declaration : split_declaration_clause)
    {
        /// Split declaration clause in the form "design-entity synonym (‘,’ synonym)*"
        declaration = StringUtil::trim(declaration, whitespace);
        size_t whitespace_index = declaration.find_first_of(whitespace);
        if (whitespace_index == std::string::npos)
        {
            return error_messages::invalid_query_declaration_clause_syntax;
        }

        std::string entity_type = declaration.substr(0, whitespace_index);
        std::string entity_names = declaration.substr(whitespace_index);
        std::vector<std::string> entity_names_list = StringUtil::split(entity_names, ',');

        if (entity_names_list.empty())
        {
            return error_messages::invalid_query_declaration_clause_syntax;
        }

        for (std::string name : entity_names_list)
        {
            pql_dto::Entity entity;
            name = StringUtil::trim(name, whitespace);
            if (declared_variables.find(name) != declared_variables.end())
            {
                return error_messages::invalid_query_declaration_duplicate_synonyms;
            }
            try
            {
                entity = pql_dto::Entity(entity_type, name, true);
                declared_variables[name] = entity_type;
            }
            catch (const std::exception &e)
            {
                return e.what();
            }
        }
    }

    return "";
}

std::string PQLParser::parse_select_clause(const std::string &query, std::vector<pql_dto::Entity> &select_clause,
        std::unordered_map<std::string, std::string> &declared_variables, std::string &condition_query)
{
    std::string trimmed_query = StringUtil::trim(query, whitespace);
    int select_index = trimmed_query.find("Select ");
    if (select_index != 0)
    {
        return error_messages::invalid_query_select_clause_syntax;
    }

    std::string select_query = StringUtil::trim(trimmed_query.substr(trimmed_query.find_first_of(whitespace)), whitespace);
    std::string select_variable;
    if (select_query.front() == '<')
    {
        /// Checks if select variable is a tuple
        if (select_query.find_first_of('>') != std::string::npos)
        {
            std::string variables_string = select_query.substr(1, select_query.find_first_of('>') - 1);
            std::vector<std::string> variables_vector = StringUtil::split(variables_string, ',');

            for (std::string var : variables_vector)
            {
                var = StringUtil::trim(var, whitespace);
                std::vector<std::string> variable_attr;

                /// If select variable has a attribute
                if (var.find_first_of('.') != std::string::npos)
                {
                    variable_attr = StringUtil::split(var, '.');
                    if (variable_attr.size() != 2)
                    {
                        return error_messages::invalid_query_select_attr_syntax;
                    }
                    try
                    {
                        add_variable_with_attr_to_select_clause(declared_variables, variable_attr, select_clause);
                    }
                    catch (std::exception& e)
                    {
                        return e.what();
                    }
                }
                else
                {
                    try
                    {
                        add_variable_to_select_clause(declared_variables, var, select_clause);
                    }
                    catch (std::exception& e)
                    {
                        return e.what();
                    }
                }
            }
        }
        else
        {
            return error_messages::invalid_query_select_clause_syntax;
        }

        /// Sets the condition query after the select clause
        if (select_query.back() != '>')
        {
            condition_query = StringUtil::trim(select_query.substr(select_query.find_first_of('>') + 1), whitespace);
        }
    }
    else
    {
        select_variable = StringUtil::trim(select_query.substr(0, select_query.find_first_of(whitespace)), whitespace);

        /// Sets the condition query after the select clause
        if (select_query.find_first_of(whitespace) != std::string::npos)
        {
            std::string remaining_select_query = StringUtil::trim(select_query.substr(select_query.find_first_of(whitespace)), whitespace);
            if (select_variable.back() == '.')
            {
                std::string var_attr = StringUtil::trim(remaining_select_query.substr(0, select_query.find_first_of(whitespace)), whitespace);
                
                select_variable.append(var_attr);
                select_query = remaining_select_query;
            }
            else if (remaining_select_query.front() == '.')
            {
                remaining_select_query = StringUtil::trim(remaining_select_query.substr(remaining_select_query.find_first_of(whitespace)), whitespace);
                std::string var_attr = StringUtil::trim(remaining_select_query.substr(0, remaining_select_query.find_first_of(whitespace)), whitespace);
                
                select_variable.append(".");
                select_variable.append(var_attr);
                select_query = remaining_select_query;
            }
            
        }

        /// If select variable has a attribute
        if (select_variable.find_first_of('.') != std::string::npos)
        {
            std::vector<std::string> variable_attr = StringUtil::split(select_variable, '.');
            if (variable_attr.size() != 2)
            {
                return error_messages::invalid_query_select_attr_syntax;
            }
            try
            {
                add_variable_with_attr_to_select_clause(declared_variables, variable_attr, select_clause);
            }
            catch (std::exception& e)
            {
                return e.what();
            }
        }
        else
        {
            /// Checks if select variable is BOOLEAN
            if (select_variable == "BOOLEAN")
            {
                pql_dto::Entity entity = pql_dto::Entity("boolean", select_variable, false);
                select_clause.push_back(entity);
            }
            else
            {
                try
                {
                    add_variable_to_select_clause(declared_variables, select_variable, select_clause);
                }
                catch (std::exception& e)
                {
                    return e.what();
                }
            }
        }

        /// Sets the condition query after the select clause
        if (select_query.find_first_of(whitespace) != std::string::npos)
        {
            condition_query = StringUtil::trim(select_query.substr(select_query.find_first_of(whitespace)), whitespace);
        }
    }

    return "";
}

void PQLParser::add_variable_with_attr_to_select_clause(std::unordered_map<std::string, std::string>& declared_variables,
    std::vector<std::string>& select_variable, std::vector<pql_dto::Entity>& select_clause)
{
    std::string var_name = StringUtil::trim(select_variable.front(), whitespace);
    std::string var_attr = StringUtil::trim(select_variable.back(), whitespace);

    /// Checks if variable in select clause exists
    if (declared_variables.find(var_name) == declared_variables.end())
    {
        throw std::runtime_error(error_messages::invalid_query_variables_not_declared);
    }

    std::string entity_type = declared_variables.at(var_name);
    pql_dto::Entity entity = pql_dto::Entity(entity_type, var_name, true);
    entity.set_entity_attr(var_attr);
    select_clause.push_back(entity);
}

void PQLParser::add_variable_to_select_clause(std::unordered_map<std::string, std::string>& declared_variables,
    std::string& select_variable, std::vector<pql_dto::Entity>& select_clause)
{
    /// Checks if variable in select clause exists
    if (declared_variables.find(select_variable) == declared_variables.end())
    {
        throw std::runtime_error(error_messages::invalid_query_variables_not_declared);
    }

    std::string entity_type = declared_variables.at(select_variable);
    pql_dto::Entity entity = pql_dto::Entity(entity_type, select_variable, true);
    select_clause.push_back(entity);
}

std::string PQLParser::parse_such_that_clause(const std::string &query, std::vector<pql_dto::Relationships> &such_that_clause,
        std::unordered_map<std::string, std::string> &declared_variables)
{
    /// Checks if query exists
    if (query.length() == 0)
    {
        return "";
    }

    /// std::string trimmed_query = StringUtil::trim(query, whitespace);
    if (query.find(such_that_keyword) != 0 && query.find(and_keyword) != 0)
    {
        return error_messages::invalid_query_such_that_clause_syntax;
    }

    /// Get relationship query
    std::string relationship_query;
    if (query.find(such_that_keyword) == 0)
    {
        relationship_query = query.substr(10);
    }
    else
    {
        relationship_query = query.substr(4);
    }
    
    size_t open_parentheses_index = relationship_query.find_first_of('(');
    size_t close_parentheses_index = relationship_query.find_first_of(')');

    if (open_parentheses_index != std::string::npos && close_parentheses_index != std::string::npos
            && open_parentheses_index < close_parentheses_index && relationship_query.back() == ')')
    {
        std::string relationship_type = StringUtil::trim(relationship_query.substr(0, open_parentheses_index), whitespace);
        std::string relationship_params = relationship_query.substr(open_parentheses_index);

        size_t comma_index = relationship_params.find_first_of(',');
        if (comma_index == std::string::npos)
        {
            return error_messages::invalid_query_such_that_clause_syntax;
        }
        std::string first_param_string = StringUtil::trim(relationship_params.substr(1, comma_index - 1), whitespace);
        std::string second_param_string = StringUtil::trim(relationship_params.substr(comma_index + 1,
                                          relationship_params.length() - comma_index - 2), whitespace);

        try
        {
            pql_dto::Entity first_param = create_entity(first_param_string, declared_variables, false);
            pql_dto::Entity second_param = create_entity(second_param_string, declared_variables, false);
            pql_dto::Relationships relationship = create_relationship(relationship_type, first_param, second_param);
            such_that_clause.push_back(relationship);
        }
        catch (std::exception &e)
        {
            return e.what();
        }
    }
    else
    {
        return error_messages::invalid_query_such_that_clause_syntax;
    }

    return "";
}

std::string PQLParser::parse_pattern_clause(const std::string &query, std::vector<pql_dto::Pattern> &pattern_clause,
        std::unordered_map<std::string, std::string> &declared_variables)
{
    /// Checks if query exists
    if (query.length() == 0)
    {
        return "";
    }

    /*std::string trimmed_query = StringUtil::trim(query, whitespace);*/
    if (query.find(pattern_keyword) != 0 && query.find(and_keyword) != 0)
    {
        return error_messages::invalid_query_pattern_clause_syntax;
    }

    /// Get pattern query
    std::string pattern_query;
    if (query.find(pattern_keyword) == 0)
    {
        pattern_query = query.substr(8);
    }
    else
    {
        pattern_query = query.substr(4);
    }
    
    size_t open_parentheses_index = pattern_query.find_first_of('(');
    size_t close_parentheses_index = pattern_query.find_first_of(')');

    if (open_parentheses_index != std::string::npos && close_parentheses_index != std::string::npos
            && open_parentheses_index < close_parentheses_index && pattern_query.back() == ')')
    {
        /// Check if pattern has correct entity
        std::string entity_name = StringUtil::trim(pattern_query.substr(0, open_parentheses_index), whitespace);
        if (declared_variables.find(entity_name) == declared_variables.end() || (declared_variables.at(entity_name) != "assign"
            && declared_variables.at(entity_name) != "while" && declared_variables.at(entity_name) != "if"))
        {
            return error_messages::invalid_query_wrong_pattern_entity;
        }

        std::string pattern_params = pattern_query.substr(open_parentheses_index);

        size_t comma_index = pattern_params.find_first_of(',');
        if (comma_index == std::string::npos)
        {
            return error_messages::invalid_query_pattern_clause_syntax;
        }

        std::string first_param_string = StringUtil::trim(pattern_params.substr(1, comma_index - 1), whitespace);

        try
        {
            pql_dto::Entity pattern_entity = pql_dto::Entity(declared_variables.at(entity_name), entity_name, true);
            if (pattern_entity.get_entity_type() == EntityType::ASSIGN || pattern_entity.get_entity_type() == EntityType::WHILE)
            {
                std::string second_param_string = StringUtil::trim(pattern_params.substr(comma_index + 1,
                    pattern_params.length() - comma_index - 2), whitespace);
                pql_dto::Entity first_param = create_entity(first_param_string, declared_variables, false);
                pql_dto::Entity second_param = create_entity(second_param_string, declared_variables, true);
                pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param, second_param);
                pattern_clause.push_back(pattern);
            }
            else if (pattern_entity.get_entity_type() == EntityType::IF)
            {
                std::string second_and_third_params = StringUtil::trim(pattern_params.substr(comma_index + 1,
                    pattern_params.length() - comma_index - 2), whitespace);
                
                size_t second_comma_index = second_and_third_params.find_first_of(',');
                if (second_comma_index == std::string::npos)
                {
                    return error_messages::invalid_query_pattern_clause_syntax;
                }

                std::string second_param_string = StringUtil::trim(second_and_third_params.substr(0, second_comma_index), whitespace);
                std::string third_param_string = StringUtil::trim(second_and_third_params.substr(second_comma_index + 1), whitespace);

                pql_dto::Entity first_param = create_entity(first_param_string, declared_variables, false);
                pql_dto::Entity second_param = create_entity(second_param_string, declared_variables, false);
                pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param, second_param);
                pattern_clause.push_back(pattern);
            }
            
        }
        catch (std::exception &e)
        {
            return e.what();
        }
    }
    else
    {
        return error_messages::invalid_query_pattern_clause_syntax;
    }

    return "";
}

std::string PQLParser::pql_validate_initial_query(std::string &query)
{
    std::string error;

    if (query.length() == 0)
    {
        return error_messages::invalid_query_not_exists;
    }
    else if (query.find("Select") == std::string::npos)
    {
        return error_messages::invalid_query_missing_select;
    }
    else if (query.find("Select") == 0)
    {
        return error_messages::invalid_query_missing_declarations;
    }

    return error;
}

pql_dto::Entity PQLParser::create_entity(std::string &var_name, std::unordered_map<std::string, std::string> &declared_variables,
        bool is_pattern_expr)
{
    pql_dto::Entity entity;

    /// Checks if variable is enclosed in ""
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
            std::string entity_type = declared_variables.at(var_name);
            entity = pql_dto::Entity(entity_type, var_name, true);
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_declared_entity_name);
        }
    }
    else
    {
        if (var_name.front() == '"' && var_name.back() == '"' && var_name.length() > 2)
        {
            if (is_pattern_expr)
            {
                entity = pql_dto::Entity("matchexpr", StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace), false);
            }
            else
            {
                std::string var_value = StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace);
                entity = pql_dto::Entity("variable", var_value, false);
            }
        }
        else if (var_name.front() == '_' && var_name.back() == '_' && var_name.length() != 1)
        {
            std::string string_value = StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace);
            if (string_value.front() == '"' && string_value.back() == '"' && string_value.length() > 2)
            {
                entity = pql_dto::Entity("pattexpr", StringUtil::trim(string_value.substr(1, string_value.length() - 2), whitespace), false);
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
            }
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
        }
    }

    return entity;
}

pql_dto::Relationships PQLParser::create_relationship(std::string &relationship_type, pql_dto::Entity first_param, pql_dto::Entity second_param)
{
    if (relationship_type == follows_keyword)
    {
        return pql_dto::FollowsRelationship(first_param, second_param, false);
    }
    else if (relationship_type.find(follows_keyword) != std::string::npos)
    {
        relationship_type = StringUtil::remove_all_white_spaces(relationship_type);
        if (relationship_type != follows_star_keyword)
        {
            throw std::runtime_error(error_messages::invalid_relationship_type);
        }
        return pql_dto::FollowsRelationship(first_param, second_param, true);
    }
    
    if (relationship_type == parent_keyword)
    {
        return pql_dto::ParentRelationship(first_param, second_param, false);
    }
    else if (relationship_type.find(parent_keyword) != std::string::npos)
    {
        relationship_type = StringUtil::remove_all_white_spaces(relationship_type);
        if (relationship_type != parent_star_keyword)
        {
            throw std::runtime_error(error_messages::invalid_relationship_type);
        }
        return pql_dto::ParentRelationship(first_param, second_param, true);
    }
    
    if (relationship_type == next_keyword)
    {
        return pql_dto::NextRelationship(first_param, second_param, false);
    }
    else if (relationship_type.find(next_keyword) != std::string::npos)
    {
        relationship_type = StringUtil::remove_all_white_spaces(relationship_type);
        if (relationship_type != next_star_keyword)
        {
            throw std::runtime_error(error_messages::invalid_relationship_type);
        }
        return pql_dto::NextRelationship(first_param, second_param, true);
    }
    
    if (relationship_type == calls_keyword)
    {
        return pql_dto::CallsRelationship(first_param, second_param, false);
    }
    else if (relationship_type.find(calls_keyword) != std::string::npos)
    {
        relationship_type = StringUtil::remove_all_white_spaces(relationship_type);
        if (relationship_type != calls_star_keyword)
        {
            throw std::runtime_error(error_messages::invalid_relationship_type);
        }
        return pql_dto::CallsRelationship(first_param, second_param, true);
    }
    
    if (relationship_type == affects_keyword)
    {
        return pql_dto::AffectsRelationship(first_param, second_param, false);
    }
    else if (relationship_type.find(affects_keyword) != std::string::npos)
    {
        relationship_type = StringUtil::remove_all_white_spaces(relationship_type);
        if (relationship_type != affects_star_keyword)
        {
            throw std::runtime_error(error_messages::invalid_relationship_type);
        }
        return pql_dto::AffectsRelationship(first_param, second_param, true);
    }
    
    if (relationship_type == uses_keyword)
    {
        return pql_dto::UsesRelationship(first_param, second_param, false);
    }
    
    if (relationship_type == modifies_keyword)
    {
        return pql_dto::ModifiesRelationship(first_param, second_param, false);
    }

    throw std::runtime_error(error_messages::invalid_relationship_type);
}
