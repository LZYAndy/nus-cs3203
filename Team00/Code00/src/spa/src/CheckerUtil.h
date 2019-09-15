#ifndef AUTOTESTER_CHECKERUTIL_H
#define AUTOTESTER_CHECKERUTIL_H

#include <regex>

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