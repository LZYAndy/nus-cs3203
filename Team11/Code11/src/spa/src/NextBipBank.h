#ifndef AUTOTESTER_NEXTBIPBANK_H
#define AUTOTESTER_NEXTBIPBANK_H

#include "Bank.h"

class NextBipBank
{
public:
    /**
     * Insert NextBip relationship between statement1 and statement2.
     * @param prev_prog
     * @param next_prog
     * @return Return true if the relationship is inserted successfully, otherwise false.
     */
    bool insert_next_bip(int prev_prog, int next_prog);
    /**
     * Insert Ingress & Egress prog line for Call statement
     * @param ingress_prog
     * @param egress_prog
     * @return Return true if the Ingress & Egress is inserted successfully, otherwise false.
     */
    bool insert_call_ingress_egress(int ingress_prog, int egress_prog);
    /**
     * If there is a NextBip relationship between statement1 and statement2.
     * @param prev_prog
     * @param next_prog
     * @return Return true if there is a NextBip relationship between these two statements, otherwise false.
     */
    bool is_next_bip(int prev_prog, int next_prog);
    /**
     * If there exists at least one NextBip relationship in the program.
     * @return Return true if there exists at least one NextBip relationship, otherwise false.
     */
    bool does_next_bip_exists();
    /**
     * Get all statements that are the NextBip statement of the input statement
     * @param prog_line
     * @return Return a vector of statements which are the NextBip statement of the input statement.
     */
    std::vector<int>  get_next_bip(int prog_line);
    /**
     * Get all statements that are the Previous statement of the input statement
     * @param prog_line
     * @return Return a vector of statements which are the previous statement of the input statement.
     */
    std::vector<int>  get_previous_bip(int prog_line);
    /**
     * Get all statements which are the in next position in their NextBip relationships.
     * @return Return all which are the in next position in their NextBip relationships.
     */
    std::vector<int>  get_all_next_bip();
    /**
     * Get all statements which are the in previous position in their NextBip relationships.
     * @return Return all which are the in previous position in their NextBip relationships.
     */
    std::vector<int>  get_all_previous_bip();
    /**
     * Get all NextBip relationships
     * @return Return all NextBip relationships in the program
     */
    std::unordered_map<int, std::vector<int>> get_all_next_bip_relationship();
    
private:
    Bank<int, int> next_bip_bank;
    std::unordered_map<int, int> ingress_egress_table;
};

#endif