#ifndef SPA_STATEMENT_H
#define SPA_STATEMENT_H

#include <string>

using namespace std;

enum StatementType
{
    ASSIGN = 1,
    CALL = 2,
    IF = 3,
    ELSE = 4,
    WHILE = 5,
    PRINT = 6,
    READ = 7,
    PROCEDURE = 8
};

class Statement
{
private:
    StatementType statement_type;
    int statement_line;
    string statement;
public:
    // Constructor
    Statement(StatementType statement_type, int prog_line, string statement);

    // Returns the StatementType.
    StatementType get_statement_type();

    // Returns the program line number.
    int get_prog_line();

    // Returns the original statement as string.
    string get_statement();
};

#endif //SPA_STATEMENT_H
