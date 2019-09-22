#pragma once

#include <string>

namespace error_messages
{
    // Error messages for Parser
    constexpr const char* invalid_proc_name(R"(Invalid procedure name!)");
    constexpr const char* invalid_no_semicolon(R"(Invalid SIMPLE code. No semicolon!)");
    constexpr const char* invalid_if_statement(R"(Invalid if statement in the SIMPLE code.)");
    constexpr const char* invalid_while_statement(R"(Invalid while statement in the SIMPLE code.)");
    constexpr const char* invalid_call_statement(R"(Invalid call statement in the SIMPLE code.)");
    constexpr const char* invalid_call_type(R"(Invalid call type.)");
    constexpr const char* invalid_print_statement(R"(Invalid print statement in the SIMPLE code.)");
    constexpr const char* invalid_print_type(R"(Invalid print type.)");
    constexpr const char* invalid_assign_statement(R"(Invalid assign statement in the SIMPLE code.)");
    constexpr const char* invalid_assign_type(R"(Invalid assign type.)");
    constexpr const char* invalid_read_statement(R"(Invalid read statement in the SIMPLE code.)");
    constexpr const char* invalid_read_type(R"(Invalid read type.)");
    constexpr const char* invalid_SIMPLE(R"(Invalid SIMPLE code.)");

    // Error messages for Entity.cpp
    constexpr const char* invalid_entity_type(R"(Invalid Entity Type!)");
    constexpr const char* invalid_declared_entity_name(R"(Invalid Declared Entity Name!)");
    constexpr const char* invalid_pattern_expression_format(R"(Invalid Format For Pattern Expression!)");
    constexpr const char* invalid_synonym_name(R"(Invalid Synonym Name!)");
    constexpr const char* invalid_statement_number(R"(Invalid Statement Number Value!)");
    constexpr const char* invalid_constant_value(R"(Invalid Constant Value!)");
    constexpr const char* invalid_undeclared_entity_name(R"(Invalid Undeclared Entity Name!)");

    // Error messages for Relationships.cpp
    constexpr const char* invalid_follows_relationship_first_param(R"(Invalid Follows Relationship First Parameter Type!)");
    constexpr const char* invalid_follows_relationship_second_param(R"(Invalid Follows Relationship Second Parameter Type!)");
    constexpr const char* invalid_modifies_relationship_first_param(R"(Invalid Modifies Relationship First Parameter Type!)");
    constexpr const char* invalid_modifies_relationship_second_param(R"(Invalid Modifies Relationship Second Parameter Type!)");
    constexpr const char* invalid_parent_relationship_first_param(R"(Invalid Parent Relationship First Parameter Type!)");
    constexpr const char* invalid_parent_relationship_second_param(R"(Invalid Parent Relationship Second Parameter Type!)");
    constexpr const char* invalid_uses_relationship_first_param(R"(Invalid Uses Relationship First Parameter Type!)");
    constexpr const char* invalid_uses_relationship_second_param(R"(Invalid Uses Relationship Second Parameter Type!)");
    constexpr const char* invalid_order_of_params(R"(First param for Relationship is greater than the second param.)");

    // Error messages for Pattern.cpp
    constexpr const char* invalid_pattern_entity(R"(Invalid Pattern Entity Type!)");
    constexpr const char* invalid_pattern_first_param(R"(Invalid Pattern First Parameter Type!)");
    constexpr const char* invalid_pattern_second_param(R"(Invalid Pattern Second Parameter Type!)");

    // Error message for PQLParser.cpp
    constexpr const char* invalid_query_not_exists(R"(Invalid Query! Query does not exists.)");
    constexpr const char* invalid_query_missing_select(R"(Invalid Query! Missing Select Clause.)");
    constexpr const char* invalid_query_missing_declarations(R"(Invalid Query! Missing Declaration Clause.)");
    constexpr const char* invalid_query_declaration_clause_syntax(R"(Invalid Query! Missing Synonym.)");
    constexpr const char* invalid_query_declaration_duplicate_synonyms(R"(Invalid Query! Duplicate Synonyms for Entities in Declaration Clause.)");
    constexpr const char* invalid_query_select_clause_syntax(R"(Invalid Query! Select Clause Syntax Error.)");
    constexpr const char* invalid_query_variables_not_declared(R"(Invalid Query! No such Variable exists.)");
    constexpr const char* invalid_query_extra_string_end(R"(Invalid Syntax! Additional string after \"Select v\" with no conditions.)");
    constexpr const char* invalid_query_mismatch_brackets(R"(Invalid Syntax! Missing closing bracket.)");
    constexpr const char* invalid_query_such_that_clause_syntax(R"(Invalid Query! Such That Clause Syntax Error.)");
    constexpr const char* invalid_query_pattern_clause_syntax(R"(Invalid Query! Pattern Clause Syntax Error.)");
    constexpr const char* invalid_query_wrong_pattern_entity(R"(Invalid Syntax! Invalid Entity for pattern.)");
    constexpr const char* invalid_relationship_type(R"(Invalid Relationship Type!)");
}