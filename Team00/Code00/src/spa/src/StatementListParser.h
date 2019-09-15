#ifndef AUTOTESTER_STATEMENTLISTPARSER_H
#define AUTOTESTER_STATEMENTLISTPARSER_H

#include <string>
#include <regex>
#include "Statement.h"
#include "StringUtil.h"
#include "pql_dto/Entity.h"

class StatementListParser
{
private:
    std::string raw_stmt_list;
    std::vector<Statement> stmt_list;
    StringUtil strUti;
    static int next_line_number;

public:
    // Constructor
    StatementListParser(std::string raw);

    std::vector<Statement> get_stmt_list();

    // The main parser.
    void parse_stmt_list();

    // This method will invoke respective parser for each statement.
    void invoke_parser();

    // This method is to parse if statement, and returns the remaining statements.
    std::string parse_if(std::string src);

    // This method is to parse while statement, and returns the remaining statements.
    std::string parse_while(std::string src);

    // This method is to parse print statement, and returns the remaining statements.
    std::string parse_print(std::string src);

    // This method is to parse read statement, and returns the remaining statements.
    std::string parse_read(std::string src);

    // This method is to parse call statement, and returns the remaining statements.
    std::string parse_call(std::string src);

    // This method is to parse assign statement, and returns the remaining statements.
    std::string parse_assign(std::string src);

    // This method is to parse parentheses, and returns the index of the ending bracket.
    int parse_bracket(std::string src, std::string opening, std::string closing);

    // This method will find the first occurrence of semicolon,
    // and returns the index of the next character of that semicolon.
    int find_semicolon(std::string src);
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
