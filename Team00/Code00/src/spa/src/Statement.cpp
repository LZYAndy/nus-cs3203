#include <pql_dto/Entity.h>
#include "Statement.h"

Statement::Statement(EntityType statement_type, int prog_line, string statement)
{
    statement_type = statement_type;
    prog_line = prog_line;
    statement = statement;
}

EntityType Statement::get_statement_type()
{
    return statement_type;
}

int Statement::get_prog_line()
{
    return statement_line;
}

string Statement::get_statement()
{
    return statement;
}
