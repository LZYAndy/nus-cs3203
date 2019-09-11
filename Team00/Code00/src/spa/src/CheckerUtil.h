#ifndef AUTOTESTER_CHECKERUTIL_H
#define AUTOTESTER_CHECKERUTIL_H

#include <string>
#include <regex>

using namespace std;

class CheckerUtil
{
public:
    bool is_name_valid(string stmt);

    bool is_const_valid(string stmt);

    bool is_expr_valid(string stmt);

    bool is_condition_valid(string stmt);
private:
    bool is_bracket_balanced(string stmt);
};



#endif //AUTOTESTER_CHECKERUTIL_H