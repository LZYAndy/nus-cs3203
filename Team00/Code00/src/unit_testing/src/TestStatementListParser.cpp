#include "catch.hpp"
#include "StatementListParser.h"
#include "ErrorMessages.h"

TEST_CASE("Test find_semicolon.")
{
    std::string to_be_check = " print a; call main;";

    int index = StatementListParser::find_semicolon(to_be_check);
    int correct_idx = 9;

    REQUIRE(index == correct_idx);
}

TEST_CASE("Test find_semicolon. No semicolon throw error.")
{
    std::string to_be_check = " print a";

    int index = StatementListParser::find_semicolon(to_be_check);
    int correct_idx = -1;

    REQUIRE(index == correct_idx);
}

TEST_CASE("Test is_beginning_with method with (")
{
    std::string to_be_check = " ( a == b ) ";

    bool is_begin = StatementListParser::is_beginning_with(to_be_check, "(");
    bool is_not_begin = StatementListParser::is_beginning_with(to_be_check, "=");

    REQUIRE(is_begin);
    REQUIRE(!is_not_begin);
}

TEST_CASE("Test is_beginning_with method with =")
{
    std::string to_be_check = " = 0; ";

    bool is_begin = StatementListParser::is_beginning_with(to_be_check, "=");
    bool is_not_begin = StatementListParser::is_beginning_with(to_be_check, "(");

    REQUIRE(is_begin);
    REQUIRE(!is_not_begin);
}

TEST_CASE("Test Parse bracket.")
{
    std::string to_be_parse = "{ a = b; } ";
    int parsed = StatementListParser::parse_bracket(to_be_parse, "{", "}");
    int correct_parsed = 10;

    REQUIRE(parsed == correct_parsed);
}

TEST_CASE("Test parse_if method successful.")
{
    std::string stmt_to_parse = " if (a == b) then { a = 10; } else { b = 10;} c = 10; ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_if(stmt_to_parse);
    std::string correct_rest = "c = 10; ";
    std::vector<Statement> list_stmt = statementListParser.get_stmt_list();
    Statement this_stmt = list_stmt[0];
    std::string condition = this_stmt.get_condition();

    REQUIRE(rest == correct_rest);
    REQUIRE(condition == "a == b");
    REQUIRE(this_stmt.get_statement_type() == EntityType::IF);
}

TEST_CASE("Test parse_if method unsuccessful.")
{
    std::string stmt_to_parse = " if (a == b) { a = 10; } else { b = 10;} c = 10; ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_if(stmt_to_parse), error_messages::invalid_if_statement);
}

TEST_CASE("Test parse_while method successful.")
{
    std::string stmt_to_parse = " while ( a > 0) { a = a - 1; }  b = 10;  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_while(stmt_to_parse);
    std::string correct_rest = "b = 10;  ";
    REQUIRE(rest == correct_rest);
}

TEST_CASE("Test parse_while method unsuccessful.")
{
    std::string stmt_to_parse = " while ( a > 0) then { a = a - 1; }  b = 10;  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_while(stmt_to_parse), error_messages::invalid_while_statement);
}

TEST_CASE("Test parse_read method successful.")
{
    std::string stmt_to_parse = "  read a; call b; ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_read(stmt_to_parse);
    std::string correct_rest = "call b; ";
    REQUIRE(rest == correct_rest);
}

TEST_CASE("Test parse_read method unsuccessful.")
{
    std::string stmt_to_parse = "  read a  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_read(stmt_to_parse), error_messages::invalid_read_statement);
}

TEST_CASE("Test parse_print method successful.")
{
    std::string stmt_to_parse = "  print a; call b; ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_print(stmt_to_parse);
    std::string correct_rest = "call b; ";
    REQUIRE(rest == correct_rest);
}

TEST_CASE("Test parse_print method unsuccessful.")
{
    std::string stmt_to_parse = "  print a  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_print(stmt_to_parse), error_messages::invalid_print_statement);
}

TEST_CASE("Test parse_call method successful.")
{
    std::string stmt_to_parse = "  call a; call b; ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_call(stmt_to_parse);
    std::string correct_rest = "call b; ";
    REQUIRE(rest == correct_rest);
}

TEST_CASE("Test parse_call method unsuccessful.")
{
    std::string stmt_to_parse = "  call a  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_call(stmt_to_parse), error_messages::invalid_call_statement);
}

TEST_CASE("Test parse_assign method successful.")
{
    std::string stmt_to_parse = "  a = a + 1; call b;   ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    std::string rest = statementListParser.parse_assign(stmt_to_parse);
    std::string correct_rest = "call b;   ";
    REQUIRE(rest == correct_rest);
}

TEST_CASE("Test parse_assign method unsuccessful.")
{
    std::string stmt_to_parse = "  a = a + 1";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_assign(stmt_to_parse), error_messages::invalid_assign_statement);
}

TEST_CASE("Test parse_statement method successful.")
{
    std::string stmt_to_parse = "  x = x + 1; while (a > b) { read x; } if (x > 1) then { a = 100; } else { b = 100;} call main; print y;  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    statementListParser.parse_stmt_list();
    std::vector<Statement> list_of_stmt = statementListParser.get_stmt_list();
    int num_of_stmt = list_of_stmt.size();
    int prog_num_1 = list_of_stmt[0].get_prog_line();
    int prog_num_2 = list_of_stmt[1].get_prog_line();
    int prog_num_3 = list_of_stmt[2].get_prog_line();
    int prog_num_4 = list_of_stmt[3].get_prog_line();
    int prog_num_5 = list_of_stmt[4].get_prog_line();

    REQUIRE(num_of_stmt == 5);
    REQUIRE(prog_num_1 == 1);
    REQUIRE(prog_num_2 == 2);
    REQUIRE(prog_num_3 == 4);
    REQUIRE(prog_num_4 == 7);
    REQUIRE(prog_num_5 == 8);

    REQUIRE(list_of_stmt[0].get_statement_type() == EntityType::ASSIGN);
    REQUIRE(list_of_stmt[1].get_statement_type() == EntityType::WHILE);
    REQUIRE(list_of_stmt[2].get_statement_type() == EntityType::IF);
    REQUIRE(list_of_stmt[3].get_statement_type() == EntityType::CALL);
    REQUIRE(list_of_stmt[4].get_statement_type() == EntityType::PRINT);
}

TEST_CASE("Test parse_statement method unsuccessful.")
{
    std::string stmt_to_parse = "  x = x + 1; while (a > b) { read x; } if (x > 1) { a = 100; } else { b = 100;} call main; print y;  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    REQUIRE_THROWS(statementListParser.parse_stmt_list(), error_messages::invalid_if_statement);
}

TEST_CASE("Test parse_statement method successful with nested while loop.")
{
    std::string stmt_to_parse = " while (a > b) { while (x > y) { call p;  print x; } read x; }  ";
    StatementListParser statementListParser = StatementListParser(stmt_to_parse, 0);

    statementListParser.parse_stmt_list();
    std::vector<Statement> list_of_stmt = statementListParser.get_stmt_list();
    int num_of_stmt = list_of_stmt.size();
    Statement stmt_1 = list_of_stmt[0];
    Statement stmt_2 = list_of_stmt[0].get_first_block()[0];
    Statement stmt_3 = list_of_stmt[0].get_first_block()[0].get_first_block()[0];
    Statement stmt_4 = list_of_stmt[0].get_first_block()[0].get_first_block()[1];
    Statement stmt_5 = list_of_stmt[0].get_first_block()[1];
    int prog_num_1 = stmt_1.get_prog_line();
    int prog_num_2 = stmt_2.get_prog_line();
    int prog_num_3 = stmt_3.get_prog_line();
    int prog_num_4 = stmt_4.get_prog_line();
    int prog_num_5 = stmt_5.get_prog_line();

    REQUIRE(num_of_stmt == 1);
    REQUIRE(prog_num_1 == 1);
    REQUIRE(prog_num_2 == 2);
    REQUIRE(prog_num_3 == 3);
    REQUIRE(prog_num_4 == 4);
    REQUIRE(prog_num_5 == 5);

    REQUIRE(stmt_1.get_statement_type() == EntityType::WHILE);
    REQUIRE(stmt_2.get_statement_type() == EntityType::WHILE);
    REQUIRE(stmt_3.get_statement_type() == EntityType::CALL);
    REQUIRE(stmt_4.get_statement_type() == EntityType::PRINT);
    REQUIRE(stmt_5.get_statement_type() == EntityType::READ);
}