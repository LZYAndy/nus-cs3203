#ifndef AUTOTESTER_STATEMENT_H
#define AUTOTESTER_STATEMENT_H

class Statement
{
private:
    EntityType statement_type;
    int statement_line;
    std::string statement;
    std::string condition;
    std::string first_block;
    std::string second_block;

public:
    // Constructor
    Statement(EntityType statement_type, int prog_line, std::string statement);

    // Returns the StatementType.
    EntityType get_statement_type();

    // Returns the program line number.
    int get_prog_line();

    // Returns the original statement as string.
    std::string get_statement();

    // Returns the condition.
    std::string get_condition();

    // Returns the first block;
    std::string get_first_block();

    // Returns the second block.
    std::string get_second_block();
};

#endif //AUTOTESTER_STATEMENT_H
