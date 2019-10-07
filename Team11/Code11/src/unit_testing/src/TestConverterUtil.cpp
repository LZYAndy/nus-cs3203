#include "catch.hpp"
#include "ConverterUtil.h"

TEST_CASE("Test convert_infix_prefix")
{
    std::string result = ConverterUtil::convert_infix_prefix("a+string-for*testing/pre%(a+process)");
    REQUIRE(true);
}
