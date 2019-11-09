#include <iostream>
#include "StringUtil.h"

std::vector<std::string> StringUtil::split(const std::string &query, std::string delimiter)
{
    std::vector<std::string> split_query;
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = query.find(delimiter, pos_start)) != std::string::npos)
    {
        token = query.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        split_query.push_back(token);
    }

    split_query.push_back(query.substr(pos_start));
    return split_query;
}

std::vector<std::string> StringUtil::split(const std::string &query, char delimiter)
{
    std::vector<std::string> split_query;
    std::istringstream iss(query);
    std::string token;

    while (std::getline(iss, token, delimiter))
    {
        split_query.push_back(token);
    }

    return split_query;
}

std::string StringUtil::trim(const std::string &s, const std::string &whitespace)
{
    int strStart = s.find_first_not_of(whitespace);
    int strEnd = s.find_last_not_of(whitespace);

    if (strStart == std::string::npos)
    {
        return "";
    }

    int strLength = strEnd - strStart + 1;
    return s.substr(strStart, strLength);

}

std::string StringUtil::replace_all_white_spaces(std::string &s)
{
    std::regex r("\\s+");
    s = std::regex_replace(s, r, " ");
    return s;
}

std::string StringUtil::remove_all_white_spaces(std::string &s)
{
    std::regex r("\\s+");
    s = std::regex_replace(s, r, "");
    return s;
}

std::string StringUtil::trim_left(std::string &s)
{
    int strStart = s.find_first_not_of(" \n\t\r\f\v");

    if (strStart == std::string::npos)
    {
        return "";
    }

    return s.substr(strStart);
}

std::vector<std::string> StringUtil::get_all_var(std::string statement)
{
    std::smatch match;
    std::vector<std::string> all_var;

    while (regex_search(statement, match, all_word))
    {
        std::string current_word = match[0];
        statement = match.suffix().str();
        if (CheckerUtil::is_name_valid(current_word))
        {
            all_var.push_back(trim(current_word, " \n\t\r\f\v"));
        }
    }

    return all_var;
}

std::vector<std::string> StringUtil::get_all_const(std::string statement)
{
    std::smatch match;
    std::vector<std::string> all_const;

    while (regex_search(statement, match, all_word))
    {
        std::string current_word = match[0];
        statement = match.suffix().str();
        if (CheckerUtil::is_const_valid(current_word))
        {
            all_const.push_back(process_constant(current_word));
        }
    }

    return all_const;
}

std::string StringUtil::preprocess_expr_string(std::string input)
{
    // Strip all whitespace
    std::regex re("(\\s+)");
    std::string result = regex_replace(input, re, "");

    // Add space before and after an operator
    std::regex re2("([+\\-*/%])");
    result = regex_replace(result, re2, " $1 ");

    // Special case for parenthesis
    std::regex re3("([(])");
    result = regex_replace(result, re3, "$1 ");
    std::regex re4("([)])");
    result = regex_replace(result, re4, " $1");

    // Trim left and right spaces
    result = StringUtil::trim(result, " \n\t\r\f\v");

    return result;
}

std::string StringUtil::process_constant(std::string input)
{
    if (std::regex_match(input, std::regex("^0+$"))){
        return "0";
    }

    if (std::regex_match(input, std::regex("^(0+)(.*)$"))){
        return regex_replace(input, std::regex("^(0+)(.*)$"), "$2");
    }

    return input;
}
