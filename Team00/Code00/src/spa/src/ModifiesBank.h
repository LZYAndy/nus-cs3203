#ifndef AUTOTESTER_MODIFIESBANK_H
#define AUTOTESTER_MODIFIESBANK_H

#include "Bank.h"

class ModifiesBank
{
public:
    /**
     * Insert a Modifies relationship between the input statement and the input variable into stmt_bank.
     * @param statement
     * @param variable
     * @return Return true if there is a Modifies relationship between the input statement and the input variable.
     */
    bool insert_modifies(int statement, std::string variable);

    /**
     * Insert a Modifies relationship between the input procedure and the input variable into proc_bank.
     * @param procedure
     * @param variable
     * @return Return true if there is a Modifies relationship between the input procedure and the input variable.
     */
    bool insert_modifies(std::string procedure, std::string variable);

    /**
     * Get all statements that modifies the input variable.
     * @param variable
     * @return Return an integer vector of all statement that modifies the variable.
     */
    std::vector<int> get_statements_modifies(std::string variable);

    /**
     * Get all procedures that modifies the input variable.
     * @param variable
     * @return Return a string vector of all procedures that modifies the variable.
     */
    std::vector<std::string> get_procedures_modifies(std::string variable);

    /**
     * Get all variables modifies by the input statement.
     * @param statement
     * @return Return a string vector of variables modifies by the statement.
     */
    std::vector<std::string> get_modified_by_statement(int statement);

    /**
     * Get all variables modifies by the input procedure.
     * @param procedure
     * @return Return a string vector of variables modifies by the statement.
     */
    std::vector<std::string> get_modified_by_procedure(std::string procedure);

    /**
     * Return true if there is a Modifies relationship between the input statement and the input variable.
     * @param statement
     * @param variable
     * @return Return true if there is a Modifies relationship between the input statement and the input variable.
     */
    bool is_modifies(int statement, std::string variable);

    /**
     * Return true if there is a Modifies relationship between the input procedure and the input variable.
     * @param procedure
     * @param variable
     * @return Return true if there is a Modifies relationship between the input procedure and the input variable.
     */
    bool is_modifies(std::string procedure, std::string variable);

    /**
     * Get all procedures having one or more Modifies relationships.
     * @return Return a string vector of procedures having one or more Modifies relationships.
     */
    std::vector<std::string> get_all_modifies_procedures();

    /**
     * Get all statements having one or more Modifies relationships.
     * @return Return an integer vector of statements having one or more Modifies relationships.
     */
    std::vector<int> get_all_modifies_statements();

    /**
     * Get all procedure-variable Modifies relationships.
     * @return Return an unordered_map<string, vector<string>> with procedure name as key and variable(s) as value.
     */
    std::unordered_map<std::string, std::vector<std::string>> get_all_modifies_procedures_relationship();

    /**
     * Get all statement-variable Modifies relationships.
     * @return Return an unordered_map<int, vector<string>> with statement number as key and variable(s) as value.
     */
    std::unordered_map<int, std::vector<std::string>> get_all_modifies_statements_relationship();

    /**
     * Return true if the ModifiesBank is empty.
     * @return Return true if the ModifiesBank is empty.
     */
    bool does_modifies_exist();

private:
    Bank<int, std::string> stmt_bank;
    Bank<std::string, std::string> proc_bank;
};

#endif //AUTOTESTER_MODIFIESBANK_H
