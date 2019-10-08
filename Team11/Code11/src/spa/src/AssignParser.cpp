#include "AssignParser.h"

std::regex assign_pattern("^\\s*([a-zA-Z][a-zA-Z0-9]*)\\s*=\\s*(.+)\\s*\\;$");

AssignParser::AssignParser(PKB &pkb, Statement statement, std::string parent_prog_line)
{

    std::string left = get_left(statement.get_statement()); // Valid var
    std::string right = StringUtil::trim(get_right(statement.get_statement()), " \n\t\r\f\v");
    vector<std::string> all_var = StringUtil::get_all_var(right);

    if (!regex_match(statement.get_statement(), assign_pattern))
    {
        throw std::runtime_error(error_messages::invalid_assign_statement);
    }

    if (!CheckerUtil::is_expr_valid(right))
    {
        throw std::runtime_error(error_messages::invalid_assign_statement);
    }

    if (statement.get_statement_type() != EntityType::ASSIGN)
    {
        throw std::runtime_error(error_messages::invalid_assign_type);
    }

    // Insert var
    pkb.insert_variable(left);
    for (const auto &var: all_var)
    {
        pkb.insert_variable(var);
    }

    // Insert const
    std::vector<std::string> all_const = StringUtil::get_all_const(statement.get_statement());
    for (const std::string &spa_constant : all_const)
    {
        pkb.insert_constant(spa_constant);
    }

    // Insert modifies
    pkb.insert_modifies(statement.get_prog_line(), left);
    pkb.insert_modifies(statement.get_procedure(), left);
    if (CheckerUtil::is_name_valid(parent_prog_line))
    {
        pkb.insert_modifies(parent_prog_line, left);
    }

    // Insert assigns
    pkb.insert_assign(statement.get_prog_line(), left, right);

    // Insert parents
    if (std::regex_match(parent_prog_line, std::regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    // Insert uses (if var is found at rhs)
    for (auto var: all_var)
    {
        pkb.insert_uses(statement.get_prog_line(), var);
        pkb.insert_uses(statement.get_procedure(), var);

        if (std::regex_match(parent_prog_line, std::regex("^[a-zA-Z][a-zA-Z0-9]+$")))
        {
            pkb.insert_uses(parent_prog_line, var);
        }
    }

    // Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

std::string AssignParser::get_left(std::string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(1);
    }
    return "";
}

std::string AssignParser::get_right(std::string statement)
{
    smatch match;
    if (regex_search(statement, match, assign_pattern))
    {
        return match.str(2);
    }
    return "";
}
