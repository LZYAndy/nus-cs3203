#include "AffectsBipStarEvaluator.h"

unordered_map<string, vector<string>> AffectsBipStarEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> empty_map;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared())
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. AffectsBip*(a, _)
            vector<int> int_vec = PKB.get_all_assigns_affect_bip();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. AffectsBip*(a, 2)
            vector<int> int_vec = PKB.get_assigns_affect_bip_star(stoi(second_name));
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (first_param.equals(second_param))
        {
            // e.g. AffectsBip*(a, a)
            unordered_map<int, vector<int>> int_map = PKB.get_all_affects_bip_star_relationship();
            result = QueryUtility::mapping(first_param, second_param, first_name, second_name, int_map, PKB);
        }
        else
        {
            // e.g. AffectsBip*(a1, a2), where a1 could equal to a2
            unordered_map<int, vector<int>> int_map = PKB.get_all_affects_bip_star_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. AffectsBip*(_, a)
            vector<int> int_vec = PKB.get_all_assigns_affected_bip();
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(first_param))
        {
            // e.g. AffectsBip*(1, a)
            vector<int> int_vec = PKB.get_assigns_affected_bip_star_by(stoi(first_name));
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
    }
    return result;
}

bool AffectsBipStarEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. AffectsBip*(_, _)
            result = PKB.does_affects_bip_exist();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. AffectsBip*(_, 2)
            result = !PKB.get_assigns_affect_bip_star(stoi(second_name)).empty();
        }
    }

    if (QueryUtility::is_statement_num(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. AffectsBip*(1, _)
            result = !PKB.get_assigns_affected_bip_star_by(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. AffectsBip*(1, 2)
            result = PKB.is_affects_bip_star(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}
