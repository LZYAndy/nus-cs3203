#ifndef AUTOTESTER_USESBANK_H
#define AUTOTESTER_USESBANK_H

#include "Bank.h"

class UsesBank
{
public:
    /*
     * Insert Uses relation for a statement into the UsesBank
     * Returns false if the relation already exists
     */
    bool insert_uses(int statement, std::string variable);

    /*
     * Insert Uses relation for a procedure into the UsesBank
     * Returns false if the relation already exists
     */
    bool insert_uses(std::string procedure, std::string variable);

    std::vector<int> get_statements_uses(std::string variable);
    std::vector<std::string> get_procedures_uses(std::string variable);
    std::vector<std::string> get_used_by_statement(int statement);
    std::vector<std::string> get_used_by_procedure(std::string procedure);

    bool is_uses(std::string procedure, std::string variable);
    bool is_uses(int statement, std::string variable);

private:
    Bank<int, std::string> stmt_bank;
    Bank<std::string, std::string> proc_bank;
};


#endif //AUTOTESTER_USESBANK_H
