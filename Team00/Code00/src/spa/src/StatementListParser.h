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
    StringModification strMod;

public:
    // Constructor
    StatementListParser(string raw);

    vector<Statement> get_stmt_list();

    // The main parser.
    void parse_stmt_list();

    // This method is to parse if statement, and returns the remaining statements.
    string parse_if(string src);

    // This method is to parse parentheses, and returns the index of the ending bracket.
    int parse_bracket(string src, string opening, string closing);
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
