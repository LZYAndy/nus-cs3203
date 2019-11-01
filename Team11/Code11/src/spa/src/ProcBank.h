#ifndef AUTOTESTER_PROC_H
#define AUTOTESTER_PROC_H

#include <vector>
#include <unordered_set>

#include "Bank.h"

class ProcBank
{
public:
    /**
     * Insert a procedure into the proc_table.
     * @param name
     * @param first_prog procedure first program line
     * @param last_progs last program lines in procedure before exit procedure
     * @return Return true if the procedure is inserted successfully, otherwise false.
     */
    bool insert_procedure(std::string name, int first_prog, std::vector<int> last_progs);
    /**
     * Get all procedures in the proc_table.
     * @return Return a string unordered_set of procedures that are contained in the proc_table.
     */
    std::vector<std::string>get_all_procedures();
    /**
     * Get the first program line of the procedure
     * @param procedure quried procedure
     * @return the first program line of the procedure quried
     */
    int get_procedure_first_line(std::string procedure);
    /**
     * Get the last program lines in procedure before exit procedure
     * @param procedure quried procedure
     * @return the last program lines in procedure before exit procedure
     */
    std::vector<int> get_procedure_last_lines(std::string procedure);
private:
    Bank<std::string, int> first_line_bank;
    Bank<std::string, int> last_lines_bank;
};

#endif