#pragma once

#include <string>
#include <vector>

class StringUtil
{
public:
    /*!
        Splits the query using a string delimiter.
        @param query The query string to be split.
        @param delimiter The string that is used to split the query.
        @return The vector of string split by the delimiter.
        */
    static std::vector<std::string> split(const std::string& query, std::string delimiter);

    /*!
    Splits the query using a char delimiter.
    @param query The query string to be split.
    @param delimiter The char that is used to split the query.
    @return The vector of string split by the delimiter.
    */
    static std::vector<std::string> split(const std::string& query, char delimiter);

    /*!
    Removes whitespace from the start and end of the given string.
    @param string The string to be trim.
    @param whitespace The char that is used to trim the string.
    @return The string without the whitespace.
    */
    static std::string trim(const std::string& string, const std::string& whitespace);

    /*!
    Removes all whitespaces from the given string.
    @param string The string.
    @return The string without whitespaces.
    */
    static std::string remove_all_white_spaces(const std::string string);
};
