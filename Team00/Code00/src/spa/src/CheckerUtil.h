#pragma once
#ifndef AUTOTESTER_CHECKERUTIL_H
#define AUTOTESTER_CHECKERUTIL_H

#include <regex>

extern std::regex all_word;
extern std::regex valid_name;
extern std::regex valid_const;
//(_word_)  (_[+-*/%]_(_word_))*  <- Do not remove the space.
extern std::regex valid_expr;
extern std::regex valid_cond;

class CheckerUtil
{
public:
    /**
     * Check if a given string is a valid name.
     * @param stmt
     * @return Returns true if the input is valid, false otherwise.
     */
    static bool is_name_valid(std::string stmt);

    /**
     * Check if a given string is a valid constant.
     * @param stmt
     * @return Returns true if the input is valid, false otherwise.
     */
    static bool is_const_valid(std::string stmt);

    /**
     * Check if a given string is a valid expression.
     * @param stmt
     * @return Returns true if the input is valid, false otherwise.
     */
    static bool is_expr_valid(std::string stmt);

    /**
     * Check if a given string is a valid condition.
     * @param stmt
     * @return Returns true if the input is valid, false otherwise.
     */
    static bool is_condition_valid(std::string stmt);

private:
    /**
     * Check if a given string has balanced brackets.
     * @param stmt
     * @return Returns true if the input is valid, false otherwise.
     */
    static bool is_bracket_balanced(std::string stmt);
};



#endif //AUTOTESTER_CHECKERUTIL_H