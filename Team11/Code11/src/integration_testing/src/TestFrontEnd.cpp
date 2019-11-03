#include "catch.hpp"
#include "PKB.h"
#include "Parser.h"

using namespace std;

TEST_CASE("Valid SIMPLE code")
{
    std::string simple_code = "procedure computeSeq {\nfirst = 1;\nd = 7;\nread b;\ncount = 0;\nread first;\nd = a;\nif (d > limit) then{\nwhile (count < limit) {\np = first; \nx = first; \nfirst = p; \ncount = count; \n} }\nelse { \nx = 4; \n }\nprint x;\n}";

    PKB pkb = PKB();
    Parser parser = Parser(&pkb);

    parser.parse(simple_code);

    SECTION("Check insertion of last statement")
    {
        Statement if_stmt = Statement(EntityType::IF, 1, "");
        Statement call_stmt = Statement(EntityType::CALL, 2, "call calculate;");
        Statement read_stmt = Statement(EntityType::READ, 3, "read x;");
        Statement print_stmt = Statement(EntityType::PRINT, 4, "print x;");
        Statement assign_stmt = Statement(EntityType::ASSIGN, 5, "x = x + 1;");
        std::vector<Statement> then_p;
        std::vector<Statement> else_p;
        then_p.push_back(call_stmt);
        then_p.push_back(read_stmt);
        else_p.push_back(print_stmt);
        else_p.push_back(assign_stmt);
        if_stmt.set_first_block(then_p);
        if_stmt.set_second_block(else_p);
        std::vector<int> re = parser.get_last_statements(if_stmt);
        REQUIRE(re.size() == 2);
    }

    SECTION("Check Statement Table")
    {
        std::vector<int> stmt_list = pkb.get_all_statement_nums();
        std::vector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
        std::sort(stmt_list.begin(), stmt_list.end());
        std::sort(expected_result.begin(), expected_result.end());
        REQUIRE(stmt_list == expected_result);
    }

    SECTION("Check Assign Table")
    {
        std::vector<int> assign_list = pkb.get_all_assigns();
        std::vector<int> expected_result = { 1, 2, 4, 6, 9, 10, 11, 12, 13 };
        std::sort(assign_list.begin(), assign_list.end());
        std::sort(expected_result.begin(), expected_result.end());
        REQUIRE(assign_list == expected_result);
    }

    SECTION("Check Variables Table")
    {
        std::unordered_set<std::string> assign_list = pkb.get_all_variables();
        std::unordered_set<std::string> expected_result = { "first", "d", "b",
                                                            "count", "first", "a", "limit", "p", "x"
                                                          };

        REQUIRE(assign_list == expected_result);
    }

    SECTION("Check Constant Table")
    {
        std::vector<std::string> constant_list = pkb.get_all_constants();
        std::vector<std::string> expected_result = {"1", "7", "0", "4" };
        std::sort(constant_list.begin(), constant_list.end());
        std::sort(expected_result.begin(), expected_result.end());

        REQUIRE(constant_list == expected_result);
    }

    SECTION("Check Proc Table")
    {
        std::unordered_set<std::string> procedure_list = pkb.get_all_procedures();
        std::unordered_set<std::string> expected_result = { "computeSeq" };

        REQUIRE(procedure_list == expected_result);
    }

    SECTION("Check Modifies Table")
    {
        std::vector<int> modifies_list = pkb.get_all_modifies_statements();
        std::vector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        std::sort(modifies_list.begin(), modifies_list.end());
        std::sort(expected_result.begin(), expected_result.end());

        REQUIRE(modifies_list == expected_result);
    }

    SECTION("Check Uses Table")
    {
        std::vector<int> uses_list = pkb.get_all_uses_statements();
        std::vector<int> expected_result = { 14, 12, 6, 7, 8, 9, 10, 11 };
        std::sort(uses_list.begin(), uses_list.end());
        std::sort(expected_result.begin(), expected_result.end());

        REQUIRE(uses_list == expected_result);
    }
}

