#ifndef AUTOTESTER_STATEMENTLISTPARSER_H
#define AUTOTESTER_STATEMENTLISTPARSER_H

#include <string>
#include <regex>
#include "Statement.h"
#include "StringUtil.h"
#include "pql_dto/Entity.h"

using namespace std;

class StatementListParser
{
private:
    string raw_stmt_list;
    vector<Statement> stmt_list;
    StringUtil strUti;
    static int next_line_number;

public:
    // Constructor
    StatementListParser(string raw);

    vector<Statement> get_stmt_list();

    // The main parser.
    void parse_stmt_list();

    // This method will invoke respective parser for each statement.
    void invoke_parser();

    // This method is to parse if statement, and returns the remaining statements.
    string parse_if(string src);

    // This method is to parse while statement, and returns the remaining statements.
    string parse_while(string src);

    // This method is to parse print statement, and returns the remaining statements.
    string parse_print(string src);

    // This method is to parse read statement, and returns the remaining statements.
    string parse_read(string src);

    // This method is to parse call statement, and returns the remaining statements.
    string parse_call(string src);

    // This method is to parse assign statement, and returns the remaining statements.
    string parse_assign(string src);

    // This method is to parse parentheses, and returns the index of the ending bracket.
    int parse_bracket(string src, string opening, string closing);

    // This method will find the first occurrence of semicolon,
    // and returns the index of the next character of that semicolon.
    int find_semicolon(string src);
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
