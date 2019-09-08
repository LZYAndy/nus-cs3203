#include "catch.hpp"
#include "Bank.h"
#include "Bank.cpp"

TEST_CASE("Bank<int, int> Test")
{
    Bank<int, int> bank;
    bank.put(1, 2);
    int popped_value = bank.get(1).at(0);
    REQUIRE(popped_value == 2);

    int popped_key = bank.get_reverse(2).at(0);
    REQUIRE(popped_key == 1);
}
