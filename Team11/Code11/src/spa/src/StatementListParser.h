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
    /**
     * The constructor for the StatementListParser.
     * @param raw The raw string to be parsed.
     * @param this_line_num The starting line number.
     */
    StatementListParser(std::string raw, int this_line_num);

    /**
     * The statement list getter.
     * @return the parsed statement list.
     */
    std::vector<Statement> get_stmt_list();

    /**
     * Parse the statement list.
     */
    void parse_stmt_list();

    /**
     * Set the procedure that the statement list belongs to.
     * @param proc The procedure that this statement list belongs to.
     */
    void set_procedure(std::string proc);

    /**
     * This method is to parse if statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is an if statement.
     * @return the rest statement.
     */
    std::string parse_if(std::string src);

    /**
     * This method is to parse while statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is a while statement.
     * @return the rest statement.
     */
    std::string parse_while(std::string src);

    /**
     * This method is to parse print statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is a print statement.
     * @return the rest statement.
     */
    std::string parse_print(std::string src);

    /**
     * This method is to parse read statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is a read statement.
     * @return the rest statement.
     */
    std::string parse_read(std::string src);

    /**
     * This method is to parse call statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is a call statement.
     * @return the rest statement.
     */
    std::string parse_call(std::string src);

    /**
     * This method is to parse assign statement, and returns the remaining statements.
     * @param src the raw string to be parsed with that the starting statement is an assignment statement.
     * @return the rest statement.
     */
    std::string parse_assign(std::string src);

    /**
     * Get the last statement number.
     * @param stmts the statement list that we need to find the last statement from.
     * @return the last statement number.
     */
    int get_last_num(std::vector<Statement> stmts);

    /**
     * This method is to parse brackets, and returns the index of the ending bracket + 1.
     * @param src The source string to find the brackets from.
     * @param opening The opening brackets, like "(" or "{".
     * @param closing The closing brackets, like ")" or "}".
     * @return the index of the ending bracket + 1.
     */
    static int parse_bracket(std::string src, std::string opening, std::string closing);

    /**
     * This method will find the first occurrence of semicolon,
     * and returns the index of the next character of that semicolon.
     * @param src the source string to find the semicolon from.
     * @return the index of the next character of that semicolon.
     */
    static int find_semicolon(std::string src);

    /**
     * Check the first non-space character is the given character or not.
     * @param src the source string.
     * @param match_char the character to need to match.
     * @return true if the first non-space character is exactly the match_char, otherwise false.
     */
    static bool is_beginning_with(std::string src, const std::string &match_char);
};


#endif //AUTOTESTER_STATEMENTLISTPARSER_H
