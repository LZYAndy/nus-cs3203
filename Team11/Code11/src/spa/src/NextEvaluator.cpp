//#include "NextEvaluator.h"
//
//unordered_map<string, vector<string>> NextEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
//        pql_dto::Entity &second_param, PKB &PKB)
//{
//    unordered_map<string, vector<string>> result;
//    unordered_map<string, vector<string>> empty_map;
//    string first_name = first_param.get_entity_name();
//    string second_name = second_param.get_entity_name();
//
//    if (first_param.is_entity_declared())
//    {
//        if (second_param.get_entity_type() == EntityType::ANY)
//        {
//            // e.g. Next(n, _)
//            vector<int> int_vec = PKB.get_all_previous();
//            result = QueryUtility::mapping(first_param, int_vec, PKB);
//        }
//        else if (QueryUtility::is_program_line(second_param))
//        {
//            // e.g. Next(n, 2)
//            vector<int> int_vec = PKB.get_statements_previous(stoi(second_name));
//            result = QueryUtility::mapping(first_param, int_vec, PKB)
//        }
//        else if (first_param.equals(second_param))
//        {
//            // e.g. Next(n, n)
//            return empty_map;
//        }
//        else
//        {
//            // e.g. Next(n1, n2)
//            unordered_map<int, vector<int>> int_map = PKB.get_all_next_relationship();
//            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
//        }
//    }
//
//    if (second_param.is_entity_declared())
//    {
//        if (first_param.get_entity_type() == EntityType::ANY)
//        {
//            // e.g. Next(_, n)
//            vector<int> int_vec = PKB.get_all_next();
//            result = QueryUtility::mapping(second_param, int_vec, PKB);
//        }
//        else if (QueryUtility::is_program_line(first_param))
//        {
//            // e.g. Next(1, n)
//            vector<int> int_vec = PKB.get_statements_next(stoi(first_name));
//            result = QueryUtility::mapping(second_param, int_vec, PKB);
//        }
//    }
//    return result;
//}
//
//bool NextEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
//        pql_dto::Entity &second_param, PKB &PKB)
//{
//    bool result = false;
//    string first_name = first_param.get_entity_name();
//    string second_name = second_param.get_entity_name();
//
//    if (first_param.get_entity_type() == EntityType::ANY)
//    {
//        if (second_param.get_entity_type() == EntityType::ANY)
//        {
//            // e.g. Next(_, _)
//            result = PKB.does_next_exist();
//        }
//        else if (QueryUtility::is_program_line(second_param))
//        {
//            // e.g. Next(_, 2)
//            result = !PKB.get_statements_previous(stoi(second_name)).empty();
//        }
//    }
//
//    if (QueryUtility::is_program_line(first_param))
//    {
//        if (second_param.get_entity_type() == EntityType::ANY)
//        {
//            // e.g. Next(1, _)
//            result = !PKB.get_statements_next(stoi(first_name)).empty();
//        }
//        else if (QueryUtility::is_program_line(second_param))
//        {
//            // e.g. Next(1, 2)
//            result = PKB.is_next(stoi(first_name), stoi(second_name));
//        }
//    }
//    return result;
//}
