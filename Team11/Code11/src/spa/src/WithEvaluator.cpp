#include "WithEvaluator.h"

unordered_map<string, vector<string>> WithEvaluator::evaluate(pql_dto::Entity &first_param,
        pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    EntityType first_type = first_param.get_entity_type();
    EntityType second_type = second_param.get_entity_type();
    vector<string> str_vec_1;
    vector<string> str_vec_2;
    vector<string> temp_vec_1;
    vector<string> temp_vec_2;
    vector<string> result_vec_1;
    vector<string> result_vec_2;

//    if (QueryUtility::is_program_line(first_param) || QueryUtility::is_statement_num(first_param))
//    { // e.g. with 10 = s.stmt#
//        str_vec_1 = QueryUtility::get_certain_type_int_list(second_type, PKB);
//        temp_vec_1 = QueryUtility::change_to_attributes(second_param, str_vec_1, PKB);
//        int i = 0;
//        for (auto iter : temp_vec_1)
//        {
//            if (iter == first_param.get_entity_name())
//            {
//                result_vec_1.push_back(str_vec_1[i]);
//            }
//            i++;
//        }
//        result[second_param.get_entity_name()] = result_vec_1;
//    }
//    else if (QueryUtility::is_program_line(second_param) || QueryUtility::is_statement_num(second_param))
//    { // e.g. with s.stmt# = 10
//        str_vec_1 = QueryUtility::get_certain_type_int_list(first_type, PKB);
//        temp_vec_1 = QueryUtility::change_to_attributes(first_param, str_vec_1, PKB);
//        int i = 0;
//        for (auto iter : temp_vec_1)
//        {
//            if (iter == second_param.get_entity_name())
//            {
//                result_vec_1.push_back(str_vec_1[i]);
//            }
//            i++;
//        }
//        result[first_param.get_entity_name()] = result_vec_1;
//    }
//    else if (QueryUtility::is_proc_name(first_param) || QueryUtility::is_var_name(first_param))
//    { // e.g. with "main" = cl.procName
//        str_vec_1 = QueryUtility::get_certain_type_str_list(second_type, PKB);
//        temp_vec_1 = QueryUtility::change_to_attributes(second_param, str_vec_1, PKB);
//        int i = 0;
//        for (auto iter : temp_vec_1)
//        {
//            if (iter == first_param.get_entity_name())
//            {
//                result_vec_1.push_back(str_vec_1[i]);
//            }
//            i++;
//        }
//        result[second_param.get_entity_name()] = result_vec_1;
//    }
//    else if (QueryUtility::is_proc_name(second_param) || QueryUtility::is_var_name(second_param))
//    { // e.g. with cl.procName = "main"
//        str_vec_1 = QueryUtility::get_certain_type_str_list(first_type, PKB);
//        temp_vec_1 = QueryUtility::change_to_attributes(first_param, str_vec_1, PKB);
//        int i = 0;
//        for (auto iter : temp_vec_1)
//        {
//            if (iter == second_param.get_entity_name())
//            {
//                result_vec_1.push_back(str_vec_1[i]);
//            }
//            i++;
//        }
//        result[first_param.get_entity_name()] = result_vec_1;
//    }
//    else
//    { // e.g. with s.stmt# = a.stmt#
//        if (first_type == EntityType::VARIABLE || first_type == EntityType::PROCEDURE || first_type == EntityType::CONSTANT)
//        {
//            str_vec_1 = QueryUtility::get_certain_type_str_list(first_type, PKB);
//        }
//        if (first_type == EntityType::CALL || first_type == EntityType::PRINT || first_type == EntityType::READ || first_type == EntityType::STMT || first_type == EntityType::WHILE || first_type == EntityType::IF || first_type == EntityType::ASSIGN || first_type == EntityType::PROG_LINE)
//        {
//            str_vec_1 = QueryUtility::get_certain_type_int_list(first_type, PKB);
//        }
//        if (second_type == EntityType::VARIABLE || second_type == EntityType::PROCEDURE || second_type == EntityType::CONSTANT)
//        {
//            str_vec_2 = QueryUtility::get_certain_type_str_list(second_type, PKB);
//        }
//        if (second_type == EntityType::CALL || second_type == EntityType::PRINT || second_type == EntityType::READ || second_type == EntityType::STMT || second_type == EntityType::WHILE || second_type == EntityType::IF || second_type == EntityType::ASSIGN || second_type == EntityType::PROG_LINE)
//        {
//            str_vec_2 = QueryUtility::get_certain_type_int_list(second_type, PKB);
//        }
//        temp_vec_1 = QueryUtility::change_to_attributes(first_param, str_vec_1, PKB);
//        temp_vec_2 = QueryUtility::change_to_attributes(second_param, str_vec_2, PKB);
//        int i = 0;
//        int j = 0;
//        for (auto iter_1 : temp_vec_1)
//        {
//            for (auto iter_2 : temp_vec_2)
//            {
//                if (iter_1 == iter_2)
//                {
//                    result_vec_1.push_back(str_vec_1[i]);
//                    result_vec_2.push_back(str_vec_2[j]);
//                }
//                j++;
//            }
//            i++;
//        }
//        result[first_param.get_entity_name()] = result_vec_1;
//        result[second_param.get_entity_name()] = result_vec_2;
//    }
    return result;
}
