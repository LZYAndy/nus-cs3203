#include "StringUtil.h"

std::vector<std::string> StringUtil::split(const std::string& query, std::string delimiter)
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

std::vector<std::string> StringUtil::split(const std::string& query, char delimiter)
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

std::string StringUtil::trim(const std::string& string, const std::string& whitespace)
{
    int strStart = string.find_first_not_of(whitespace);
    int strEnd = string.find_last_not_of(whitespace);

    if (strStart == std::string::npos) {
        return "";
    }

    int strLength = strEnd - strStart + 1;
    return string.substr(strStart, strLength);

}

std::string StringUtil::remove_all_white_spaces(const std::string string) {
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());
    return string;
}