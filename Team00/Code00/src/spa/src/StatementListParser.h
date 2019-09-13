#ifndef AUTOTESTER_STATEMENTLISTPARSER_H
#define AUTOTESTER_STATEMENTLISTPARSER_H

#include <string>
#include <regex>
#include "Statement.h"
#include "StringModification.h"

using namespace std;

class StatementListParser
{
private:
    string raw_stmt_list;
    vector<Statement> stmt_list;

public:
    // Constructor
    StatementListParser(string raw);

    vector<Statement> get_stmt_list();

    // The main parser.
    void parse_stmt_list();
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
