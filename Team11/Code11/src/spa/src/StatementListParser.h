#ifndef AUTOTESTER_STATEMENTLISTPARSER_H
#define AUTOTESTER_STATEMENTLISTPARSER_H

#include <string>
#include <regex>
#include "Statement.h"
#include "StringUtil.h"
#include "pql_dto/Entity.h"
#include "ErrorMessages.h"

class StatementListParser
{
private:
    std::string raw_stmt_list;
    std::vector<Statement> stmt_list;
    int next_line_number;
    std::string proc_belonging;

public:
    // Constructor
    StatementListParser(std::string raw, int this_line_num);

    std::vector<Statement> get_stmt_list();

    // The main parser.
    void parse_stmt_list();

    // Set the procedure that the statement list belongs to.
    void set_procedure(std::string proc);

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

    int get_last_num(std::vector<Statement> stmts);

    // This method is to parse brackets, and returns the index of the ending bracket + 1.
    static int parse_bracket(std::string src, std::string opening, std::string closing);

    // This method will find the first occurrence of semicolon,
    // and returns the index of the next character of that semicolon.
    static int find_semicolon(std::string src);

    // Check the first non-space character is the given character or not.
    static bool is_beginning_with(std::string src, const std::string &match_char);
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
