#ifndef AUTOTESTER_CHECKERUTIL_H
#define AUTOTESTER_CHECKERUTIL_H

#include <string>
#include <regex>

using namespace std;

class CheckerUtil
{

};

namespace parser_checker
{
    bool is_procedure_name_valid(string stmt);

    bool is_condition_valid(string stmt);
}

#endif //AUTOTESTER_CHECKERUTIL_H