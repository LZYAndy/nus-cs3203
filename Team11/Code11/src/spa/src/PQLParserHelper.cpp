#include "PQLParserHelper.h"
#include "StringUtil.h"
#include "ErrorMessages.h"

#include "pql_dto/UsesRelationship.cpp"
#include "pql_dto/ModifiesRelationship.cpp"
#include "pql_dto/ParentRelationship.cpp"
#include "pql_dto/FollowsRelationship.cpp"
#include "pql_dto/NextRelationship.cpp"
#include "pql_dto/CallsRelationship.cpp"
#include "pql_dto/AffectsRelationship.cpp"

std::string PQLParserHelper::pql_validate_initial_query(std::string& query)
{
    if (query.length() == 0)
    {
        return error_messages::invalid_query_not_exists;
    }
    else if (query.find(select_keyword) == std::string::npos)
    {
        return error_messages::invalid_query_missing_select;
    }

    return "";
}

std::string PQLParserHelper::parse_declaration_clause(const std::string& query, std::unordered_map<std::string, std::string>& declared_variables)
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
            name = StringUtil::trim(name, whitespace);
            if (declared_variables.find(name) != declared_variables.end())
            {
                return error_messages::invalid_query_declaration_duplicate_synonyms;
            }
            try
            {
                pql_dto::Entity entity = pql_dto::Entity(entity_type, name, true);
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

std::string PQLParserHelper::parse_select_clause(const std::string& query, std::vector<pql_dto::Entity>& select_clause,
    std::unordered_map<std::string, std::string>& declared_variables, std::string& condition_query)
{
    std::string trimmed_query = StringUtil::trim(query, whitespace);
    int select_index = trimmed_query.find(select_keyword_with_space);
    if (select_index != 0)
    {
        return error_messages::invalid_query_select_clause_syntax;
    }

    // Remove Select keyword from the query
    std::string select_query = StringUtil::trim(trimmed_query.substr(7), whitespace);
    std::string select_variable;

    /// Checks if select variable is a tuple
    if (select_query.front() == '<')
    {
        if (select_query.find_first_of('>') != std::string::npos)
        {
            std::string variables_string = select_query.substr(1, select_query.find_first_of('>') - 1);
            std::vector<std::string> variables_vector = StringUtil::split(variables_string, ',');

            for (std::string var : variables_vector)
            {
                var = StringUtil::trim(var, whitespace);
                try
                {
                    pql_dto::Entity entity = parse_variable_to_entity(var, declared_variables);
                    select_clause.push_back(entity);
                }
                catch (std::exception& e)
                {
                    return e.what();
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

        /// Sets the attribute value to the select variable if exists.
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
                pql_dto::Entity entity = parse_variable_to_entity(select_variable, declared_variables);
                select_clause.push_back(entity);
            }
            catch (std::exception& e)
            {
                return e.what();
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

std::string PQLParserHelper::parse_such_that_clause(const std::string& query, std::vector<pql_dto::Relationships>& such_that_clause,
    std::unordered_map<std::string, std::string>& declared_variables)
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
        catch (std::exception& e)
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

std::string PQLParserHelper::parse_pattern_clause(std::string& query, std::vector<pql_dto::Pattern>& pattern_clause,
    std::unordered_map<std::string, std::string>& declared_variables)
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
                std::string remaining_query = StringUtil::trim(pattern_params.substr(comma_index + 1), whitespace);
                std::string second_param_string;
                size_t start_underscore_index = remaining_query.find_first_of('_');

                if (remaining_query.find_first_of('"') == 0)
                {
                    size_t closing_expr_index = remaining_query.find('"', 1);
                    if (closing_expr_index == std::string::npos)
                    {
                        return error_messages::invalid_query_pattern_clause_syntax;
                    }

                    second_param_string = StringUtil::trim(remaining_query.substr(0, closing_expr_index + 1), whitespace);
                    remaining_query = StringUtil::trim(remaining_query.substr(closing_expr_index + 1), whitespace);
                }
                else if (start_underscore_index == 0)
                {
                    std::string check_query = StringUtil::trim(remaining_query.substr(1), whitespace);
                    if (check_query.find_first_of('"') == 0)
                    {
                        size_t closing_underscore_index = remaining_query.find('_', 1);
                        if (closing_underscore_index == std::string::npos)
                        {
                            return error_messages::invalid_query_pattern_clause_syntax;
                        }

                        second_param_string = StringUtil::trim(remaining_query.substr(0, closing_underscore_index + 1), whitespace);
                        remaining_query = StringUtil::trim(remaining_query.substr(closing_underscore_index + 1), whitespace);
                    }
                    else
                    {
                        size_t closing_bracket_index = remaining_query.find(')', 1);
                        if (closing_bracket_index == std::string::npos)
                        {
                            return error_messages::invalid_query_pattern_clause_syntax;
                        }

                        second_param_string = StringUtil::trim(remaining_query.substr(0, closing_bracket_index), whitespace);
                        remaining_query = StringUtil::trim(remaining_query.substr(closing_bracket_index), whitespace);
                    }
                }
                else
                {
                    size_t closing_bracket_index = remaining_query.find(')', 1);
                    if (closing_bracket_index == std::string::npos)
                    {
                        return error_messages::invalid_query_pattern_clause_syntax;
                    }

                    second_param_string = StringUtil::trim(remaining_query.substr(0, closing_bracket_index), whitespace);
                    remaining_query = StringUtil::trim(remaining_query.substr(closing_bracket_index), whitespace);
                }

                pql_dto::Entity first_param = create_entity(first_param_string, declared_variables, false);
                pql_dto::Entity second_param = create_entity(second_param_string, declared_variables, true);
                pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param, second_param);
                pattern_clause.push_back(pattern);

                query = StringUtil::trim(remaining_query.substr(1), whitespace);
            }
            else if (pattern_entity.get_entity_type() == EntityType::IF)
            {
                size_t closing_bracket_index = pattern_params.find(')');
                std::string second_and_third_params = StringUtil::trim(pattern_params.substr(comma_index + 1,
                    closing_bracket_index - comma_index - 1), whitespace);

                size_t second_comma_index = second_and_third_params.find_first_of(',');
                if (second_comma_index == std::string::npos)
                {
                    return error_messages::invalid_query_pattern_clause_syntax;
                }

                std::string second_param_string = StringUtil::trim(second_and_third_params.substr(0, second_comma_index), whitespace);
                std::string third_param_string = StringUtil::trim(second_and_third_params.substr(second_comma_index + 1), whitespace);
                if (second_param_string != "_" || third_param_string != "_")
                {
                    return error_messages::invalid_query_pattern_clause_syntax;
                }

                pql_dto::Entity first_param = create_entity(first_param_string, declared_variables, false);
                pql_dto::Entity second_param = create_entity(second_param_string, declared_variables, false);
                pql_dto::Pattern pattern = pql_dto::Pattern(pattern_entity, first_param, second_param);
                pattern_clause.push_back(pattern);

                query = StringUtil::trim(pattern_params.substr(closing_bracket_index + 1), whitespace);
            }

        }
        catch (std::exception& e)
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

std::string PQLParserHelper::parse_with_clause(std::string& query, std::vector<pql_dto::With>& with_clause,
    std::unordered_map<std::string, std::string>& declared_variables)
{
    /// Checks if query exists
    if (query.length() == 0)
    {
        return "";
    }

    if (query.find(with_keyword) != 0 && query.find(and_keyword) != 0)
    {
        return error_messages::invalid_query_with_clause_syntax;
    }

    /// Get with query
    std::string with_query;
    if (query.find(with_keyword) == 0)
    {
        with_query = query.substr(5);
    }
    else
    {
        with_query = query.substr(4);
    }

    size_t equal_index = with_query.find_first_of('=');
    if (equal_index == std::string::npos)
    {
        return error_messages::invalid_query_missing_equal_with_clause;
    }

    std::string left_reference = StringUtil::trim(with_query.substr(0, equal_index), whitespace);
    query = StringUtil::trim(with_query.substr(equal_index + 1), whitespace);

    std::string right_reference = StringUtil::trim(query.substr(0, query.find_first_of(whitespace)), whitespace);

    /// Sets the attribute value to the with variable if exists.
    if (query.find_first_of(whitespace) != std::string::npos)
    {
        std::string remaining_condition_query = StringUtil::trim(query.substr(query.find_first_of(whitespace)), whitespace);
        if (right_reference.back() == '.')
        {
            std::string var_attr = StringUtil::trim(remaining_condition_query.substr(0, query.find_first_of(whitespace)), whitespace);

            right_reference.append(var_attr);
        }
        else if (remaining_condition_query.front() == '.')
        {
            remaining_condition_query = StringUtil::trim(remaining_condition_query.substr(remaining_condition_query.find_first_of(whitespace)), whitespace);
            std::string var_attr = StringUtil::trim(remaining_condition_query.substr(0, remaining_condition_query.find_first_of(whitespace)), whitespace);

            right_reference.append(".");
            right_reference.append(var_attr);
        }

        query = remaining_condition_query;
    }
    else
    {
        // end of query
        query = "";
    }
    
    try
    {
        pql_dto::Entity left_entity = create_with_entity(left_reference, declared_variables);
        pql_dto::Entity right_entity = create_with_entity(right_reference, declared_variables);
        pql_dto::With with = pql_dto::With(left_entity, right_entity);
        with_clause.push_back(with);
    }
    catch (std::exception& e)
    {
        return e.what();
    }

    return "";
}

pql_dto::Entity PQLParserHelper::parse_variable_to_entity(std::string& var, std::unordered_map<std::string, std::string>& declared_variables)
{
    /// If variable has a attribute
    if (var.find_first_of('.') != std::string::npos)
    {
        std::vector<std::string> variable_attr = StringUtil::split(var, '.');
        if (variable_attr.size() != 2)
        {
            throw std::runtime_error(error_messages::invalid_query_select_attr_syntax);
        }

        std::string var_name = StringUtil::trim(variable_attr.front(), whitespace);
        std::string var_attr = StringUtil::trim(variable_attr.back(), whitespace);

        /// Checks if variable in select clause exists
        if (declared_variables.find(var_name) == declared_variables.end())
        {
            throw std::runtime_error(error_messages::invalid_query_variables_not_declared);
        }

        std::string entity_type = declared_variables.at(var_name);
        pql_dto::Entity entity = pql_dto::Entity(entity_type, var_name, true);
        entity.set_entity_attr(var_attr);

        return entity;
    }
    else
    {
        /// Checks if variable in select clause exists
        if (declared_variables.find(var) == declared_variables.end())
        {
            throw std::runtime_error(error_messages::invalid_query_variables_not_declared);
        }

        std::string entity_type = declared_variables.at(var);

        return pql_dto::Entity(entity_type, var, true);
    }
}

pql_dto::Entity PQLParserHelper::create_entity(std::string& var_name, std::unordered_map<std::string, std::string>& declared_variables,
    bool is_pattern_expr)
{
    /// Checks if variable is enclosed in ""
    if (var_name.find_first_of('"') == std::string::npos)
    {
        /// Checks if variable name is an INTEGER
        if (!var_name.empty() && std::all_of(var_name.begin(), var_name.end(), ::isdigit))
        {
            return pql_dto::Entity("stmt", var_name, false);
        }
        
        if (var_name == "_")
        {
            return pql_dto::Entity("any", var_name, false);
        }
        
        if (declared_variables.find(var_name) != declared_variables.end())
        {
            std::string entity_type = declared_variables.at(var_name);
            return pql_dto::Entity(entity_type, var_name, true);
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
                return pql_dto::Entity("matchexpr", StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace), false);
            }
            std::string var_value = StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace);
            return pql_dto::Entity("variable", var_value, false);
        }
        
        if (var_name.front() == '_' && var_name.back() == '_' && var_name.length() != 1)
        {
            std::string string_value = StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace);
            if (string_value.front() == '"' && string_value.back() == '"' && string_value.length() > 2)
            {
                return pql_dto::Entity("pattexpr", StringUtil::trim(string_value.substr(1, string_value.length() - 2), whitespace), false);
            }
        }
        throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
    }
}

pql_dto::Entity PQLParserHelper::create_with_entity(std::string& var_name, std::unordered_map<std::string, std::string>& declared_variables)
{
    pql_dto::Entity entity;

    /// if variable is not enclosed in ""
    if (var_name.find_first_of('"') == std::string::npos)
    {
        /// Checks if variable name is an INTEGER
        if (!var_name.empty() && std::all_of(var_name.begin(), var_name.end(), ::isdigit))
        {
            return pql_dto::Entity("prog_line", var_name, false);
        }

        return parse_variable_to_entity(var_name, declared_variables);
    }

    if (var_name.front() == '"' && var_name.back() == '"' && var_name.length() > 2)
    {
        std::string var_value = StringUtil::trim(var_name.substr(1, var_name.length() - 2), whitespace);
        return pql_dto::Entity("variable", var_value, false);
    }

    throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
}

pql_dto::Relationships PQLParserHelper::create_relationship(std::string& relationship_type, pql_dto::Entity first_param, pql_dto::Entity second_param)
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
