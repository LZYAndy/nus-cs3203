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
    static std::string convert_infix_prefix(std::string infix);
};

#endif //AUTOTESTER_CONVERTERUTIL_H
