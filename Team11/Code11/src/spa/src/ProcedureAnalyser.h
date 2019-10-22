#ifndef AUTOTESTER_PROCEDUREANALYSER_H
#define AUTOTESTER_PROCEDUREANALYSER_H

#include <string>
#include <regex>
#include "Procedure.h"
#include "StringUtil.h"
#include "StatementListParser.h"
#include "ErrorMessages.h"

class ProcedureAnalyser
{
private:
    std::string raw_data;

public:
    /**
     * The constructor of the ProcedureAnalyser.
     * @param raw The raw string to be parsed into procedures.
     */
    ProcedureAnalyser(std::string raw);

    /**
     * Parse the raw data, find all the procedures and return as a vector of procedures.
     * @return a vector of procedures.
     */
    std::vector<Procedure> analyse();

    /**
     * The find the closing brackets of the opening brackets which is the first non-space character of the string.
     * @param src the source string.
     * @param opening the opening bracket, which is also the first non-space character.
     * @param closing the closing bracket to be found.
     * @return the index of the closing bracket.
     */
    static int find_bracket(std::string src, std::string opening, std::string closing);
};

#endif //AUTOTESTER_PROCEDUREANALYSER_H
