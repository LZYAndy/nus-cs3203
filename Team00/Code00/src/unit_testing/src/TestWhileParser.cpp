#include "iostream"
#include "catch.hpp"
#include "ErrorMessages.h"
#include "WhileParser.h"
#include "Statement.h"
#include "pql_dto/Entity.h"

TEST_CASE("Test while parser successfully.")
{
    Statement while_statement = Statement(EntityType::WHILE, 1, " ");

    while_statement.set_condition("a > 0");
    std::vector<Statement> loop_p;
    Statement loop_s = Statement(EntityType::READ, 2, "read x;");
    loop_p.push_back(loop_s);

    while_statement.set_first_block(loop_p);
    PKB pkb = PKB();
    WhileParser whileParser = WhileParser(pkb, while_statement, "main");

    std::vector<int> parent = pkb.get_all_parent();
    std::vector<int> children = pkb.get_all_children();

    REQUIRE(parent.size() == 1);
    REQUIRE(children.size() == 1);
}
