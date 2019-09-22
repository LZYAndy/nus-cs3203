#include "catch.hpp"
#include "ParentStarBank.h"

TEST_CASE("ParentStarBank::is_parent_star")
{
    ParentStarBank parent_star_bank;
    parent_star_bank.insert_parent_star(1, 2);
    parent_star_bank.insert_parent_star(1, 3);
    
    SECTION("is_parent_star true")
    {
        REQUIRE(parent_star_bank.is_parent_star(1, 2));
        REQUIRE(parent_star_bank.is_parent_star(1, 3));
    }

    SECTION("is_parent_star false")
    {
        REQUIRE_FALSE(parent_star_bank.is_parent_star(1, 4));
        REQUIRE_FALSE(parent_star_bank.is_parent_star(2, 3));
        REQUIRE_FALSE(parent_star_bank.is_parent_star(3, 1));
    }
}

TEST_CASE("ParentStarBank::get_parent_star()")
{
    ParentStarBank parent_star_bank;

    parent_star_bank.insert_parent_star(1, 2);
    parent_star_bank.insert_parent_star(2, 3);
    parent_star_bank.insert_parent_star(2, 4);
    parent_star_bank.insert_parent_star(1, 4);

    SECTION("empty")
    {
        REQUIRE(parent_star_bank.get_parent_star(-1).empty());
        REQUIRE(parent_star_bank.get_parent_star(1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(parent_star_bank.get_parent_star(2).size() == 1);
        REQUIRE(parent_star_bank.get_parent_star(2)[0] == 1);
    }

    SECTION("return size of >1")
    {
        REQUIRE(parent_star_bank.get_parent_star(4).size() == 2);
        std::vector<int> result = parent_star_bank.get_parent_star(4);
        std::vector<int> expected({1, 2});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("ParentStarBank::get_children_star()")
{
    ParentStarBank parent_star_bank;

    parent_star_bank.insert_parent_star(1, 3);
    parent_star_bank.insert_parent_star(2, 3);
    parent_star_bank.insert_parent_star(1, 4);
    parent_star_bank.insert_parent_star(1, 5);

    SECTION("empty")
    {
        REQUIRE(parent_star_bank.get_children_star(-1).empty());
        REQUIRE(parent_star_bank.get_children_star(4).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(parent_star_bank.get_children_star(2).size() == 1);
        REQUIRE(parent_star_bank.get_children_star(2)[0] == 3);
    }

    SECTION("return size of >1")
    {
        REQUIRE(parent_star_bank.get_children_star(1).size() == 3);
        std::vector<int> result = parent_star_bank.get_children_star(1);
        std::vector<int> expected({3, 4, 5});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("ParentStarBank::get_all_children_star()")
{
    ParentStarBank parent_star_bank;
    
    SECTION("empty")
    {
        REQUIRE(parent_star_bank.get_all_children_star().empty());
    }

    SECTION("return size of 1")
    {
        parent_star_bank.insert_parent_star(1, 2);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 1);
        REQUIRE(parent_star_bank.get_all_children_star() == std::vector<int>({2}));
    }

    SECTION("return size of >1, 1 parent")
    {
        parent_star_bank.insert_parent_star(1, 2);
        parent_star_bank.insert_parent_star(1, 3);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = parent_star_bank.get_all_children_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }

    SECTION("return size of >1, >1 parent")
    {
        parent_star_bank.insert_parent_star(1, 2);
        parent_star_bank.insert_parent_star(1, 4);
        parent_star_bank.insert_parent_star(2, 3);
        parent_star_bank.insert_parent_star(2, 4);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 3);
        std::vector<int> expected({2, 3, 4});
        std::vector<int> result = parent_star_bank.get_all_children_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("ParentStarBank::get_all_parent_star()")
{
    ParentStarBank parent_star_bank;
    
    SECTION("empty")
    {
        REQUIRE(parent_star_bank.get_all_parent_star().empty());
    }

    SECTION("return size of 1")
    {
        parent_star_bank.insert_parent_star(1, 2);
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 1);
        REQUIRE(parent_star_bank.get_all_parent_star() == std::vector<int>({1}));
    }

    SECTION("return size of >1")
    {
        parent_star_bank.insert_parent_star(1, 2);
        parent_star_bank.insert_parent_star(1, 4);
        parent_star_bank.insert_parent_star(2, 3);
        parent_star_bank.insert_parent_star(2, 4);
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 2);
        std::vector<int> expected({1, 2});
        std::vector<int> result = parent_star_bank.get_all_parent_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("ParentStarBank::does_parent_star_exist()")
{
    ParentStarBank parent_star_bank;

    SECTION("does not exists")
    {
        REQUIRE_FALSE(parent_star_bank.does_parent_star_exist());
    }

    SECTION("exists")
    {
        parent_star_bank.insert_parent_star(1, 2);
        REQUIRE(parent_star_bank.does_parent_star_exist());
    }
}

TEST_CASE("ParentStarBank::get_all_parent_star_relationship()")
{
    ParentStarBank parent_star_bank;

    SECTION("empty")
    {
        REQUIRE(parent_star_bank.get_all_parent_star_relationship().empty());
    }

    SECTION("return size of 1")
    {
        parent_star_bank.insert_parent_star(1, 2);
        std::unordered_map<int, std::vector<int>> result = parent_star_bank.get_all_parent_star_relationship();
        std::unordered_map<int, std::vector<int>> expected({{1, std::vector<int>({2})}});
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == expected[1]);
    }

    SECTION("return size of >1")
    {
        parent_star_bank.insert_parent_star(1, 2);
        parent_star_bank.insert_parent_star(1, 3);
        parent_star_bank.insert_parent_star(1, 4);
        parent_star_bank.insert_parent_star(2, 3);
        parent_star_bank.insert_parent_star(2, 4);
        parent_star_bank.insert_parent_star(3, 4);
        std::unordered_map<int, std::vector<int>> result = parent_star_bank.get_all_parent_star_relationship();
        REQUIRE(result.size() == 3);
        
        std::vector<int> expected_vector({2, 3, 4});
        std::vector<int> result_vector = result[1];
        std::sort(result_vector.begin(), result_vector.end());
        std::sort(expected_vector.begin(), expected_vector.end());
        REQUIRE(result_vector == expected_vector);
        
        std::vector<int> expected2_vector({3, 4});
        std::vector<int> result2_vector = result[2];
        std::sort(result2_vector.begin(), result2_vector.end());
        std::sort(expected2_vector.begin(), expected2_vector.end());
        REQUIRE(result2_vector == expected2_vector);
    }
}
