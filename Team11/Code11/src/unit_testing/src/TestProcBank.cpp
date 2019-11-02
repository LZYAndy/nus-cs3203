#include "catch.hpp"
#include "ProcBank.h"

TEST_CASE("ProcBank::insert_procedure")
{
    ProcBank proc_bank;
    SECTION("insert success")
    {
        REQUIRE(proc_bank.insert_procedure("test", 1, {3}));
        REQUIRE(proc_bank.insert_procedure("extra", 1, {2, 4}));
    }

    SECTION("insert fail")
    {
        REQUIRE(proc_bank.insert_procedure("test", 1, {3}));
        REQUIRE_FALSE(proc_bank.insert_procedure("test", 1, {3}));
    }
}

TEST_CASE("ProcBank::get_all_procedures")
{
    ProcBank proc_bank;
    SECTION("0 procedure")
    {
        REQUIRE(proc_bank.get_all_procedures().empty());
    }

    proc_bank.insert_procedure("main", 1, {3});
    proc_bank.insert_procedure("procX", 1 , {2, 4});
    proc_bank.insert_procedure("procX", 1, {3, 5} );

    SECTION("more than 0 procedure")
    {
        std::vector<std::string> result = proc_bank.get_all_procedures();
        std::vector<std::string> expected;
        expected.push_back("procX");
        expected.push_back("main");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("ProcBank::get_procedure_first_line")
{
    ProcBank proc_bank;
    SECTION("no first line")
    {
        REQUIRE(proc_bank.get_procedure_first_line("a") == -1);
    }

    proc_bank.insert_procedure("main", 1, {3});
    proc_bank.insert_procedure("procX", 6 , {2, 4});
    proc_bank.insert_procedure("procX", 1, {3, 5} );

    SECTION("return first line")
    {
        int result = proc_bank.get_procedure_first_line("main");
        REQUIRE(1 == result);
    }
}

TEST_CASE("ProcBank::get_procedure_last_lines")
{
    ProcBank proc_bank;
    SECTION("no last_lines")
    {
        REQUIRE(proc_bank.get_procedure_last_lines("a").empty());
    }

    proc_bank.insert_procedure("main", 1, {3});
    proc_bank.insert_procedure("procX", 6 , {2, 4});
    proc_bank.insert_procedure("procX", 1, {3, 5} );

    SECTION("return last_lines")
    {
        std::vector<int> result = proc_bank.get_procedure_last_lines("procX");
        std::vector<int> expected;
        expected.push_back(4);
        expected.push_back(2);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}
