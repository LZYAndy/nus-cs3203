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

std::string StringUtil::trim(const std::string& s, const std::string& whitespace)
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

std::string StringUtil::replace_all_white_spaces(std::string& s)
{
    std::regex r("\\s+");
    s = std::regex_replace(s, r, " ");
    return s;
}

std::string StringUtil::trim_left(std::string& s)
{
    while (true)
    {
        std::string this_pos = s.substr(0,1);
        if (this_pos.compare(" ") == 0)
        {
            s = s.substr(1);
            continue;
        }
        else
        {
            return s;
        }
    }
}