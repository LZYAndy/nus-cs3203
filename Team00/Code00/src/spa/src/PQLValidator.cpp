#include "PQLValidator.h"

std::string PQLValidator::pql_validate_initial_query(std::string query)
{
    std::string error;

    if (query.length() <= 0)
    {
        return "Invalid Query! Query does not exists.";
    }
    else if (query.find("Select") == std::string::npos)
    {
        return "Invalid Query! Missing Select Clause.";
    }
    else if (query.find("Select") == 0)
    {
        return "No Declarations.";
    }

    return error;
}

std::string PQLValidator::pql_validate_declaration_clause(std::string query)
{
    std::string error;

    return error;
}

std::string PQLValidator::pql_validate_select_clause(std::string query)
{
    std::string error;

    return error;
}

std::string PQLValidator::pql_validate_such_that_clause(std::string query)
{
    std::string error;

    return error;
}

std::string PQLValidator::pql_validate_pattern_clause(std::string query)
{
    std::string error;

    return error;
}
