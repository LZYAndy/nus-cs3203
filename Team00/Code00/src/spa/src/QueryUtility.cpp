//
// Created by 刘照宇 on 2/9/19.
//

#include <pql_dto/Entity.h>
#include "QueryUtility.h"

PKB PKB;

/*
Checks if the string is an integer
*/
bool QueryUtility::is_integer(string& s)
{
    for (char i : s)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }
    return true;
}

/*
Checks if the entity is a procedure undeclared
*/
bool QueryUtility::is_proc_name(pql_dto::Entity entity)
{
    return !(entity.is_entity_declared() || entity.get_entity_type() != EntityType::PROCEDURE);
}

/*
Checks if the entity is a procedure declared
*/
bool QueryUtility::is_proc_declared(pql_dto::Entity entity)
{
    return (entity.is_entity_declared() && entity.get_entity_type() == EntityType::PROCEDURE);
}

/*
Checks if the entity is a variable undeclared
*/
bool QueryUtility::is_var_name(pql_dto::Entity entity)
{
    return !(entity.is_entity_declared() || entity.get_entity_type() != EntityType::VARIABLE);
}

/*
 * Returns the string list of certain type
 */
vector<string> QueryUtility::get_certain_type_str_list(EntityType type)
{
    unordered_set<string> type_list;
    unordered_set<string> :: iterator iter;
    vector<string> result;
    if (type == EntityType::VARIABLE)
    {
        type_list = PKB.get_all_variables();
    }

    if (type == EntityType::PROCEDURE)
    {
        type_list = PKB.get_all_procedures();
    }

    for (iter = type_list.begin(); iter != type_list.end(); iter++) {
        result.push_back(*iter);
    }

    return result;
}

/*
 * Returns the int list of certain type
 */
vector<string> QueryUtility::get_certain_type_int_list(EntityType type)
{
    vector<int> type_list;
    vector<string> result;
    if (type == EntityType::ASSIGN)
    {
        type_list = PKB.get_all_assigns();
    }

    if (type == EntityType::STMT)
    {
        type_list = PKB.get_all_statement_nums();
    }

    if (type == EntityType::WHILE)
    {
        type_list = PKB.get_all_whiles();
    }

    if (type == EntityType::IF)
    {
        type_list = PKB.get_all_ifs();
    }

    if (type == EntityType::READ)
    {
        type_list = PKB.get_all_reads();
    }

    if (type == EntityType::PRINT)
    {
        type_list = PKB.get_all_prints();
    }

    if (type == EntityType::CALL)
    {
        type_list = PKB.get_all_calls();
    }

    result.reserve(type_list.size());
    for (auto iter : type_list) {
        result.push_back(to_string(iter));
    }

    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key, vector<int>& int_vec)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    for (auto & iter : int_vec)
    {
        if (PKB.get_statement_type(iter) == key.get_entity_type())
        {
            key_value.push_back(to_string(iter));
        }
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key, vector<string>& str_vec)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    key_value.reserve(str_vec.size());
    for (auto & iter : str_vec)
    {
        key_value.push_back(iter);
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key, int n)
{
    unordered_map<string, vector<string>> result;
    std::vector<std::string> key_value;
    if (PKB.get_statement_type(n) == key.get_entity_type())
    {
        key_value.push_back(to_string(n));
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
        unordered_map<int, vector<int>>& int_map)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto & iter : int_map)
    {
        int first = iter.first;
        vector<int> second = iter.second;
        if (PKB.get_statement_type(first) == key_1.get_entity_type())
        {
            for (auto & it : second) {
                if (PKB.get_statement_type(it) == key_2.get_entity_type()) {
                    key_value_1.push_back(to_string(first));
                    key_value_2.push_back(to_string(it));
                }
            }
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
        unordered_map<string, vector<string>>& str_map)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto & iter : str_map)
    {
        string first = iter.first;
        vector<string> second = iter.second;
        for (const auto& it : second) {
            key_value_1.push_back(first);
            key_value_2.push_back(it);
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
        unordered_map<int, vector<string>>& int_str_map)
{
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto & iter : int_str_map)
    {
        int first = iter.first;
        vector<string> second = iter.second;
        if (PKB.get_statement_type(first) == key_1.get_entity_type())
        {
            for (auto & it : second) {
                key_value_1.push_back(to_string(first));
                key_value_2.push_back(it);
            }
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(const string& str, vector<int>& int_vec) {
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    key_value.reserve(int_vec.size());
    for (auto & iter : int_vec)
    {
        key_value.push_back(to_string(iter));
    }
    result[str] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(const string& str1, const string& str2,
        vector<int>& int_vec) {
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    for (auto & iter : int_vec) {
        if (PKB.assign_to_variable(iter) == str2) {
            key_value.push_back(to_string(iter));
        }
    }
    result[str1] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(const string& str1, pql_dto::Entity key,
        vector<int>& int_vec) {
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (auto & iter : int_vec) {
        key_value_1.push_back(to_string(iter));
        key_value_2.push_back(PKB.assign_to_variable(iter));
    }
    result[str1] = key_value_1;
    result[key.get_entity_name()] = key_value_2;
    return result;
}

