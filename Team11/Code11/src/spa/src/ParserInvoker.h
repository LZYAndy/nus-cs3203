#ifndef AUTOTESTER_PARSERINVOKER_H
#define AUTOTESTER_PARSERINVOKER_H

#include <string>
#include "Statement.h"
#include "AssignParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "ReadParser.h"
#include "IfParser.h"
#include "WhileParser.h"
#include "PKB.h"
#include "pql_dto/Entity.h"

class ParserInvoker
{
private:
    std::vector<Statement> list_of_statement;
    PKB *pkb;
    std::string parent_prog_line;

public:
    /**
     * The constructor for ParserInvoker.
     * @param pkbi The PKB instance.
     * @param stmt_list The statement list that we need to go through each statement to invoker each parser.
     * @param parent_line The parent line number to help to insert Parent relationships.
     */
    ParserInvoker(PKB &pkbi, std::vector<Statement> stmt_list, std::string parent_line);

    /**
     * Invoke the parser to go through each statement inside the statement list
     * and call the respective parser.
     */
    void invoke_parser();

    /**
     * The helper function to insert the Next relationship in the case that an if statement
     * is the last statement in a container statement, the last statement of then and the last
     * statement of else should go back to the container statement or the next statement.
     * @param if_statement the if statement that is the last statement in the container statement.
     * @param next_stmt_num The next statement number inside the Next relationships to be inserted into PKB.
     */
    void insert_next_for_if(Statement if_statement, int next_stmt_num);
};

#endif //AUTOTESTER_PARSERINVOKER_H
