#include "iostream"
#include "catch.hpp"
#include "ErrorMessages.h"
#include "IfParser.h"
#include "ParserInvoker.h"
#include "Statement.h"
#include "pql_dto/Entity.h"

TEST_CASE("Test if parser successfully.")
{
    std::vector<Statement> stmts;
    Statement if_statement = Statement(EntityType::IF, 1, " ");

    if_statement.set_condition("a == b");
    std::vector<Statement> then_p;
    std::vector<Statement> else_p;
    Statement then_s = Statement(EntityType::READ, 2, "read x;");
    Statement then_s2 = Statement(EntityType::CALL, 3, "call calculate;");
    Statement else_s = Statement(EntityType::PRINT, 4, "print y;");
    then_p.push_back(then_s);
    then_p.push_back(then_s2);
    else_p.push_back(else_s);
    if_statement.set_first_block(then_p);
    if_statement.set_second_block(else_p);
    PKB pkb = PKB();
    stmts.push_back(if_statement);
    ParserInvoker parserInvoker = ParserInvoker(pkb, stmts, "main");
    parserInvoker.invoke_parser();
    std::vector<int> parent = pkb.get_all_parent();
    std::vector<int> follows = pkb.get_all_follows();
    std::vector<int> followed = pkb.get_all_followed();
    std::vector<int> children = pkb.get_all_children();
    unordered_set<std::string> all_var = pkb.get_all_variables();
    int num_of_var = all_var.size();

    REQUIRE(parent.size() == 1);
    REQUIRE(num_of_var == 4);
    REQUIRE(children.size() == 3);
    REQUIRE(follows.size() == 1);
    REQUIRE(followed.size() == 1);
    bool check1 = pkb.get_statement_type(1) == EntityType::IF;
    bool check2 = pkb.get_statement_type(2) == EntityType::READ;
    bool check3 = pkb.get_statement_type(3) == EntityType::CALL;
    bool check4 = pkb.get_statement_type(4) == EntityType::PRINT;
    REQUIRE(check1);
    REQUIRE(check2);
    REQUIRE(check3);
    REQUIRE(check4);
}
