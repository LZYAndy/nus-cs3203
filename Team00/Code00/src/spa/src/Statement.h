#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <string>

using namespace std;

class Statement
{
private:
    EntityType statement_type;
    int statement_line;
    string statement;
    string condition;
    string first_block;
    string second_block;

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

    // Returns the first block;
    string get_first_block();

    // Returns the second block.
    string get_second_block();
};

#endif //SPA_STATEMENT_H
