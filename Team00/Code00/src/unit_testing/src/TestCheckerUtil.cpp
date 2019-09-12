#include "catch.hpp"
#include "CheckerUtil.cpp"

TEST_CASE("CheckerUtil is_name_valid")
{
REQUIRE(CheckerUtil::is_name_valid("") == 0);
REQUIRE(CheckerUtil::is_name_valid("0a") == 0);
REQUIRE(CheckerUtil::is_name_valid("a!") == 0);
REQUIRE(CheckerUtil::is_name_valid("a b") == 0);

REQUIRE(CheckerUtil::is_name_valid("a") == 1);
REQUIRE(CheckerUtil::is_name_valid("A") == 1);
REQUIRE(CheckerUtil::is_name_valid("aa") == 1);
REQUIRE(CheckerUtil::is_name_valid("aA") == 1);
REQUIRE(CheckerUtil::is_name_valid("a0") == 1);
REQUIRE(CheckerUtil::is_name_valid("aaa") == 1);
}

TEST_CASE("CheckerUtil is_constant_valid")
{
REQUIRE(CheckerUtil::is_const_valid("") == 0);
REQUIRE(CheckerUtil::is_const_valid("a") == 0);
REQUIRE(CheckerUtil::is_const_valid("!") == 0);
REQUIRE(CheckerUtil::is_const_valid("123 1") == 0);
REQUIRE(CheckerUtil::is_const_valid("-1") == 0);
REQUIRE(CheckerUtil::is_const_valid("1.1") == 0);

REQUIRE(CheckerUtil::is_const_valid("1") == 1);
REQUIRE(CheckerUtil::is_const_valid("10") == 1);
REQUIRE(CheckerUtil::is_const_valid("01") == 1);
}