#ifndef AUTOTESTER_READPARSER_H
#define AUTOTESTER_READPARSER_H

#include <string>
#include <regex>
#include "PKB.h"

using namespace std;

class ReadParser
{
public:
    ReadParser(PKB pkb, string statement, int parent_prog_line);

private:
    bool is_read_valid(string statement);

    string get_var(string statement);
};

#endif //AUTOTESTER_READPARSER_H
