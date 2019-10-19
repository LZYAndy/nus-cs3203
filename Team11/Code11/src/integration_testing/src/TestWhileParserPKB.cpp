#include "iostream"
#include "catch.hpp"
#include "ErrorMessages.h"
#include "WhileParser.h"
#include "Statement.h"
#include "pql_dto/Entity.h"
#include "ParserInvoker.h"

TEST_CASE("Test while parser successfully.")
{
    std::vector<Statement> stmts;
    Statement while_statement = Statement(EntityType::WHILE, 1, " ");

    while_statement.set_procedure("main");

    while_statement.set_condition("( if >= (10)) && (c > d) || ((e * print) != (read % call))");
    std::vector<Statement> loop_p;
    Statement loop_s = Statement(EntityType::READ, 2, "read x;");

    loop_s.set_procedure("main");
    loop_p.push_back(loop_s);

    while_statement.set_first_block(loop_p);
    PKB pkb = PKB();
    stmts.push_back(while_statement);
    ParserInvoker parserInvoker = ParserInvoker(pkb, stmts, "main");
    parserInvoker.invoke_parser();

    std::vector<int> parent = pkb.get_all_parent();
    std::vector<int> children = pkb.get_all_children();

    REQUIRE(parent.size() == 1);
    REQUIRE(children.size() == 1);

    std::vector<std::string> modifies_procs = pkb.get_all_modifies_procedures();
    REQUIRE(modifies_procs.size() == 1);

    std::unordered_map<int, std::vector<std::string>> control_var = pkb.get_all_whilestmt_and_control_var();
    std::unordered_map<int, std::vector<std::string>> expected_control_var;
    expected_control_var.insert({1, {"if", "c", "d", "e", "print", "read", "call"}});
    REQUIRE(control_var == expected_control_var);
}
