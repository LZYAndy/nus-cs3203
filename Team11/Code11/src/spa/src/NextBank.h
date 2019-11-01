#ifndef AUTOTESTER_NEXTBANK_H
#define AUTOTESTER_NEXTBANK_H


#include "Bank.h"

class NextBank
{
public:
    /**
     * Insert Next relationship between statement1 and statement2.
     * @param stmt1
     * @param stmt2
     * @return Return true if the relationship is inserted successfully, otherwise false.
     */
    bool insert_next(int stmt1, int stmt2);

    /**
     * If there is a Next relationship between statement1 and statement2.
     * @param stmt1
     * @param stmt2
     * @return Return true if there is a Next relationship between these two statements, otherwise false.
     */
    bool is_next(int stmt1, int stmt2);

    /**
     * If there exists at least one Next relationship in the program.
     * @return Return true if there exists at least one Next relationship, otherwise false.
     */
    bool does_next_exists();

    /**
     * Get all statements that are the Previous statement of the input statement
     * @param statement
     * @return Return a vector of statements which are the previous statement of the input statement.
     */
    std::vector<int> get_statements_previous(int statement);

    /**
     * Get all statements that are the Next statement of the input statement
     * @param statement
     * @return Return a vector of statements which are the next statement of the input statement.
     */
    std::vector<int> get_statements_next(int statement);

    /**
     * Get all statements which are the in previous position in their Next relationships.
     * @return Return all which are the in previous position in their Next relationships.
     */
    std::vector<int> get_all_previous();

    /**
     * Get all statements which are the in next position in their Next relationships.
     * @return Return all which are the in next position in their Next relationships.
     */
    std::vector<int> get_all_next();

    /**
     * Get all next relationships
     * @return Return all next relationships in the program
     */
    std::unordered_map<int, std::vector<int>> get_all_next_relationship();

    /**
     * Get all reversed next relationships
     * @return Return all reversed next relationships in the program
     */
    std::unordered_map<int, std::vector<int>> get_all_previous_relationship();

private:
    Bank<int, int> next_bank;
};


#endif //AUTOTESTER_NEXTBANK_H
