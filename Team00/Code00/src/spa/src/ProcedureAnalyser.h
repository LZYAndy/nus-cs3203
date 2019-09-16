#ifndef AUTOTESTER_PROCEDUREANALYSER_H
#define AUTOTESTER_PROCEDUREANALYSER_H

#include <string>
#include <regex>
#include <Procedure.h>

class ProcedureAnalyser
{
private:
    std::string raw_data;

public:
    // Constructor
    ProcedureAnalyser(std::string raw);

    // Find all the procedures and return as a vector of procedure.
    std::vector<Procedure> analyse();

    Procedure parse_procedure(std::string proc_string);

    std::string trim_left(std::string proc_string);
};

#endif //AUTOTESTER_PROCEDUREANALYSER_H
