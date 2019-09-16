#include "FollowsEvaluator.h"

unordered_map<string, vector<string>> FollowsEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    unordered_map<string, vector<string>> result;
    vector<string> empty_vec;
    PKB PKB;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared())
    {
        if (second_name == "_")
        { // e.g. Follows(s, _)
            vector<int> int_vec = PKB.get_all_followed();
            result = QueryUtility::mapping(first_param, int_vec);
        }
        else if (CheckerUtil::is_const_valid(second_name))
        { // e.g. Follows(s, 2)
            int first_stmt_num = PKB.get_followed_by(stoi(second_name));
            if (first_stmt_num > 0)
            {
                result = QueryUtility::mapping(first_param, first_stmt_num);
            }
            else
            {
                result[first_name] = empty_vec;
            }
        }
        else if (first_name == second_name)
        { // e.g. Follows(s, s)
            result[first_name] = empty_vec;
        }
        else
        { // e.g. Follows(s1, s2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_follows_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_name == "_")
        { // e.g. Follows(_, s)
            vector<int> int_vec = PKB.get_all_follows();
            result = QueryUtility::mapping(second_param, int_vec);
        }
        else if (CheckerUtil::is_const_valid(first_name))
        { // e.g. Follows(1, s)
            int second_stmt_num = PKB.get_follows(stoi(first_name));
            if (second_stmt_num > 0)
            {
                result = QueryUtility::mapping(second_param, second_stmt_num);
            }
            else
            {
                result[second_name] = empty_vec;
            }
        }
    }

    return result;
}

bool FollowsEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    bool result = false;
    PKB PKB;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_name == "_")
    {
        if (second_name == "_")
        { // e.g. Follows(_, _)
            result = PKB.does_follows_exist();
        }
        else if (CheckerUtil::is_const_valid(second_name))
        { // e.g. Follows(_, 2)
            result = PKB.get_followed_by(stoi(second_name)) > 0;
        }
    }

    if (CheckerUtil::is_const_valid(first_name))
    {
        if (second_name == "_")
        { // e.g. Follows(1, _)
            result = PKB.get_follows(stoi(first_name)) > 0;
        }
        else if (CheckerUtil::is_const_valid(second_name))
        { // e.g. Follows(1, 2)
            result = PKB.is_follows(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}