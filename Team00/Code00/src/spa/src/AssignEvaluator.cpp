#include "AssignEvaluator.h"

unordered_map<string, vector<string>> AssignEvaluator::evaluate(pql_dto::Pattern pattern,
        pql_dto::Entity first_param, pql_dto::Entity second_param)
{
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    string pattern_name = pattern.get_pattern_entity().get_entity_name();
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_name == "_")
    {
        if (first_name == "_")
        { // e.g. pattern a(_, _)
            result = QueryUtility::mapping(pattern_name, PKB::get_all_assigns());
        }
        else if (QueryUtility::is_var_name(first_param))
        { // e.g. pattern a("y", _)
            result = QueryUtility::mapping(pattern_name, first_name, PKB::get_all_assigns())
        }
        else
        { // e.g. pattern a(v, _)
            result = QueryUtility::mapping(pattern_name, first_param, PKB::get_all_assigns())
        }
    }
    else if (second_param.get_entity_type() == EntityType::PATTEXPR)
    {
        if (first_name == "_")
        { // e.g. pattern a(_, _"x"_)
            result = QueryUtility::mapping(pattern_name, PKB::get_all_assign_pattern_contains(second_name));
        }
        else if (QueryUtility::is_var_name(first_param))
        { // e.g. pattern a("y", _"x"_)
            result = QueryUtility::mapping(pattern_name, PKB::get_assign_pattern_contains(first_name, second_name));
        }
        else
        { // e.g. pattern a(v, _"x"_)
            result = QueryUtility::mapping(pattern_name, first_param, PKB::get_all_assign_pattern_contains(second_name));
        }
    }
    else
    {
        if (first_name == "_")
        { // e.g. pattern a(_, "x")
            result = QueryUtility::mapping(pattern_name, PKB::get_all_assign_pattern_matches(second_name));
        }
        else if (QueryUtility::is_var_name(first_param))
        { // e.g. pattern a("y", "x")
            result = QueryUtility::mapping(pattern_name, PKB::get_assign_pattern_matches(first_name, second_name));
        }
        else
        { // e.g. pattern a(v, "x")
            result = QueryUtility::mapping(pattern_name, first_param, PKB::get_all_assign_pattern_matches(second_name));
        }
    }

    return result;
}
