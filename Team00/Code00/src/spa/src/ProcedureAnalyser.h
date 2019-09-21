#ifndef AUTOTESTER_PROCEDUREANALYSER_H
#define AUTOTESTER_PROCEDUREANALYSER_H

#include <string>
#include <regex>
#include <Procedure.h>
#include "StringUtil.h"
#include "StatementListParser.h"
#include "ErrorMessages.h"

class ProcedureAnalyser
{
private:
    std::string raw_data;

public:
    // Constructor
    ProcedureAnalyser(std::string raw);

    // Find all the procedures and return as a vector of procedure.
    std::vector<Procedure> analyse();

//    Procedure parse_procedure(std::string proc_string);

//    std::string trim_left(std::string proc_string);

    static int find_bracket(std::string src, std::string opening, std::string closing);
};

#endif //AUTOTESTER_PROCEDUREANALYSER_H
