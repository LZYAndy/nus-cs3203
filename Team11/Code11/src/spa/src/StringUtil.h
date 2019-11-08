#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <regex>
#include "CheckerUtil.h"

class StringUtil
{
public:
    /**
     * Splits the query using a string delimiter.
     * @param query The pointer to the query string to be split.
     * @param delimiter The string that is used to split the query.
     * @return The vector of string split by the delimiter.
     */
    static std::vector<std::string> split(const std::string &query, std::string delimiter);

    /**
     * Splits the query using a char delimiter.
     * @param query The pointer to the query string to be split.
     * @param delimiter The char that is used to split the query.
     * @return The vector of string split by the delimiter.
     */
    static std::vector<std::string> split(const std::string &query, char delimiter);

    /**
     * Removes whitespace from the start and end of the given string.
     * @param s The pointer to the string to be trim.
     * @param whitespace The pointer to the string of chars that is used to trim the string.
     * @return The string without the whitespace.
     */
    static std::string trim(const std::string &s, const std::string &whitespace);

    /**
     * Replace all whitespaces from the given string with a space character.
     * @param s The pointer to the string.
     * @return The string without whitespaces.
     */
    static std::string replace_all_white_spaces(std::string &s);

    /**
     * Remove all whitespaces from the given string.
     * @param s The pointer to the string.
     * @return The string without whitespaces.
     */
    static std::string remove_all_white_spaces(std::string &s);

    /**
      * Removes all whitespaces from the beginning of the string.
      * @param s The pointer to the string.
      * @return The string starting from a non-whitespace character.
      */
    static std::string trim_left(std::string &s);

    /**
      * Gets all valid variable from a string.
      * @param input The string.
      * @return The vector of variables in string.
      */
    static std::vector<std::string> get_all_var(std::string input);

    /**
     * Gets all valid constant from a string.
     * @param input The string.
     * @return The vector of constants in string.
     */
    static std::vector<std::string> get_all_const(std::string input);

    /**
     * Converts an infix expression into a string without whitespaces except a single space before and after an operator.
     * @param input An infix expression
     * @return An infix expression with no whitespaces except a single space before and after an operator.
     */
    static std::string preprocess_expr_string(std::string input);

    /**
    * Removes any trailing zero character in a string.
    * @param input A string
    * @return A string with trailing zero removed.
    */
    static std::string process_constant(std::string input);
};
