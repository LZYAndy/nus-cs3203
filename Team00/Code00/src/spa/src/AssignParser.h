#ifndef AUTOTESTER_ASSIGNPARSER_H
#define AUTOTESTER_ASSIGNPARSER_H

#include <string>
#include <regex>
#include "PKB.h"
#include "CheckerUtil.h"
#include "Statement.h"

using namespace std;

class AssignParser
{
public:
    AssignParser(PKB pkb, Statement statement, string parent_prog_line);

private:
    string get_left(string statement);

    string get_right(string statement);

    vector<string> get_all_var(string sub_statement);

};

#endif //AUTOTESTER_ASSIGNPARSER_H
