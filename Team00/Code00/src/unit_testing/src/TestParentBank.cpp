#include "catch.hpp"
#include "ParentBank.h"

TEST_CASE("ParentBank::is_parent()")
{
    ParentBank parent_bank;
    parent_bank.insert_parent(1, 2);

    SECTION("is_parent true")
    {
        REQUIRE(parent_bank.is_parent(1, 2));
    }

    SECTION("is_parent false")
    {
        REQUIRE_FALSE(parent_bank.is_parent(1, 3));
        REQUIRE_FALSE(parent_bank.is_parent(2, 1));
    }
}

TEST_CASE("ParentBank::get_all_parent_relationship()")
{
    ParentBank parent_bank;

    SECTION("empty")
    {
        REQUIRE(parent_bank.get_all_parent_relationship().empty());
    }

    parent_bank.insert_parent(1, 2);

    SECTION("return 1")
    {
        std::unordered_map<int, std::vector<int>> result = parent_bank.get_all_parent_relationship();
        std::unordered_map<int, std::vector<int>> expected({{1, std::vector<int>({2})}});
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == expected[1]);
    }

    parent_bank.insert_parent(1, 3);
    parent_bank.insert_parent(1, 4);
    parent_bank.insert_parent(1, 5);
    parent_bank.insert_parent(3, 6);

    SECTION("return >1")
    {
        std::unordered_map<int, std::vector<int>> result = parent_bank.get_all_parent_relationship();
        std::vector<int> expected_vector({2, 3, 4, 5});
        std::vector<int> result_vector = result[1];
        std::sort(result_vector.begin(), result_vector.end());
        std::sort(expected_vector.begin(), expected_vector.end());
        REQUIRE(result.size() == 2);
        REQUIRE(result_vector == expected_vector);
    }
}

TEST_CASE("ParentBank::get_children()")
{
    ParentBank parent_bank;

    SECTION("empty")
    {
        REQUIRE(parent_bank.get_children(-1).empty());
        REQUIRE(parent_bank.get_children(2).empty());
    }

    parent_bank.insert_parent(1, 2);

    SECTION("return children of size 1")
    {
        REQUIRE(parent_bank.get_children(1).size() == 1);
        REQUIRE(parent_bank.get_children(1)[0] == 2);
    }

    SECTION("return children of size >1")
    {
        parent_bank.insert_parent(1, 3);
        parent_bank.insert_parent(2, 4);
        REQUIRE(parent_bank.get_children(1).size() == 2);
        REQUIRE(parent_bank.get_children(1) == std::vector<int>({2, 3}));
        REQUIRE(parent_bank.get_children(2) == std::vector<int>({4}));
    }
}

TEST_CASE("ParentBank::get_parent()")
{
    ParentBank parent_bank;
    parent_bank.insert_parent(1, 2);
    parent_bank.insert_parent(1, 3);

    SECTION("success")
    {
        REQUIRE(parent_bank.get_parent(2) == 1);
        REQUIRE(parent_bank.get_parent(3) == 1);
    }

    SECTION("fail")
    {
        REQUIRE(parent_bank.get_parent(-1) == -1);
        REQUIRE(parent_bank.get_parent(1) == -1);
    }
}

TEST_CASE("ParentBank::does_parent_exist()")
{
    ParentBank parent_bank;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(parent_bank.does_parent_exist());
    }

    SECTION("exist")
    {
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.does_parent_exist());
    }
}

TEST_CASE("ParentBank::get_all_children()")
{
    ParentBank parent_bank;

    SECTION("empty")
    {
        REQUIRE(parent_bank.get_all_children().empty());
    }

    SECTION("return size of 1")
    {
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.get_all_children().size() == 1);
        REQUIRE(parent_bank.get_all_children() == std::vector<int>({2}));
    }

    SECTION("return size of >1, 1 parent")
    {
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(1, 3);
        REQUIRE(parent_bank.get_all_children().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = parent_bank.get_all_children();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }

    SECTION("return size of >1, >1 parent")
    {
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(1, 4);
        parent_bank.insert_parent(2, 3);
        REQUIRE(parent_bank.get_all_children().size() == 3);
        std::vector<int> expected({2, 3, 4});
        std::vector<int> result = parent_bank.get_all_children();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("ParentBank::get_all_parent()")
{
    ParentBank parent_bank;

    SECTION("empty")
    {
        REQUIRE(parent_bank.get_all_parent().empty());
    }

    SECTION("return size of 1")
    {
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.get_all_parent().size() == 1);
        REQUIRE(parent_bank.get_all_parent() == std::vector<int>({1}));
    }

    SECTION("return size of >1")
    {
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(2, 3);
        REQUIRE(parent_bank.get_all_parent().size() == 2);
        std::vector<int> expected({2, 1});
        std::vector<int> result = parent_bank.get_all_parent();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}
