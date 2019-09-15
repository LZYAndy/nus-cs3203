#ifndef AUTOTESTER_STATEMENT_H
#define AUTOTESTER_STATEMENT_H

#include "pql_dto/Entity.h"

using namespace std;

class Statement
{
private:
    EntityType statement_type;
    int statement_line;
    string statement;
    string condition;
    vector<Statement> first_block;
    vector<Statement> second_block;

public:
    // Constructor
    Statement(EntityType statement_type, int prog_line, string statement);

    // Returns the StatementType.
    EntityType get_statement_type();

    // Returns the program line number.
    int get_prog_line();

    // Returns the original statement as string.
    string get_statement();

    // Returns the condition.
    string get_condition();

    // Set the condition.
    void set_condition(string condi);

    // Returns the first block;
    vector<Statement> get_first_block();

    // Set the first block.
    void set_first_block(vector<Statement> fb);

    // Returns the second block.
    vector<Statement> get_second_block();

    // Set the second block.
    void set_second_block(vector<Statement> sb);
};

#endif //AUTOTESTER_STATEMENT_H
