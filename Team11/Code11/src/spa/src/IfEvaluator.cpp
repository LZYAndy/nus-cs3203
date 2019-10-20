#include "IfEvaluator.h"

unordered_map<string, vector<string>> IfEvaluator::evaluate(pql_dto::Pattern &pattern,
        pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    pql_dto::Entity pattern_entity = pattern.get_pattern_entity();
    string pattern_name = pattern_entity.get_entity_name();
    string first_name = first_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    { // pattern ifs(_, _, _)
        vector<int> int_vec = PKB.get_all_ifs();
        result = QueryUtility::mapping(pattern_name, int_vec);
    }
    else if (QueryUtility::is_var_name(first_param))
    { // pattern ifs("x", _, _)
        vector<int> int_vec = PKB.get_all_if_pattern_contains(first_name);
        result = QueryUtility::mapping(pattern_name, int_vec);
    }
    else
    { // pattern ifs(v, _, _)
        unordered_map<int, vector<string>> int_str_map = PKB.get_all_if_and_control_variables_map();
        result = QueryUtility::mapping(pattern_entity, first_param, int_str_map, PKB);
    }
    return result;
}