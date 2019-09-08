#pragma once

#include <string>
#include <vector>

class PQLValidator
{
public:
    static std::string pql_validate_initial_query(std::string query);
    static std::string pql_validate_declaration_clause(std::string query);
    static std::string pql_validate_select_clause(std::string query);
    static std::string pql_validate_such_that_clause(std::string query);
    static std::string pql_validate_pattern_clause(std::string query);
};