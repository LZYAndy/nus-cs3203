#include "iostream"
#include "catch.hpp"
#include "ErrorMessages.h"
#include "ParserInvoker.h"
#include "Statement.h"
#include "pql_dto/Entity.h"

TEST_CASE("Test ParserInvoker successfully.")
{
    std::vector<Statement> stmt_list;

    // Create if statement.
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

    // Create while statement.
    Statement while_statement = Statement(EntityType::WHILE, 4, " ");

    while_statement.set_condition("a > 0");
    std::vector<Statement> loop_p;
    Statement loop_s = Statement(EntityType::READ, 5, "read x;");
    loop_p.push_back(loop_s);

    while_statement.set_first_block(loop_p);

    // Create call statement.
    Statement call_statement = Statement(EntityType::CALL, 6, "call p;");

    // Create print statement.
    Statement print_statement = Statement(EntityType::PRINT, 7, "print x;");

    // Create read statement.
    Statement read_statement = Statement(EntityType::READ, 8, "read y;");

    // Create assign statement.
    Statement assign_statement = Statement(EntityType::ASSIGN, 9, "x = x + 1;");

    PKB pkb = PKB();

    stmt_list.push_back(if_statement);
    stmt_list.push_back(while_statement);
    stmt_list.push_back(call_statement);
    stmt_list.push_back(print_statement);
    stmt_list.push_back(read_statement);
    stmt_list.push_back(assign_statement);

    ParserInvoker parserInvoker = ParserInvoker(reinterpret_cast<PKB &>(pkb), stmt_list, "main");
    parserInvoker.invoke_parser();

    std::vector<int> follows = pkb.get_all_follows();
    std::vector<int> followed = pkb.get_all_followed();
    std::vector<int> reads = pkb.get_all_reads();
    std::vector<int> prints = pkb.get_all_prints();
    std::vector<int> calls = pkb.get_all_calls();
    std::vector<int> assigns = pkb.get_all_assigns();

    REQUIRE(follows.size() == 5);
    REQUIRE(followed.size() == 5);
    REQUIRE(reads.size() == 3);
    REQUIRE(reads[0] == 2);
    REQUIRE(reads[1] == 5);
    REQUIRE(reads[2] == 8);
    REQUIRE(prints.size() == 2);
    REQUIRE(prints[0] == 3);
    REQUIRE(prints[1] == 7);
    REQUIRE(calls.size() == 1);
    REQUIRE(calls[0] == 6);
    REQUIRE(assigns.size() == 1);
    REQUIRE(assigns[0] == 9);
}
