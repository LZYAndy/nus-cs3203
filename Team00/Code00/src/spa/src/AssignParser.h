#ifndef AUTOTESTER_ASSIGNPARSER_H
#define AUTOTESTER_ASSIGNPARSER_H

#include <string>
#include <regex>
#include "PKB.h"

using namespace std;

class AssignParser
{
public:
    AssignParser(PKB pkb, string statement, int parent_prog_line);

private:
    string get_left(string statement);

    string get_right(string statement);

    vector<string> get_all_var(string sub_statement);

};

#endif //AUTOTESTER_ASSIGNPARSER_H
