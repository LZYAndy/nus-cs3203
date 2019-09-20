#include <pql_dto/Entity.h>
#include "Statement.h"

Statement::Statement(EntityType statement_type, int prog_line, std::string statement)
{
    this->statement_type = statement_type;
    this->statement_line = prog_line;
    this->statement = statement;
}

EntityType Statement::get_statement_type()
{
    return statement_type;
}

int Statement::get_prog_line()
{
    return statement_line;
}

std::string Statement::get_statement()
{
    return statement;
}

std::string Statement::get_condition()
{
    return condition;
}

void Statement::set_condition(std::string condi)
{
    condition = condi;
}

std::vector<Statement> Statement::get_first_block()
{
    return first_block;
}

void Statement::set_first_block(std::vector<Statement> fb)
{
    first_block = fb;
}

std::vector<Statement> Statement::get_second_block()
{
    return second_block;
}

void Statement::set_second_block(std::vector <Statement> sb)
{
    second_block = sb;
}
