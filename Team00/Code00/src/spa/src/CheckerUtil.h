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
    static bool is_name_valid(std::string stmt);

    static bool is_const_valid(std::string stmt);

    static bool is_expr_valid(std::string stmt);

    static bool is_condition_valid(std::string stmt);
private:
    static bool is_bracket_balanced(std::string stmt);
};



#endif //AUTOTESTER_CHECKERUTIL_H