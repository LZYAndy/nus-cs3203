//
// Created by 刘照宇 on 2/9/19.
//

#include <pql_dto/Entity.h>
#include "QueryUtility.h"

/*
Checks if the string is an integer
*/
bool QueryUtility::is_integer(string s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

/*
Checks if the entity is a procedure undeclared
*/
bool QueryUtility::is_proc_name(pql_dto::Entity entity) {
    return !(entity.is_entity_declared() || entity.get_entity_type() != EntityType::PROCEDURE);
}

/*
Checks if the entity is a procedure declared
*/
bool QueryUtility::is_proc_declared(pql_dto::Entity entity) {
    return (entity.is_entity_declared() && entity.get_entity_type() == EntityType::PROCEDURE);
}

/*
Checks if the entity is a variable undeclared
*/
bool QueryUtility::is_var_name(pql_dto::Entity entity) {
    return !(entity.is_entity_declared() || entity.get_entity_type() != EntityType::VARIABLE);
}

/*
 * Returns the list of certain type
 */
vector<string> QueryUtility::get_certain_type_list(EntityType type) {
    vector<string> type_list;
    if (type == EntityType::VARIABLE){
        type_list = PKB::get_var_list();
    }

    if (type == EntityType::ASSIGN){
        type_list = PKB::get_assign_list();
    }

    if (type == EntityType::STMT){
        type_list = PKB::get_stmt_list();
    }

    if (type == EntityType::PROCEDURE){
        type_list = PKB::get_proc_list();
    }

    if (type == EntityType::WHILE){
        type_list = PKB::get_while_list();
    }

    if (type == EntityType::IF){
        type_list = PKB::get_if_list();
    }

    if (type == EntityType::READ){
        type_list = PKB::get_read_list();
    }

    if (type == EntityType::PRINT){
        type_list = PKB::get_print_list();
    }

    if (type == EntityType::CALL){
        type_list = PKB::get_call_list();
    }
    return type_list;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key, vector<int> int_vec) {
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value;
    for (int & iter : int_vec) {
        if (PKB::get_statement_type(iter) == key.get_entity_type()) {
            key_value.push_back(to_string(iter));
        }
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key, int n) {
    unordered_map<string, vector<string>> result;
    std::vector<std::string> key_value;
    if (PKB::get_statement_type(n) == key.get_entity_type()) {
        key_value.push_back(to_string(n));
    }
    result[key.get_entity_name()] = key_value;
    return result;
}

unordered_map<string, vector<string>> QueryUtility::mapping(pql_dto::Entity key_1, pql_dto::Entity key_2,
        unordered_map<int, int> int_map) {
    unordered_map<std::string, std::vector<std::string>> result;
    vector<string> key_value_1;
    vector<string> key_value_2;
    for (unordered_map<int, int>::iterator iter = int_map.begin(); iter != int_map.end(); iter++) {
        int first = iter->first;
        int second = iter->second;
        if (PKB::get_statement_type(first) == key_1.get_entity_type() &&
        PKB::get_statement_type(second) == key_2.get_entity_type()) {
            key_value_1.push_back(to_string(first));
            key_value_2.push_back(to_string(second));
        }
    }
    result[key_1.get_entity_name()] = key_value_1;
    result[key_2.get_entity_name()] = key_value_2;
    return result;
}

