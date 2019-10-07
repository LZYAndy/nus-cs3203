#pragma once
#ifndef AUTOTESTER_CONVERTERUTIL_H
#define AUTOTESTER_CONVERTERUTIL_H

#include <stack>
#include <string>
#include "CheckerUtil.h"
#include "ErrorMessages.h"
#include "StringUtil.h"

class ConverterUtil
{
public:
    /**
     * Converts an infix expression into an prefix expression
     * @param infix
     * @return Returns the expression in prefix form.
     */
    static std::string convert_infix_prefix(std::string infix);

private:
    /**
     * Obtains the priority of an operator. The higher the value, the more priority it has.
     * @param input
     * @return Returns the priority of an operator.
     */
    static int get_opr_priority(std::string input);

    /**
     * Checks if an character is a valid operator.
     * @param input
     * @return Returns true if the input is valid and false otherwise.
     */
    static bool is_operator(char input);
};

#endif //AUTOTESTER_CONVERTERUTIL_H
