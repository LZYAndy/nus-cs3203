#ifndef AUTOTESTER_PROCEDURE_H
#define AUTOTESTER_PROCEDURE_H

#include <string>
#include "CheckerUtil.h"
#include "ErrorMessages.h"

class Procedure
{
private:
    std::string proc_name;
    std::string body_of_proc;

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
};

#endif //AUTOTESTER_PROCEDURE_H
