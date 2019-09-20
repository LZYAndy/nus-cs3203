#include "catch.hpp"
#include "Procedure.h"
#include "ErrorMessages.h"

TEST_CASE("Set valid procedure name.")
{
    Procedure proc = Procedure("proc_name", "this_is_body");

    std::string correct_name = "proc_name";
    std::string got_name = proc.get_name();

    REQUIRE(correct_name == got_name);
}

TEST_CASE("Set non-empty procedure body.")
{
    Procedure proc = Procedure("proc_name", "this_is_body");

    std::string correct_body = "this_is_body";
    std::string got_body = proc.get_body();

    REQUIRE(correct_body == got_body);
}

TEST_CASE("Set empty procedure body is still valid.")
{
    Procedure proc = Procedure("proc_name", "");

    std::string correct_body = "";
    std::string got_body = proc.get_body();

    REQUIRE(correct_body == got_body);
}

TEST_CASE("Set invalid procedure name should throw error.")
{
    REQUIRE_THROWS(Procedure("1main", "this_is_body"), error_messages::invalid_proc_name);
}
