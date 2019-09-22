#include "catch.hpp"
#include "ErrorMessages.h"
#include "IfParser.h"
#include "Statement.h"
#include "pql_dto/Entity.h"

TEST_CASE("Test if parser successfully.")
{
    Statement if_statement = Statement(EntityType::IF, 1, " ");

    if_statement.set_condition("a == b");
    std::vector<Statement> then_p;
    std::vector<Statement> else_p;
    Statement then_s = Statement(EntityType::READ, 2, "read x;");
    Statement else_s = Statement(EntityType::PRINT, 3, "print y;");
    then_p.push_back(then_s);
    else_p.push_back(else_s);
    if_statement.set_first_block(then_p);
    if_statement.set_second_block(else_p);
    PKB pkb = PKB();
    IfParser ifParser = IfParser(pkb, if_statement, "main");
    std::vector<int> parent = pkb.get_all_parent();
    std::vector<int> children = pkb.get_all_children();

    REQUIRE(parent.size() == 1);
    REQUIRE(children.size() == 2);
}
