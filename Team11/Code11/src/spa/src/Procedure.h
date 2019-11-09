#ifndef AUTOTESTER_PROCEDURE_H
#define AUTOTESTER_PROCEDURE_H

#include <string>
#include "CheckerUtil.h"
#include "Statement.h"
#include "ErrorMessages.h"

class Procedure
{
private:
    std::string proc_name;
    std::string body_of_proc;
    std::vector<Statement> statement_list;

public:
    /**
     * Constructor of a Procedure.
     * @param name the name of the procedure.
     * @param body the body of the procedure.
     */
    Procedure(std::string name, std::string body);

    /**
     * The name getter.
     * @return the name of this procedure.
     */
    std::string get_name();

    /**
     * The body getter.
     * @return the body of the procedure.
     */
    std::string get_body();

    /**
     * The statement list getter, which is basically the parsed body.
     * @return A statement list.
     */
    std::vector<Statement> get_statement_list();

    /**
     * Set the statement list for this procedure.
     * @param stmt_list The statement list to be set.
     */
    void set_statement_list(std::vector<Statement> stmt_list);
};

#endif //AUTOTESTER_PROCEDURE_H
