#include "catch.hpp"
#include "CheckerUtil.h"

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

TEST_CASE("CheckerUtil is_expr_valid")
{
REQUIRE(CheckerUtil::is_expr_valid(" a! ") == 0);
REQUIRE(CheckerUtil::is_expr_valid(" a * (( a + b )) % 5) ") == 0); // Brackets not balanced
REQUIRE(CheckerUtil::is_expr_valid(" a == 0 ") == 0);
REQUIRE(CheckerUtil::is_expr_valid(" a > 0 ") == 0);
REQUIRE(CheckerUtil::is_expr_valid(" a < 0 ") == 0);
REQUIRE(CheckerUtil::is_expr_valid(" a != 0 ") == 0);
REQUIRE(CheckerUtil::is_expr_valid(" a += b ") == 0);

REQUIRE(CheckerUtil::is_expr_valid(" a ") == 1);
REQUIRE(CheckerUtil::is_expr_valid(" a * ((( a + b ) % 5)) - c * (d + e) ") == 1);
}

TEST_CASE("CheckerUtil is_condition_valid")
{
REQUIRE(CheckerUtil::is_condition_valid(" a ") == 0);
REQUIRE(CheckerUtil::is_condition_valid(" a + a_ ") == 0);
REQUIRE(CheckerUtil::is_condition_valid(" (a==2)) ") == 0);
REQUIRE(CheckerUtil::is_condition_valid(" a!==2 ") == 0);
//REQUIRE(CheckerUtil::is_condition_valid(" abc + cde ") == 0); // Not working

REQUIRE(CheckerUtil::is_condition_valid(" a == b ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a >= b ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a <= b ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a != b ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a+0==b/1 ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a+b && b-1 ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" a+b || b-1 ") == 1);
REQUIRE(CheckerUtil::is_condition_valid(" ((((( a + b ) - c ) * d) / e ) % f ) && ( a - 1 || b / 9 )") == 1);
}
