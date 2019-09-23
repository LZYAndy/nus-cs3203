#include "catch.hpp"
#include "FollowsBank.h"

TEST_CASE("FollowBank::isfollows()")
{
    FollowsBank follows_bank;
    follows_bank.insert_follows(1, 2);

    SECTION("is_follow true")
    {
        REQUIRE(follows_bank.is_follows(1,2));
    }

    SECTION("is_follow false")
    {
        REQUIRE_FALSE(follows_bank.is_follows(1, 3));
        REQUIRE_FALSE(follows_bank.is_follows(2, 3));
    }
}

TEST_CASE("FollowsBank::get_all_follows_relationship()")
{
    FollowsBank follows_bank;

    SECTION("empty")
    {
        REQUIRE(follows_bank.get_all_follows_relationship().empty());
    }

    follows_bank.insert_follows(1, 2);

    SECTION("return 1")
    {
        std::unordered_map<int, std::vector<int>> result = follows_bank.get_all_follows_relationship();
        std::unordered_map<int, std::vector<int>> expected({{1, std::vector<int>({2})}});
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == expected[1]);
    }

    follows_bank.insert_follows(2, 3);
    follows_bank.insert_follows(3, 4);
    follows_bank.insert_follows(4, 5);
    follows_bank.insert_follows(5, 6);

    SECTION("return >1")
    {
        std::unordered_map<int, std::vector<int>> result = follows_bank.get_all_follows_relationship();
        REQUIRE(result.size() == 5);
        REQUIRE(result[1] == std::vector<int>({2}));
        REQUIRE(result[2] == std::vector<int>({3}));
        REQUIRE(result[3] == std::vector<int>({4}));
        REQUIRE(result[4] == std::vector<int>({5}));
        REQUIRE(result[5] == std::vector<int>({6}));
    }
}

TEST_CASE("FollowsBank::get_all_follows()")
{
    FollowsBank follows_bank;

    SECTION("empty")
    {
        REQUIRE(follows_bank.get_all_follows().empty());
    }

    follows_bank.insert_follows(1, 2);

    SECTION("return size of 1")
    {
        REQUIRE(follows_bank.get_all_follows().size() == 1);
        REQUIRE(follows_bank.get_all_follows()[0] == 2);
    }

    follows_bank.insert_follows(2, 3);

    SECTION("return size of >1")
    {
        REQUIRE(follows_bank.get_all_follows().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = follows_bank.get_all_follows();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("FollowsBank::get_all_followed()")
{
    FollowsBank follows_bank;

    SECTION("empty")
    {
        REQUIRE(follows_bank.get_all_followed().empty());
    }

    follows_bank.insert_follows(1, 2);

    SECTION("return size of 1")
    {
        REQUIRE(follows_bank.get_all_followed().size() == 1);
        REQUIRE(follows_bank.get_all_followed()[0] == 1);
    }

    follows_bank.insert_follows(2, 3);

    SECTION("return size of >1")
    {
        REQUIRE(follows_bank.get_all_followed().size() == 2);
        std::vector<int> expected({1, 2});
        std::vector<int> result = follows_bank.get_all_followed();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("FollowsBank::get_followed_by()")
{
    FollowsBank follows_bank;
    follows_bank.insert_follows(1, 2);

    SECTION("success")
    {
        REQUIRE(follows_bank.get_followed_by(2) == 1);
    }

    SECTION("fail")
    {
        REQUIRE(follows_bank.get_followed_by(-1) == -1);
        REQUIRE(follows_bank.get_followed_by(1) == -1);
    }
}

TEST_CASE("FollowsBank::get_follows()")
{
    FollowsBank follows_bank;
    follows_bank.insert_follows(1, 2);

    SECTION("success")
    {
        REQUIRE(follows_bank.get_follows(1) == 2);
    }

    SECTION("fail")
    {
        REQUIRE(follows_bank.get_follows(-1) == -1);
        REQUIRE(follows_bank.get_follows(2) == -1);
    }
}

TEST_CASE("FollowsBank::does_follows_exists()")
{
    FollowsBank follows_bank;


    SECTION("does not exist")
    {
        REQUIRE_FALSE(follows_bank.does_follows_exists());
    }

    SECTION("exist")
    {
        follows_bank.insert_follows(1, 2);
        REQUIRE(follows_bank.does_follows_exists());
    }
}
