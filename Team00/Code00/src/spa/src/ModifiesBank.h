#ifndef AUTOTESTER_MODIFIESBANK_H
#define AUTOTESTER_MODIFIESBANK_H

#include "Bank.h"

class ModifiesBank
{
public:
    /*
     * Insert Modifies relation for a statement into the ModifiesBank
     */
    void insert_modifies(int statement, std::string variable);

    /*
     * Insert Modifies relation for a procedure into the ModifiesBank
     */
    void insert_modifies(std::string procedure, std::string variable);

    std::vector<int> get_statements_modifies(std::string variable);
    std::vector<std::string> get_procedures_modifies(std::string variable);
    std::vector<std::string> get_modified_by_statement(int statement);
    std::vector<std::string> get_modified_by_procedure(std::string procedure);
    bool is_modifies(int statement, std::string variable);
    bool is_modifies(std::string procedure, std::string variable);
    std::vector<std::string> get_all_modifies_procedures();
    std::vector<int> get_all_modifies_statements();

    std::unordered_map<std::string, std::vector<std::string>> get_all_modifies_procedures_relationship();
    std::unordered_map<int, std::vector<std::string>> get_all_modifies_statements_relationship();
private:
    Bank<int, std::string> stmt_bank;
    Bank<std::string, std::string> proc_bank;
};


#endif //AUTOTESTER_MODIFIESBANK_H
