#ifndef AUTOTESTER_STATEMENT_H
#define AUTOTESTER_STATEMENT_H

#include "pql_dto/Entity.h"

class Statement
{
private:
    EntityType statement_type;
    int statement_line;
    std::string statement;
    std::string condition;
    std::vector<Statement> first_block;
    std::vector<Statement> second_block;
    std::string proc_belonging;

public:
    /**
     * The constructor for a Statement.
     * @param statement_type The type of this statement.
     * @param prog_line The line number.
     * @param statement The statement contents.
     */
    Statement(EntityType statement_type, int prog_line, std::string statement);

    /**
     * The statement type getter.
     * @return the type of this statement.
     */
    EntityType get_statement_type();

    /**
     * The line number getter.
     * @return the line number of this statement.
     */
    int get_prog_line();

    /**
     * The body of the statement getter.
     * @return The body of the statement as a string.
     */
    std::string get_statement();

    /**
     * The condition of the statement getter.
     * @return The condition of the statement.
     */
    std::string get_condition();

    /**
     * Set the condition of the statement.
     * @param condi The condition to be set into the statement.
     */
    void set_condition(std::string condi);

    /**
     * The first block getter, the loop body in while statement or the then body in if statement.
     * @return the first block of the statement.
     */
    std::vector<Statement> get_first_block();

    /**
     * Set the procedure that this statement belongs to.
     * @param proc The procedure that this statement belongs to.
     */
    void set_procedure(std::string proc);

    /**
     * The procedure getter.
     * @return the name of the procedure that this statement belongs to.
     */
    std::string get_procedure();

    /**
     * Set the first block.
     * @param fb The first block to be set into the statement.
     */
    void set_first_block(std::vector<Statement> fb);

    /**
     * The second block getter, only the else body in if statement.
     * @return the second block in this statement.
     */
    std::vector<Statement> get_second_block();

    /**
     * Set the second block.
     * @param sb the second block to be set into the statement.
     */
    void set_second_block(std::vector<Statement> sb);
};

#endif //AUTOTESTER_STATEMENT_H
