#ifndef AUTOTESTER_PROCEDURE_H
#define AUTOTESTER_PROCEDURE_H

#include <string>

using namespace std;

class Procedure
{
private:
    string proc_name;
    string body_of_proc;

public:
    // Constructor
    Procedure(string name, string body);

    string get_name();
    string get_body();
};

#endif //AUTOTESTER_PROCEDURE_H
