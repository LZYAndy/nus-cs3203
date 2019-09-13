#ifndef AUTOTESTER_PROCEDUREANALYSER_H
#define AUTOTESTER_PROCEDUREANALYSER_H

#include <string>
#include <regex>
#include <Procedure.h>

using namespace std;

class ProcedureAnalyser{
private:
    string rawData;
    vector<string> listOfProc;
public:
    // Constructor
    ProcedureAnalyser(string raw);

    // Find all the procedures and return as a vector of procedure.
    vector<string> analyse();

    Procedure parse_procedure(string proc_string);

    string trim_left(string proc_string);
};

#endif //AUTOTESTER_PROCEDUREANALYSER_H
