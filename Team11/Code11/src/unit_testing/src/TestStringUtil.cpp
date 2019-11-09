#include "catch.hpp"
#include "StringUtil.h"

#include <string>
#include <vector>

TEST_CASE("Test split function with string delimiter.")
{
    SECTION("Split with string delimiter \"Select\"")
    {
        std::string test_string = "variable v; Select v";
        std::vector<std::string> result = StringUtil::split(test_string, "Select");
        REQUIRE(result.size() == 2);
        CHECK(result.at(0) == "variable v; ");
        CHECK(result.at(1) == " v");
    }

    SECTION("Split with string delimiter \"Select\" that does not exist")
    {
        std::string test_string = "variable v;";
        std::vector<std::string> result = StringUtil::split(test_string, "Select");
        REQUIRE(result.size() == 1);
        CHECK(result.at(0) == "variable v;");
    }
}

TEST_CASE("Test split function with space char delimiter.")
{
    SECTION("Split with char delimiter \' \'")
    {
        std::string test_string = "variable v; Select v";
        std::vector<std::string> result = StringUtil::split(test_string, ' ');
        REQUIRE(result.size() == 4);
        CHECK(result.at(0) == "variable");
        CHECK(result.at(1) == "v;");
        CHECK(result.at(2) == "Select");
        CHECK(result.at(3) == "v");
    }

    SECTION("Split with char delimiter \'o\' that does not exist")
    {
        std::string test_string = "variable v;";
        std::vector<std::string> result = StringUtil::split(test_string, 'o');
        REQUIRE(result.size() == 1);
        CHECK(result.at(0) == "variable v;");
    }
}

TEST_CASE("Test trim whitespace function.")
{
    SECTION("Remove whitespaces in string filled with whitespaces.")
    {
        std::string test_string = "     variable v; Select v   ";
        std::string result = StringUtil::trim(test_string, " \n\t\r\f\v");
        REQUIRE(result == "variable v; Select v");
    }

    SECTION("Remove character in string ending with d.")
    {
        std::string test_string = "ddddddddddddvariable v; Select vdddddddddddddd";
        std::string result = StringUtil::trim(test_string, "d");
        REQUIRE(result == "variable v; Select v");
    }
}

TEST_CASE("Test replace whitespace function with single space.")
{
    SECTION("Replace whitespaces in string filled with whitespaces with single space char.")
    {
        std::string test_string = "variable\f v;       Select\t\n v";
        std::string result = StringUtil::replace_all_white_spaces(test_string);
        REQUIRE(result == "variable v; Select v");
    }

    SECTION("Replace whitespaces in normal string with single space char.")
    {
        std::string test_string = "variable v; Select v";
        std::string result = StringUtil::replace_all_white_spaces(test_string);
        REQUIRE(result == "variable v; Select v");
    }
}

TEST_CASE("Test trim_left")
{
    std::string to_be_trim = "   left";
    std::string trimed = StringUtil::trim_left(to_be_trim);

    std::string correct_trimed = "left";
    REQUIRE(trimed == correct_trimed);
}

TEST_CASE("Test get_all_var")
{
    std::string to_extract = " ! ( a <    b12 ) || ((    c >= d   ) && !  (   e ==   f )    )";
    std::vector<std::string> result = StringUtil::get_all_var(to_extract);

    std::vector<std::string> expected({"a", "b12", "c", "d", "e", "f"});
    REQUIRE(result == expected);
}

TEST_CASE("Test get_all_const")
{
    std::string to_extract = "((((( a +20) -   12  )*16) / 9) % f ) && (( a - 1) || (6 /9 ))";
    std::vector<std::string> result = StringUtil::get_all_const(to_extract);

    std::vector<std::string> expected({"20", "12", "16", "9", "1", "6", "9"});
    REQUIRE(result == expected);
}

TEST_CASE("Test preprocess_expr_string")
{
    std::string to_process = "a+string-for*testing/pre%(a+process)";
    std::string result = StringUtil::preprocess_expr_string(to_process);
    std::string expected = "a + string - for * testing / pre % ( a + process )";
    REQUIRE(result == expected);

    std::string to_process_space = "    a     +     string  -  "
                                   "for   *     testing"
                                   "/pre   %  (    a  +  process)";
    std::string result_space = StringUtil::preprocess_expr_string(to_process_space);
    REQUIRE(result_space == expected);
}

TEST_CASE("Test removing zeros")
{
    std::string input_string = "00000000000005";
    std::string result = StringUtil::process_constant(input_string);
    std::string expected = "5";
    REQUIRE(result == expected);

    input_string = "0000050000";
    result = StringUtil::process_constant(input_string);
    expected = "50000";
    REQUIRE(result == expected);

    input_string = "000000000";
    result = StringUtil::process_constant(input_string);
    expected = "0";
    REQUIRE(result == expected);
}
