#include "ConverterUtil.h"

std::string ConverterUtil::convert_infix_prefix(std::string infix)
{
    // Check if infix expression is valid
    if (!CheckerUtil::is_expr_valid(infix)){
        throw std::runtime_error(error_messages::invalid_expr);
    }

    // Preprocess infix
    std::string processed_infix_expr = StringUtil::preprocess_expr_string(infix);

    // Split by white spaces
    std::vector<std::string> expressionVector = StringUtil::split(processed_infix_expr, ' ');

    std::stack<std::string> operatorStack;
    std::stack<std::string> operandStack;

    return std::string();
}

