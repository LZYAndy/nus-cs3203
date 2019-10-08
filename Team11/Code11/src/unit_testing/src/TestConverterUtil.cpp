#include "catch.hpp"
#include "ConverterUtil.h"

TEST_CASE("convert_infix_prefix - 1v")
{
    std::string result = ConverterUtil::convert_infix_prefix("  a  ");
    std::string expected = "a";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - 2v, 1o")
{
    std::string result = ConverterUtil::convert_infix_prefix("  first  +  second  ");
    std::string expected = "+ first second";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - 3v, 2o, check priority")
{
    std::string result = ConverterUtil::convert_infix_prefix("  first  +  second  * third  ");
    std::string expected = "+ first * second third";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - 3v, 2o, check priority with parenthesis")
{
    std::string result = ConverterUtil::convert_infix_prefix("  (first  +  second)  * third  ");
    std::string expected = "* + first second third";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - similar naming")
{
    std::string result = ConverterUtil::convert_infix_prefix("aa + a + aa");
    std::string expected = "+ + aa a aa";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - all operators")
{
    std::string result = ConverterUtil::convert_infix_prefix("first+second-third*fourth/fifth%sixth");
    std::string expected = "- + first second % / * third fourth fifth sixth";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - all operators w integers")
{
    std::string result = ConverterUtil::convert_infix_prefix("first+20-third*fourth/50%sixth");
    std::string expected = "- + first 20 % / * third fourth 50 sixth";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - all operators w parenthesis")
{
    std::string result = ConverterUtil::convert_infix_prefix("(first+(second-third))*fourth/fifth%sixth");
    std::string expected = "% / * + first - second third fourth fifth sixth";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - all operators w integers and parenthesis")
{
    std::string result = ConverterUtil::convert_infix_prefix("(first+20)-third*(fourth/(50%sixth))");
    std::string expected = "- + first 20 * third / fourth % 50 sixth";
    REQUIRE(result == expected);
}

TEST_CASE("convert_infix_prefix - all operators w integers and parenthesis, shifted order")
{
    std::string result = ConverterUtil::convert_infix_prefix("((first)+(20))/((third*fourth)-50)%sixth");
    std::string expected = "% / + first 20 - * third fourth 50 sixth";
    REQUIRE(result == expected);
}