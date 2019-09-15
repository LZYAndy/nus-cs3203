#ifndef AUTOTESTER_PROCEDURE_H
#define AUTOTESTER_PROCEDURE_H

class Procedure
{
private:
    std::string proc_name;
    std::string body_of_proc;

public:
    // Constructor
    Procedure(std::string name, std::string body);

    std::string get_name();
    std::string get_body();
};

#endif //AUTOTESTER_PROCEDURE_H
