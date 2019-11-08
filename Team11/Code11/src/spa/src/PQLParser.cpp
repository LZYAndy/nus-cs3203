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

std::string PQLParser::pql_parse_query(std::string query, std::vector<pql_dto::Entity> &select_clause,
        std::vector<pql_dto::Relationships> &such_that_clause, std::vector<pql_dto::Pattern> &pattern_clause,
        std::vector<pql_dto::With> &with_clause)
{
    std::string error;
    std::unordered_map<std::string, std::string> declared_variables; // Maps variables' name to entity type

    /// Validates if query meets the basic grammer of select-cl
    error = PQLParserHelper::pql_validate_initial_query(query);
    if (!error.empty())
    {
        return error;
    }

    /// Normalise the query for parsing
    query = StringUtil::replace_all_white_spaces(query);

    /// Validates the declaration string
    size_t last_semi_colon = query.find_last_of(';');
    if (last_semi_colon != std::string::npos)
    {
        error = PQLParserHelper::parse_declaration_clause(query.substr(0, last_semi_colon), declared_variables);
        if (!error.empty())
        {
            // Checks if Select clause is BOOLEAN
            if (error.find("Semantic Error:") != std::string::npos)
            {
                std::string select_clause_string = StringUtil::trim(query.substr(last_semi_colon + 1), whitespace);
                if (select_clause_string.find("Select BOOLEAN") == 0)
                {
                    pql_dto::Entity entity = pql_dto::Entity(boolean_keyword, "BOOLEAN", false);
                    select_clause.push_back(entity);
                }
            }
            return error;
        }
    }

    /// Validates the select string
    std::string select_clause_query = query.substr(last_semi_colon + 1);
    std::string condition_query;
    error = PQLParserHelper::parse_select_clause(select_clause_query, select_clause, declared_variables, condition_query);
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
            error = PQLParserHelper::parse_such_that_clause(such_that_query, such_that_clause, declared_variables);
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
                error = PQLParserHelper::parse_such_that_clause(such_that_query, such_that_clause, declared_variables);
                if (!error.empty())
                {
                    return error;
                }

                condition_query = StringUtil::trim(condition_query.substr(closing_bracket_index + 1), whitespace);
            }
            continue;
        }

        /// Find first occurence of pattern
        size_t pattern_index = condition_query.find(pattern_keyword);
        if (pattern_index == 0)
        {
            size_t closing_bracket_index = condition_query.find_first_of(')');
            if (closing_bracket_index == std::string::npos)
            {
                return error_messages::invalid_query_mismatch_brackets;
            }

            /// Validates the pattern string
            error = PQLParserHelper::parse_pattern_clause(condition_query, pattern_clause, declared_variables);
            if (!error.empty())
            {
                return error;
            }

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

                /// Validates the pattern string
                error = PQLParserHelper::parse_pattern_clause(condition_query, pattern_clause, declared_variables);
                if (!error.empty())
                {
                    return error;
                }
            }

            continue;
        }

        /// Find first occurence of with
        size_t with_index = condition_query.find(with_keyword);
        if (with_index == 0)
        {
            error = PQLParserHelper::parse_with_clause(condition_query, with_clause, declared_variables);
            if (!error.empty())
            {
                return error;
            }

            while (!condition_query.empty())
            {
                size_t and_index = condition_query.find(and_keyword);
                if (and_index != 0)
                {
                    break;
                }

                error = PQLParserHelper::parse_with_clause(condition_query, with_clause, declared_variables);
                if (!error.empty())
                {
                    return error;
                }
            }

            continue;
        }

        /// if condition does not start with clauses keywords
        return error_messages::invalid_query_extra_string_end;
    }

    return "";
}
