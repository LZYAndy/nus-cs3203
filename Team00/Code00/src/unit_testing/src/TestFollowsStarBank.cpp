#include "catch.hpp"
#include "FollowsStarBank.h"

TEST_CASE("FollowStarBank::isfollows()")
{
    FollowsStarBank follows_star_bank;
    
    follows_star_bank.insert_follows_star(1, 2);
    follows_star_bank.insert_follows_star(1, 3);

    SECTION("is_follows_star true")
    {
        REQUIRE(follows_star_bank.is_follows_star(1, 2));
        REQUIRE(follows_star_bank.is_follows_star(1, 3));
    }

    SECTION("is_follows_star false")
    {
        REQUIRE_FALSE(follows_star_bank.is_follows_star(1, 4));
        REQUIRE_FALSE(follows_star_bank.is_follows_star(2, 3));
        REQUIRE_FALSE(follows_star_bank.is_follows_star(2, 1));
    }
}

TEST_CASE("FollowStarBank::get_follows_star()")
{
    FollowsStarBank follows_star_bank;
    
    follows_star_bank.insert_follows_star(1, 2);
    follows_star_bank.insert_follows_star(1, 3);
    follows_star_bank.insert_follows_star(5, 6);

    SECTION("empty")
    {
        REQUIRE(follows_star_bank.get_follows_star(2).empty());
        REQUIRE(follows_star_bank.get_follows_star(-1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(follows_star_bank.get_follows_star(5).size() == 1);
        REQUIRE(follows_star_bank.get_follows_star(5)[0] == 6);
    }

    SECTION("return size of >1")
    {
        REQUIRE(follows_star_bank.get_follows_star(1).size() == 2);
        std::vector<int> result = follows_star_bank.get_follows_star(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("FollowStarBank::get_followed_star_by()")
{
    FollowsStarBank follows_star_bank;
    
    follows_star_bank.insert_follows_star(1, 2);
    follows_star_bank.insert_follows_star(1, 3);
    follows_star_bank.insert_follows_star(2, 3);

    SECTION("empty")
    {
        REQUIRE(follows_star_bank.get_followed_star_by(1).empty());
        REQUIRE(follows_star_bank.get_followed_star_by(-1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(follows_star_bank.get_followed_star_by(2).size() == 1);
        REQUIRE(follows_star_bank.get_followed_star_by(2)[0] == 1);
    }

    SECTION("return size of >1")
    {
        REQUIRE(follows_star_bank.get_followed_star_by(3).size() == 2);
        std::vector<int> result = follows_star_bank.get_followed_star_by(3);
        std::vector<int> expected({2, 1});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("FollowStarBank::get_all_follows_star_relationship()")
{
    FollowsStarBank follows_star_bank;

    SECTION("empty")
    {
        REQUIRE(follows_star_bank.get_all_follows_star_relationship().empty());
    }

    follows_star_bank.insert_follows_star(1, 2);

    SECTION("return 1")
    {
        std::unordered_map<int, std::vector<int>> result = follows_star_bank.get_all_follows_star_relationship();
        std::unordered_map<int, std::vector<int>> expected({{1, std::vector<int>({2})}});
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == expected[1]);
    }

    follows_star_bank.insert_follows_star(1, 2);
    follows_star_bank.insert_follows_star(1, 3);
    follows_star_bank.insert_follows_star(1, 4);
    follows_star_bank.insert_follows_star(2, 3);
    follows_star_bank.insert_follows_star(3, 4);

    SECTION("return >1")
    {
        std::unordered_map<int, std::vector<int>> result = follows_star_bank.get_all_follows_star_relationship();
        std::vector<int> expected_vector({2, 3, 4});
        std::vector<int> result_vector = result[1];
        std::sort(result_vector.begin(), result_vector.end());
        std::sort(expected_vector.begin(), expected_vector.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result_vector == expected_vector);
    }
}

TEST_CASE("FollowStarBank::does_follows_star_exist()")
{
    FollowsStarBank follows_star_bank;

    SECTION("does not exists")
    {
        REQUIRE_FALSE(follows_star_bank.does_follows_star_exist());
    }

    SECTION("exists")
    {
        follows_star_bank.insert_follows_star(1, 2);
        follows_star_bank.insert_follows_star(1, 3);
        REQUIRE(follows_star_bank.does_follows_star_exist());
    }
}

TEST_CASE("FollowStarBank::get_all_follows_star()")
{
    FollowsStarBank follows_star_bank;

    SECTION("empty")
    {
        REQUIRE(follows_star_bank.get_all_follows_star().empty());
    }


    SECTION("return size of 1")
    {
        follows_star_bank.insert_follows_star(1, 2);
        follows_star_bank.insert_follows_star(1, 3);
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 1);
        REQUIRE(follows_star_bank.get_all_follows_star()[0] == 1);
    }

    SECTION("return size of >1")
    {
        follows_star_bank.insert_follows_star(1, 2);
        follows_star_bank.insert_follows_star(1, 3);
        follows_star_bank.insert_follows_star(2, 3);
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 2);
        std::vector<int> expected({1, 2});
        std::vector<int> result = follows_star_bank.get_all_follows_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("FollowStarBank::get_all_followed_star()")
{
    FollowsStarBank follows_star_bank;
    
    SECTION("empty")
    {
        REQUIRE(follows_star_bank.get_all_followed_star().empty());
    }


    SECTION("return size of 1")
    {
        follows_star_bank.insert_follows_star(1, 2);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 1);
        REQUIRE(follows_star_bank.get_all_followed_star()[0] == 2);
    }

    SECTION("return size of >1")
    {
        follows_star_bank.insert_follows_star(1, 2);
        follows_star_bank.insert_follows_star(1, 3);
        follows_star_bank.insert_follows_star(2, 3);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = follows_star_bank.get_all_followed_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}
