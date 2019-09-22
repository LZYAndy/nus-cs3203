#include "catch.hpp"
#include "CheckerUtil.h"

TEST_CASE("CheckerUtil is_name_valid")
{
    REQUIRE_FALSE(CheckerUtil::is_name_valid("")); // Empty string
    REQUIRE_FALSE(CheckerUtil::is_name_valid("0a")); // First character does not start with [a-zA-Z]
    REQUIRE_FALSE(CheckerUtil::is_name_valid("a!")); // Second character not [a-zA-Z0-9]
    REQUIRE_FALSE(CheckerUtil::is_name_valid("a b")); // Space not allowed

    REQUIRE(CheckerUtil::is_name_valid("a")); // Name length of 1 (lowercase)
    REQUIRE(CheckerUtil::is_name_valid("A")); // Name length of 1 (uppercase)
    REQUIRE(CheckerUtil::is_name_valid("aa")); // Name length of 2 (lowercase)
    REQUIRE(CheckerUtil::is_name_valid("aA")); // Name length of 2 (lower and upper case)
    REQUIRE(CheckerUtil::is_name_valid("aA0")); // Name length of 3 with digits
}

TEST_CASE("CheckerUtil is_constant_valid")
{
    REQUIRE_FALSE(CheckerUtil::is_const_valid("")); // Empty string
    REQUIRE_FALSE(CheckerUtil::is_const_valid("a")); // Not digit
    REQUIRE_FALSE(CheckerUtil::is_const_valid("!")); // Not digit
    REQUIRE_FALSE(CheckerUtil::is_const_valid("123 1")); // Space not allowed
    REQUIRE_FALSE(CheckerUtil::is_const_valid("-1")); // No negative values
    REQUIRE_FALSE(CheckerUtil::is_const_valid("1.1")); // No decimal values

    REQUIRE(CheckerUtil::is_const_valid("1")); // Constant length 1
    REQUIRE(CheckerUtil::is_const_valid("10")); // Constant length 2
    REQUIRE(CheckerUtil::is_const_valid("01")); // Digits starting with 0 is valid
}

TEST_CASE("CheckerUtil is_expr_valid")
{
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a! ")); // Invalid name
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a * (( a + b )) % 5) ")); // Brackets not balanced
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a == 0 ")); // No comparator in expression
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a > 0 ")); // No comparator in expression
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a < 0 ")); // No comparator in expression
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a != 0 ")); // No comparator in expression
    REQUIRE_FALSE(CheckerUtil::is_expr_valid(" a += b ")); // No such expression

    REQUIRE(CheckerUtil::is_expr_valid(" a ")); // Single var
    REQUIRE(CheckerUtil::is_expr_valid(" a1 + bZ ")); // Var + var
    REQUIRE(CheckerUtil::is_expr_valid(" B01 + 100 ")); // Var + const
    REQUIRE(CheckerUtil::is_expr_valid(" a12 - b21 ")); // Var - var
    REQUIRE(CheckerUtil::is_expr_valid(" Q1a - 200 ")); // Var - const
    REQUIRE(CheckerUtil::is_expr_valid(" a * b ")); // Var * var
    REQUIRE(CheckerUtil::is_expr_valid(" a * 1 ")); // Var * const
    REQUIRE(CheckerUtil::is_expr_valid(" a / b ")); // Var / var
    REQUIRE(CheckerUtil::is_expr_valid(" a / 1 ")); // Var / const
    REQUIRE(CheckerUtil::is_expr_valid(" a % b ")); // Var % var
    REQUIRE(CheckerUtil::is_expr_valid(" a % 1 ")); // Var % const
    REQUIRE(CheckerUtil::is_expr_valid(" a + ((( a -   b ) * 5 )   ) / (c %  d ) "));
}

TEST_CASE("CheckerUtil is_condition_valid")
{
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a ")); // A single var is invalid for condition
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" !a ")); // Not a condition
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a + a_ ")); // Underscore is not allowed for var_name
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (a==2)) ")); // Bracket is not balanced
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a!==2 ")); // No "!==" comparator
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" abc + cde ")); // A comparator is required for condition
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (abc) & (cde) ")); // Lack of one symbol
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (abc) &&& (cde) ")); // Extra &
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (abc) |||| (cde) ")); // Extra |
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (abc) |& (cde) ")); // Invalid symbol

    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (a) && (b) ")); // Var AND var
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a && 100 ")); // Var AND const
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a || b ")); // Var OR var
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" 100 || b ")); // Const OR var
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" a+b && (b-1) ")); // Expr AND expr
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" ( a ) || b-1 ")); // Expr OR expr
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" (a + b)")); // Single expression
    REQUIRE_FALSE(CheckerUtil::is_condition_valid(" ((((( a + b ) - c ) * d) / e ) % f ) && ( a - 1 || b / 9 )")); // a-1 not wrapped in brackets

    REQUIRE(CheckerUtil::is_condition_valid(" a0 == A0Z ")); // Var compare against var
    REQUIRE(CheckerUtil::is_condition_valid(" A0z == 123 ")); // Var compare against const
    REQUIRE(CheckerUtil::is_condition_valid(" a+   0==b  /1 ")); // Comparing two expressions
    REQUIRE(CheckerUtil::is_condition_valid(" aa >      b1 ")); // Comparing greater than
    REQUIRE(CheckerUtil::is_condition_valid(" a1 < ba ")); // Comparing lesser than
    REQUIRE(CheckerUtil::is_condition_valid(" a0a >= b ")); // Comparing greater and equals than
    REQUIRE(CheckerUtil::is_condition_valid(" a <= bAz ")); // Comparing lesser and equals than
    REQUIRE(CheckerUtil::is_condition_valid(" a != 1 ")); // Not equals against a const
    REQUIRE(CheckerUtil::is_condition_valid(" ( a < b ) && (c > d)")); // Expression and expression
    REQUIRE(CheckerUtil::is_condition_valid(" ! ( a == ( a +3 )    ) ")); // Not outside of comparing var with expression
    REQUIRE(CheckerUtil::is_condition_valid(" ! ( a <    b12 ) || ((c >= d) && !  (e ==   f )    )"));
    REQUIRE(CheckerUtil::is_condition_valid(" ( a >= (b + c )) && (c > d)"));
}
