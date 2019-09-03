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
Checks if the string is a synonym
*/
bool QueryUtility::is_synonym(std::string s) {
    bool result = !is_integer(s) && !is_quoted(s) && !has_reference(s) && s != "_";
    return result;
}

/*
Checks if the string is quoted
*/
bool QueryUtility::is_quoted(std::string s) {
    bool result = s[0] == '"';
    return result;
}

/*
Checks if the string contains a reference
*/
bool QueryUtility::has_reference(std::string s) {
    bool result = s.find(".") != std::string::npos;
    return result;
}

/*
 * Returns the list of certain type
 */
vector<string> QueryUtility::get_certain_type_list(EntityType type) {
    vector<string> type_list;
    if (type == EntityType::VARIABLE){
        type_list = {}; // get_var_list();
    }

    if (type == EntityType::ASSIGN){
        type_list = {}; // get_assign_list();
    }

    if (type == EntityType::STMT){
        type_list = {}; // get_stmt_list();
    }

    if (type == EntityType::PROCEDURE){
        type_list = {}; // get_proc_list();
    }

    if (type == EntityType::WHILE){
        type_list = {}; // get_while_list();
    }

    if (type == EntityType::IF){
        type_list = {}; // get_if_list();
    }

    if (type == EntityType::READ){
        type_list = {}; // get_read_list();
    }

    if (type == EntityType::PRINT){
        type_list = {}; // get_print_list();
    }

    if (type == EntityType::CALL){
        type_list = {}; // get_call_list();
    }
    return type_list
}










/*
The function transforms a boolean value
into a string.
*/
std::string QueryUtility::truthValue(bool boolean) {
    if (boolean) {
        return "TRUE";
    }

    return "FALSE";
}

/*
Trims quote in front and end of a string.
*/
std::string QueryUtility::trimFrontEnd(std::string quotedString) {
    return quotedString.substr(1, quotedString.size() - 2);
}



/*
Checks if the string is quoted
*/
bool QueryUtility::isQuoted(std::string s) {
    bool result = s[0] == '"';
    return result;
}

/*
Checks if the string is a synonym
*/
bool QueryUtility::isSynonym(std::string s) {
    bool result = !isInteger(s) && !isQuoted(s) && !hasReference(s) && s != "_";
    return result;
}

/*
Checks if the string contains a reference
*/
bool QueryUtility::hasReference(std::string s) {
    bool result = s.find(".") != std::string::npos;
    return result;
}

/*
Checks if string s, which is an integer
is not in the range of integers of source
statements
*/
bool QueryUtility::isOutOfRange(std::string s) {
    bool result = LexicalToken::verifyInteger(s)
                  && ((s.compare("1") < 0)
                      || (s.compare(std::to_string(PKB().getTotalStmNo())) > 0));
    return result;
}

/*
Get attribute of an
attribute reference.
*/
std::string QueryUtility::attrOf(std::string s) {
    std::size_t dotPos = s.find(".");
    return s.substr(0, dotPos);
}

/*
Get reference of an
attribute reference.
*/
std::string QueryUtility::refOf(std::string s) {
    std::size_t dotPos = s.find(".");
    return s.substr(dotPos + 1, s.size() - dotPos - 1);
}
/*
The function returns the list of all statements.
*/
std::unordered_set<std::string> QueryUtility::getAllStms() {
    std::unordered_set<std::string> allStms;
    for (int i = 1; i <= PKB().getTotalStmNo(); i++) {
        allStms.insert(std::to_string(i));
    }

    return allStms;
}
