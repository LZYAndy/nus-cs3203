#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <regex>

class StringUtil
{
public:
    /*!
    Splits the query using a string delimiter.
    @param query The pointer to the query string to be split.
    @param delimiter The string that is used to split the query.
    @return The vector of string split by the delimiter.
    */
    static std::vector<std::string> split(const std::string& query, std::string delimiter);

    /*!
    Splits the query using a char delimiter.
    @param query The pointer to the query string to be split.
    @param delimiter The char that is used to split the query.
    @return The vector of string split by the delimiter.
    */
    static std::vector<std::string> split(const std::string& query, char delimiter);

    /*!
    Removes whitespace from the start and end of the given string.
    @param s The pointer to the string to be trim.
    @param whitespace The pointer to the string of chars that is used to trim the string.
    @return The string without the whitespace.
    */
    static std::string trim(const std::string& s, const std::string& whitespace);

    /*!
    Replace all whitespaces from the given string with a space character.
    @param s The string.
    @return The string without whitespaces.
    */
    static std::string replace_all_white_spaces(std::string& s);
};
