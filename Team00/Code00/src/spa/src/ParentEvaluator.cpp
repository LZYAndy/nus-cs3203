#include "ParentEvaluator.h"

unordered_map<string, vector<string>> ParentEvaluator::evaluate_non_trivial(pql_dto::Entity first_param,
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
        { // e.g. Parent(s, _)
            vector<int> int_vec = PKB.get_all_parent();
            result = QueryUtility::mapping(first_param, int_vec);
        }
        else if (QueryUtility::is_integer(second_name))
        { // e.g. Parent(s, 2)
            int first_stmt_num = PKB.get_parent(stoi(second_name));
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
        { // e.g. Parent(s, s)
            result[first_name] = empty_vec;
        }
        else
        { // e.g. Parent(s1, s2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_parent_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_name == "_")
        { // e.g. Parent(_, s)
            vector<int> int_vec = PKB.get_all_children();
            result = QueryUtility::mapping(second_param, int_vec);
        }
        else if (QueryUtility::is_integer(first_name))
        { // e.g. Parent(1, s)
            vector<int> int_vec = PKB.get_children(stoi(first_name));
            result = QueryUtility::mapping(second_param, int_vec);
        }
    }

    return result;
}

bool ParentEvaluator::evaluate_trivial(pql_dto::Entity first_param,
        pql_dto::Entity second_param)
{
    bool result = false;
    vector<string> empty_vec;
    PKB PKB;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_name == "_")
    {
        if (second_name == "_")
        { // e.g. Parent(_, _)
            result = PKB.does_parent_exist();
        }
        else if (QueryUtility::is_integer(second_name))
        { // e.g. Parent(_, 2)
            result = PKB.get_parent(stoi(second_name)) > 0;
        }
    }

    if (QueryUtility::is_integer(first_name))
    {
        if (second_name == "_")
        { // e.g. Parent(1, _)
            result = !PKB.get_children(stoi(first_name)).empty();
        }
        else if (QueryUtility::is_integer(second_name))
        { // e.g. Parent(1, 2)
            result = PKB.is_parent(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}
