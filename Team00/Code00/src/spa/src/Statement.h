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

public:
    // Constructor
    Statement(EntityType statement_type, int prog_line, string statement);

    // Returns the StatementType.
    EntityType get_statement_type();

    // Returns the program line number.
    int get_prog_line();

    // Returns the original statement as string.
    string get_statement();
};

#endif //SPA_STATEMENT_H
