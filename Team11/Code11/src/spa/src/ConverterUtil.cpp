#include "ConverterUtil.h"

std::string ConverterUtil::convert_infix_prefix(std::string infix)
{
    // Check if infix expression is valid
    if (!CheckerUtil::is_expr_valid(infix))
    {
        throw std::runtime_error(error_messages::invalid_expr);
    }

    // Preprocess infix
    std::string processed_infix_expr = StringUtil::preprocess_expr_string(infix);

    // Split by white spaces
    std::vector<std::string> elements = StringUtil::split(processed_infix_expr, ' ');

    std::stack<std::string> operator_stack;
    std::stack<std::string> operand_stack;

    for (auto & element : elements)
    {
        // Opening of parenthesis
        if (element == "(")
        {
            operator_stack.push(element);
        }

        // If close parenthesis, continuously pop the operand stack until we get back the first opening bracket
        else if (element == ")")
        {
            while (!operator_stack.empty() && operator_stack.top() != "(")
            {
                std::string older_operand = operand_stack.top();
                operand_stack.pop();

                std::string newer_operand = operand_stack.top();
                operand_stack.pop();

                std::string spa_operator = operator_stack.top();
                operator_stack.pop();

                // Treat subexpression as operand and push it into operand_stack
                std::string sub_expr;
                sub_expr.append(spa_operator);
                sub_expr.append(" ");
                sub_expr.append(newer_operand);
                sub_expr.append(" ");
                sub_expr.append(older_operand);

                operand_stack.push(sub_expr);
            }

            // Pop the opening parenthesis
            operator_stack.pop();
        }

        // If operand, push it into operand_stack
        else if (!is_operator(element[0]))
        {
            operand_stack.push(element);
        }

        // If operator, check for priority then push to operator_stack
        else
        {
            while ((!operator_stack.empty()) && (get_opr_priority(element) <= get_opr_priority(operator_stack.top())))
            {
                std::string older_operand = operand_stack.top();
                operand_stack.pop();

                std::string newer_operand = operand_stack.top();
                operand_stack.pop();

                std::string spa_operator = operator_stack.top();
                operator_stack.pop();

                // Treat subexpression as operand and push it into operand_stack
                std::string sub_expr;
                sub_expr.append(spa_operator);
                sub_expr.append(" ");
                sub_expr.append(newer_operand);
                sub_expr.append(" ");
                sub_expr.append(older_operand);

                operand_stack.push(sub_expr);
            }
            operator_stack.push(element);
        }
    }

    while (!operator_stack.empty())
    {
        std::string older_operand = operand_stack.top();
        operand_stack.pop();

        std::string newer_operand = operand_stack.top();
        operand_stack.pop();

        std::string spa_operator = operator_stack.top();
        operator_stack.pop();

        // Treat subexpression as operand and push it into operand_stack
        std::string sub_expr;
        sub_expr.append(spa_operator);
        sub_expr.append(" ");
        sub_expr.append(newer_operand);
        sub_expr.append(" ");
        sub_expr.append(older_operand);

        operand_stack.push(sub_expr);
    }

    return operand_stack.top();
}

bool ConverterUtil::is_operator(char input)
{
    return (!isalpha(input) && !isdigit(input));
}

int ConverterUtil::get_opr_priority(std::string input)
{
    char current_char = input[0];
    if (current_char == '-' || current_char == '+')
    {
        return 1;
    }
    else if (current_char == '*' || current_char == '/' || current_char == '%')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}
