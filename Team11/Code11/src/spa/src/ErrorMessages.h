#pragma once

#include <string>

namespace error_messages
{
// Error messgage for TestWrapper.cpp
constexpr const char* invalid_file(R"(File not found!)");

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
constexpr const char* invalid_expr(R"(Invalid expression!)");
constexpr const char* invalid_SIMPLE(R"(Invalid SIMPLE code.)");
constexpr const char* cyclic_call(R"(Invalid SIMPLE code, contains cyclic calls.)");
constexpr const char* call_does_not_exist(R"(Invalid SIMPLE code, contains call statement calling to a non-exist procedure.)");


// Error messages for Entity.cpp
constexpr const char* invalid_entity_type(R"(Syntax Error: Invalid Entity Type!)");
constexpr const char* invalid_entity_attr(R"(Syntax Error: Invalid Entity Attribute!)");
constexpr const char* invalid_entity_attr_to_type(R"(Semantic Error: Invalid Entity Attribute To EntityType!)");
constexpr const char* invalid_declared_entity_name(R"(Syntax Error: Invalid Declared Entity Name!)");
constexpr const char* invalid_pattern_expression_format(R"(Syntax Error: Invalid Format For Pattern Expression!)");
constexpr const char* invalid_synonym_name(R"(Syntax Error: Invalid Synonym Name!)");
constexpr const char* invalid_statement_number(R"(Syntax Error: Invalid Statement Number Value!)");
constexpr const char* invalid_undeclared_entity_name(R"(Syntax Error: Invalid Undeclared Entity Name!)");

// Error messages for Relationships.cpp
constexpr const char* invalid_follows_relationship_first_param(R"(Semantic Error: Invalid Follows Relationship First Parameter Type!)");
constexpr const char* invalid_follows_relationship_second_param(R"(Semantic Error: Invalid Follows Relationship Second Parameter Type!)");
constexpr const char* invalid_follows_relationship_first_param_syntax(R"(Syntax Error: Invalid Follows Relationship First Parameter Type!)");
constexpr const char* invalid_follows_relationship_second_param_syntax(R"(Syntax Error: Invalid Follows Relationship Second Parameter Type!)");
constexpr const char* invalid_modifies_relationship_first_param(R"(Semantic Error: Invalid Modifies Relationship First Parameter Type!)");
constexpr const char* invalid_modifies_relationship_second_param(R"(Semantic Error: Invalid Modifies Relationship Second Parameter Type!)");
constexpr const char* invalid_modifies_relationship_first_param_syntax(R"(Syntax Error: Invalid Modifies Relationship First Parameter Type!)");
constexpr const char* invalid_modifies_relationship_second_param_syntax(R"(Syntax Error: Invalid Modifies Relationship Second Parameter Type!)");
constexpr const char* invalid_parent_relationship_first_param(R"(Semantic Error: Invalid Parent Relationship First Parameter Type!)");
constexpr const char* invalid_parent_relationship_second_param(R"(Semantic Error: Invalid Parent Relationship Second Parameter Type!)");
constexpr const char* invalid_parent_relationship_first_param_syntax(R"(Syntax Error: Invalid Parent Relationship First Parameter Type!)");
constexpr const char* invalid_parent_relationship_second_param_syntax(R"(Syntax Error: Invalid Parent Relationship Second Parameter Type!)");
constexpr const char* invalid_uses_relationship_first_param(R"(Semantic Error: Invalid Uses Relationship First Parameter Type!)");
constexpr const char* invalid_uses_relationship_second_param(R"(Semantic Error: Invalid Uses Relationship Second Parameter Type!)");
constexpr const char* invalid_uses_relationship_first_param_syntax(R"(Syntax Error: Invalid Uses Relationship First Parameter Type!)");
constexpr const char* invalid_uses_relationship_second_param_syntax(R"(Syntax Error: Invalid Uses Relationship Second Parameter Type!)");
constexpr const char* invalid_calls_relationship_first_param(R"(Semantic Error: Invalid Calls Relationship First Parameter Type!)");
constexpr const char* invalid_calls_relationship_second_param(R"(Semantic Error: Invalid Calls Relationship Second Parameter Type!)");
constexpr const char* invalid_calls_relationship_first_param_syntax(R"(Syntax Error: Invalid Calls Relationship First Parameter Type!)");
constexpr const char* invalid_calls_relationship_second_param_syntax(R"(Syntax Error: Invalid Calls Relationship Second Parameter Type!)");
constexpr const char* invalid_next_relationship_first_param(R"(Semantic Error: Invalid Next Relationship First Parameter Type!)");
constexpr const char* invalid_next_relationship_second_param(R"(Semantic Error: Invalid Next Relationship Second Parameter Type!)");
constexpr const char* invalid_next_relationship_first_param_syntax(R"(Syntax Error: Invalid Next Relationship First Parameter Type!)");
constexpr const char* invalid_next_relationship_second_param_syntax(R"(Syntax Error: Invalid Next Relationship Second Parameter Type!)");
constexpr const char* invalid_affects_relationship_first_param(R"(Semantic Error: Invalid Affects Relationship First Parameter Type!)");
constexpr const char* invalid_affects_relationship_second_param(R"(Semantic Error: Invalid Affects Relationship Second Parameter Type!)");
constexpr const char* invalid_affects_relationship_first_param_syntax(R"(Syntax Error: Invalid Affects Relationship First Parameter Type!)");
constexpr const char* invalid_affects_relationship_second_param_syntax(R"(Syntax Error: Invalid Affects Relationship Second Parameter Type!)");
constexpr const char* invalid_next_bip_relationship_first_param(R"(Semantic Error: Invalid NextBip Relationship First Parameter Type!)");
constexpr const char* invalid_next_bip_relationship_second_param(R"(Semantic Error: Invalid NextBip Relationship Second Parameter Type!)");
constexpr const char* invalid_next_bip_relationship_first_param_syntax(R"(Syntax Error: Invalid NextBip Relationship First Parameter Type!)");
constexpr const char* invalid_next_bip_relationship_second_param_syntax(R"(Syntax Error: Invalid NextBip Relationship Second Parameter Type!)");
constexpr const char* invalid_affects_bip_relationship_first_param(R"(Semantic Error: Invalid AffectsBip Relationship First Parameter Type!)");
constexpr const char* invalid_affects_bip_relationship_second_param(R"(Semantic Error: Invalid AffectsBip Relationship Second Parameter Type!)");
constexpr const char* invalid_affects_bip_relationship_first_param_syntax(R"(Syntax Error: Invalid AffectsBip Relationship First Parameter Type!)");
constexpr const char* invalid_affects_bip_relationship_second_param_syntax(R"(Syntax Error: Invalid AffectsBip Relationship Second Parameter Type!)");
constexpr const char* invalid_order_of_params(R"(Semantic Error: First param for Relationship is greater than the second param.)");

// Error messages for Pattern.cpp
constexpr const char* invalid_pattern_entity(R"(Semantic Error: Invalid Pattern Entity Type!)");
constexpr const char* invalid_pattern_first_param(R"(Semantic Error: Invalid Pattern First Parameter Type!)");
constexpr const char* invalid_pattern_second_param(R"(Semantic Error: Invalid Pattern Second Parameter Type!)");
constexpr const char* invalid_pattern_entity_syntax(R"(Syntax Error: Invalid Pattern Entity Type!)");
constexpr const char* invalid_pattern_first_param_syntax(R"(Syntax Error: Invalid Pattern First Parameter Type!)");
constexpr const char* invalid_pattern_second_param_syntax(R"(Syntax Error: Invalid Pattern Second Parameter Type!)");
constexpr const char* not_a_pattern_object(R"(Not a Pattern Object!)");

// Error messages for With.cpp
constexpr const char* invalid_with_first_param(R"(Semantic Error: Invalid With First Parameter Type!)");
constexpr const char* invalid_with_second_param(R"(Semantic Error: Invalid With Second Parameter Type!)");
constexpr const char* invalid_with_param(R"(Semantic Error: Invalid With Parameter!)");
constexpr const char* invalid_with_mismatch_type(R"(Semantic Error: Invalid With Mismatch Type!)");
constexpr const char* with_trivial_false(R"(Semantic Error: Different string/integer for With!)");

// Error message for PQLParser.cpp
constexpr const char* invalid_query_not_exists(R"(Syntax Error: Invalid Query! Query does not exists.)");
constexpr const char* invalid_query_missing_select(R"(Syntax Error: Invalid Query! Missing Select Clause.)");
constexpr const char* invalid_query_declaration_clause_syntax(R"(Syntax Error: Invalid Query! Missing Synonym.)");
constexpr const char* invalid_query_declaration_duplicate_synonyms(R"(Semantic Error: Invalid Query! Duplicate Synonyms for Entities in Declaration Clause.)");
constexpr const char* invalid_query_select_clause_syntax(R"(Syntax Error: Invalid Query! Select Clause Syntax Error.)");
constexpr const char* invalid_query_select_attr_syntax(R"(Syntax Error: Invalid Query! Variables has two or more '.'.)");
constexpr const char* invalid_query_variables_not_declared(R"(Semantic Error: Invalid Query! No such Variable exists.)");
constexpr const char* invalid_query_extra_string_end(R"(Syntax Error: Invalid Syntax! Additional string after \"Select v\" with no conditions.)");
constexpr const char* invalid_query_mismatch_brackets(R"(Syntax Error: Invalid Syntax! Missing closing bracket.)");
constexpr const char* invalid_query_such_that_clause_syntax(R"(Syntax Error: Invalid Query! Such That Clause Syntax Error.)");
constexpr const char* invalid_query_pattern_clause_syntax(R"(Syntax Error: Invalid Query! Pattern Clause Syntax Error.)");
constexpr const char* invalid_query_with_clause_syntax(R"(Syntax Error: Invalid Query! With Clause Syntax Error.)");
constexpr const char* invalid_query_wrong_pattern_entity(R"(Semantic Error: Invalid Entity for pattern.)");
constexpr const char* invalid_relationship_type(R"(Syntax Error: Invalid Relationship Type!)");
constexpr const char* invalid_query_missing_equal_with_clause(R"(Syntax Error: Invalid Query! Missing equal in with clause.)");
constexpr const char* invalid_attribute_syntax(R"(Syntax Error: Invalid Query! Attribute Syntax Error.)");
}
