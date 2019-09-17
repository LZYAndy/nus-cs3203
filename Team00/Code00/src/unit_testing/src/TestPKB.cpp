#include "catch.hpp"
#include "PKB.h"

TEST_CASE("PKB::insert_procedure()")
{
    PKB pkb;
    
    SECTION("insert success")
    {
        REQUIRE(pkb.insert_procedure("test"));
        REQUIRE(pkb.insert_procedure("extra"));
    }

    SECTION("insert fail")
    {
        REQUIRE(pkb.insert_procedure("test"));
        REQUIRE_FALSE(pkb.insert_procedure("test"));
    }
}

TEST_CASE("PKB::insert_variable()")
{
    PKB pkb;

    SECTION("insert success")
    {
        REQUIRE(pkb.insert_variable("test"));
        REQUIRE(pkb.insert_variable("extra"));
    }

    SECTION("insert fail")
    {
        REQUIRE(pkb.insert_variable("test"));
        REQUIRE_FALSE(pkb.insert_variable("test"));
    }    
}

TEST_CASE("PKB::get_statement_type()")
{
    PKB pkb;
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(3, EntityType::IF);
    pkb.insert_type(4, EntityType::PRINT);
    pkb.insert_type(5, EntityType::READ);
    pkb.insert_type(6, EntityType::WHILE);
    
    REQUIRE(pkb.get_statement_type(1) == EntityType::ASSIGN);
    REQUIRE(pkb.get_statement_type(2) == EntityType::CALL);
    REQUIRE(pkb.get_statement_type(3) == EntityType::IF);
    REQUIRE(pkb.get_statement_type(4) == EntityType::PRINT);
    REQUIRE(pkb.get_statement_type(5) == EntityType::READ);
    REQUIRE(pkb.get_statement_type(6) == EntityType::WHILE);
    REQUIRE(pkb.get_statement_type(-1) == EntityType::INVALID);
    REQUIRE(pkb.get_statement_type(7) == EntityType::INVALID);

}

TEST_CASE("PKB::get_all_statement_nums()")
{
    PKB pkb;
    SECTION("0 stmt")
    {
        REQUIRE(pkb.get_all_statement_nums().empty());
    }

    SECTION(">1 stmt")
    {
        pkb.insert_type(1, EntityType::PRINT);
        pkb.insert_type(2, EntityType::PRINT);
        REQUIRE(pkb.get_all_statement_nums().size() == 1);
    }

}

TEST_CASE("PKB::insert_follows()")
{
    PKB pkb;
    
    SECTION("insert success")
    {
        REQUIRE(pkb.insert_follows(1, 2));
    }

    SECTION("insert fail")
    {
        REQUIRE_FALSE(pkb.insert_follows(1, 1));
        REQUIRE_FALSE(pkb.insert_follows(1, 0));
        REQUIRE_FALSE(pkb.insert_follows(2, 1));

        // double insert
        pkb.insert_follows(1, 2);
        REQUIRE_FALSE(pkb.insert_follows(1, 2));
    }
}

TEST_CASE("PKB::extract_design()")
{
    PKB pkb;

    SECTION("follows* 1-level depth")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.extract_design();
        
        REQUIRE(pkb.is_follows_star(1, 2));
        REQUIRE(pkb.is_follows_star(1, 3));
    }

    SECTION("follows* 2-level depth")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.insert_follows(4, 5);
        pkb.insert_follows(5, 6);
        pkb.insert_follows(3, 8);
        pkb.extract_design();
        
        REQUIRE(pkb.is_follows_star(1, 2));
        REQUIRE(pkb.is_follows_star(1, 3));
        REQUIRE(pkb.is_follows_star(4, 6));
        REQUIRE(pkb.is_follows_star(2, 8));

        REQUIRE_FALSE(pkb.is_follows_star(1, 6));
        REQUIRE_FALSE(pkb.is_follows_star(1, 5));
        REQUIRE_FALSE(pkb.is_follows_star(4, 8));
    }

    SECTION("parent* 3-level depth")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(2, 3);
        pkb.extract_design();

        REQUIRE(pkb.is_parent_star(1, 3));        
    }

    SECTION("parent* 4-level depth")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(1, 3);
        pkb.insert_parent(2, 4);
        pkb.insert_parent(4, 5);
        pkb.insert_parent(3, 6);
        pkb.extract_design();

        REQUIRE(pkb.is_parent_star(1, 3));        
        REQUIRE(pkb.is_parent_star(1, 4));        
        REQUIRE(pkb.is_parent_star(1, 5));        
        REQUIRE(pkb.is_parent_star(1, 6));        
        REQUIRE(pkb.is_parent_star(2, 5));

        REQUIRE_FALSE(pkb.is_parent_star(4, 6));        
        REQUIRE_FALSE(pkb.is_parent_star(2, 6));        
        REQUIRE_FALSE(pkb.is_parent_star(3, 5));        
    }
}

TEST_CASE("PKB::insert_parent()")
{
    PKB pkb;

    SECTION("insert success")
    {
        REQUIRE(pkb.insert_parent(1, 2));
    }

    SECTION("insert fail")
    {
        REQUIRE_FALSE(pkb.insert_parent(1, 1));
        REQUIRE_FALSE(pkb.insert_parent(1, 0));
        REQUIRE_FALSE(pkb.insert_parent(2, 1));
    }
}

TEST_CASE("PKB::get_follows_star()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    pkb.insert_follows(2, 3);
    pkb.insert_follows(5, 6);
    pkb.extract_design();

    SECTION("empty")
    {
        REQUIRE(pkb.get_follows_star(3).empty());
        REQUIRE(pkb.get_follows_star(-1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(pkb.get_follows_star(5).size() == 1);
        REQUIRE(pkb.get_follows_star(5)[0] == 6);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_follows_star(1).size() == 2);
        std::vector<int> result = pkb.get_follows_star(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_followed_star_by()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    pkb.insert_follows(2, 3);
    pkb.extract_design();

    SECTION("empty")
    {
        REQUIRE(pkb.get_followed_star_by(1).empty());
        REQUIRE(pkb.get_followed_star_by(-1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(pkb.get_followed_star_by(2).size() == 1);
        REQUIRE(pkb.get_followed_star_by(2)[0] == 1);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_followed_star_by(3).size() == 2);
        std::vector<int> result = pkb.get_followed_star_by(3);
        std::vector<int> expected({2, 1});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_parent_star()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);
    pkb.insert_parent(2, 3);
    pkb.extract_design();

    SECTION("empty")
    {
        REQUIRE(pkb.get_parent_star(-1).empty());
        REQUIRE(pkb.get_parent_star(4).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(pkb.get_parent_star(2).size() == 1);
        REQUIRE(pkb.get_parent_star(1)[0] == 3);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_parent_star(1).size() == 2);
        std::vector<int> result = pkb.get_parent_star(1);
        std::vector<int> expected({3, 2});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_children_star()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);
    pkb.insert_parent(2, 3);
    pkb.insert_parent(1, 11);
    pkb.extract_design();

    SECTION("empty")
    {
        REQUIRE(pkb.get_children_star(-1).empty());
        REQUIRE(pkb.get_children_star(1).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(pkb.get_children_star(11).size() == 1);
        REQUIRE(pkb.get_children_star(11)[0] == 1);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_children_star(3).size() == 2);
        std::vector<int> result = pkb.get_children_star(3);
        std::vector<int> expected({1, 2});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_follows()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    
    SECTION("success")
    {
        REQUIRE(pkb.get_follows(1) == 2);
    }

    SECTION("fail")
    {
        REQUIRE(pkb.get_follows(2) == -1);
        REQUIRE(pkb.get_follows(-1) == -1);
    }
}

TEST_CASE("PKB::get_followed_by()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    
    SECTION("success")
    {
        REQUIRE(pkb.get_followed_by(2) == 1);
    }

    SECTION("fail")
    {
        REQUIRE(pkb.get_followed_by(1) == -1);
        REQUIRE(pkb.get_followed_by(-1) == -1);
    }
}

TEST_CASE("PKB::get_parent()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);

    SECTION("success")
    {
        REQUIRE(pkb.get_parent(2) == 1);
    }
    
    SECTION("fail")
    {
        REQUIRE(pkb.get_parent(1) == -1);
        REQUIRE(pkb.get_parent(-1) == -1);
    }
}

TEST_CASE("PKB::get_children()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_children(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    SECTION("return >1")
    {
        pkb.insert_parent(1, 3);
        vector<int> result = pkb.get_children(1);
        REQUIRE(result.size() == 2);
    }

    SECTION("return empty")
    {
        REQUIRE(pkb.get_children(-1).empty());
        REQUIRE(pkb.get_children(3).empty());
    }
}

TEST_CASE("PKB::insert_assign()")
{
    PKB pkb;

    SECTION("success")
    {
        REQUIRE(pkb.insert_assign(1, "a", "b"));
    }
}

TEST_CASE("PKB::get_assign_pattern_matches()")
{
    PKB pkb;

    pkb.insert_assign(1, "c", "d");
    pkb.insert_assign(2, "a", "b");
    pkb.insert_assign(3, "a", "b");
    
    SECTION("1 matches")
    {
        vector<int> result = pkb.get_assign_pattern_matches("c", "d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION(">1 matches")
    {
        vector<int> result = pkb.get_assign_pattern_matches("a", "b");
        REQUIRE(result.size() == 2);
        vector<int> expected({2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }

    SECTION("0 matches")
    {
        REQUIRE(pkb.get_assign_pattern_matches("b", "a").empty());
        REQUIRE(pkb.get_assign_pattern_matches("A", "b").empty());
        REQUIRE(pkb.get_assign_pattern_matches("a", "B").empty());
    }
}

TEST_CASE("PKB::get_assign_pattern_contains()")
{
  PKB pkb;

    pkb.insert_assign(1, "c", "d");
    pkb.insert_assign(2, "a", "b");
    pkb.insert_assign(3, "a", "b");
    pkb.insert_assign(4, "a", "b + c");
    
    SECTION("1 matches")
    {
        vector<int> result = pkb.get_assign_pattern_contains("c", "d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION(">1 matches")
    {
        vector<int> result = pkb.get_assign_pattern_contains("a", "b");
        REQUIRE(result.size() == 3);
        vector<int> expected({2, 3, 4});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }

    SECTION("0 matches")
    {
        REQUIRE(pkb.get_assign_pattern_contains("b", "a").empty());
        REQUIRE(pkb.get_assign_pattern_contains("A", "b").empty());
        REQUIRE(pkb.get_assign_pattern_contains("a", "B").empty());
    }
}

TEST_CASE("PKB::get_all_assign_pattern_matches()")
{
PKB pkb;

    pkb.insert_assign(1, "c", "d");
    pkb.insert_assign(2, "a", "b");
    pkb.insert_assign(3, "e", "b");
    
    SECTION("1 matches")
    {
        vector<int> result = pkb.get_all_assign_pattern_matches("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION(">1 matches")
    {
        vector<int> result = pkb.get_all_assign_pattern_matches("b");
        REQUIRE(result.size() == 2);
        vector<int> expected({2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }

    SECTION("0 matches")
    {
        REQUIRE(pkb.get_all_assign_pattern_matches("a").empty());
        REQUIRE(pkb.get_all_assign_pattern_matches("B").empty());
    }
}

TEST_CASE("PKB::get_all_assign_pattern_contains()")
{
PKB pkb;

    pkb.insert_assign(1, "c", "d");
    pkb.insert_assign(2, "a", "b");
    pkb.insert_assign(3, "b", "b");
    pkb.insert_assign(4, "e", "e + b");
    
    SECTION("1 matches")
    {
        vector<int> result = pkb.get_all_assign_pattern_contains("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION(">1 matches")
    {
        vector<int> result = pkb.get_all_assign_pattern_contains("b");
        REQUIRE(result.size() == 3);
        vector<int> expected({2, 3, 4});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }

    SECTION("0 matches")
    {
        REQUIRE(pkb.get_all_assign_pattern_contains("a").empty());
        REQUIRE(pkb.get_all_assign_pattern_contains("B").empty());
    }
}

TEST_CASE("PKB::get_all_parent_relationship()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_parent_relationship().empty());
    }

    pkb.insert_parent(1, 2);
    
    SECTION("return 1")
    {
        unordered_map<int, vector<int>> result = pkb.get_all_parent_relationship();
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == vector<int>({2}));
    }

    pkb.insert_parent(1, 3);
    pkb.insert_parent(4, 5);

    SECTION("return >1")
    {
        unordered_map<int, vector<int>> result = pkb.get_all_parent_relationship();
        REQUIRE(result.size() == 2);
        REQUIRE(result[4] == vector<int>({5}));
        vector<int> result_vector = result[1];
        vector<int> expected({2, 3});
        sort(result_vector.begin(), result_vector.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result_vector == expected);
    }
}

TEST_CASE("PKB::get_all_follows_relationship()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_follows_relationship().empty());
    }

    pkb.insert_follows(1, 2);

    SECTION("return 1")
    {
        unordered_map<int, vector<int>> result = pkb.get_all_follows_relationship();
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == vector<int>({2}));
    }

    pkb.insert_follows(4, 5);

    SECTION("return >1")
    {
        unordered_map<int, vector<int>> result = pkb.get_all_follows_relationship();
        REQUIRE(result.size() == 2);
        REQUIRE(result[4] == vector<int>({5}));
        REQUIRE(result[1] == vector<int>({2}));
    }
}

TEST_CASE("PKB::get_all_parent_star_relationship()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_parent_star_relationship().empty());
    }
    
    SECTION("return 1")
    {
        pkb.insert_parent(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.get_all_parent_star_relationship().size() == 1);
        REQUIRE(pkb.get_all_parent_star_relationship()[1] == vector<int>({2}));
    }

    SECTION("return >1")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(1, 3);
        pkb.insert_parent(2, 4);
        pkb.extract_design();
        REQUIRE(pkb.get_all_parent_star_relationship().size() == 2);
        unordered_map<int, vector<int>> result = pkb.get_all_parent_star_relationship();
        vector<int> expected_vector({2, 3, 4});
        vector<int> result_vector = result[1];
        sort(result_vector.begin(), result_vector.end());
        sort(expected_vector.begin(), expected_vector.end());
        REQUIRE(result.size() == 2);
        REQUIRE(result_vector == expected_vector);
    }
}

TEST_CASE("PKB::get_all_follows_star_relationship()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_follows_relationship().empty());
    }


    SECTION("return 1")
    {
        pkb.insert_follows(1, 2);
        pkb.extract_design();
        unordered_map<int, vector<int>> result = pkb.get_all_follows_star_relationship();
        unordered_map<int, vector<int>> expected({{1, vector<int>({2})}});
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == expected[1]);
    }


    SECTION("return >1")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.insert_follows(3, 4);
        pkb.insert_follows(4, 11);
        pkb.extract_design();
        unordered_map<int, vector<int>> result = pkb.get_all_follows_star_relationship();
        vector<int> expected_vector({2, 3, 4, 11});
        vector<int> result_vector = result[1];
        sort(result_vector.begin(), result_vector.end());
        sort(expected_vector.begin(), expected_vector.end());
        REQUIRE(result.size() == 4);
        REQUIRE(result_vector == expected_vector);
    }
}

TEST_CASE("PKB::does_follows_exist()")
{
    PKB pkb;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb.does_follows_exist());
    }

    pkb.insert_follows(1, 2);

    SECTION("exist")
    {
        REQUIRE(pkb.does_follows_exist());
    }
}

TEST_CASE("PKB::does_follows_star_exist()")
{
    PKB pkb;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb.does_follows_star_exist());
    }

    SECTION("does not exist")
    {
        pkb.insert_follows(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.does_follows_star_exist());
    }
}

TEST_CASE("PKB::does_parent_exist()")
{
    PKB pkb;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb.does_parent_exist());
    }

    pkb.insert_parent(1, 2);

    SECTION("does not exist")
    {
        REQUIRE(pkb.does_parent_exist());
    }
}

TEST_CASE("PKB::does_parent_star_exist()")
{
    PKB pkb;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb.does_parent_star_exist());
    }

    SECTION("does not exist")
    {
        pkb.insert_parent(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.does_parent_star_exist());
    }
}

TEST_CASE("PKB::get_all_follows()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_follows().empty());
    }

    pkb.insert_follows(1, 2);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_follows();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    pkb.insert_follows(2, 3);
    pkb.insert_follows(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_follows();
        REQUIRE(result.size() == 3);
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_followed()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_followed().empty());
    }

    pkb.insert_follows(1, 2);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_followed();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    pkb.insert_follows(2, 3);
    pkb.insert_follows(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_followed();
        REQUIRE(result.size() == 3);
        vector<int> expected({2, 3, 4});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_parent()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_parent().empty());
    }

    pkb.insert_parent(1, 2);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_parent();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    pkb.insert_parent(1, 3);
    pkb.insert_parent(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_parent();
        REQUIRE(result.size() == 2);
        vector<int> expected({1, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_children()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_children().empty());
    }

    pkb.insert_parent(1, 2);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_children();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    pkb.insert_parent(1, 3);
    pkb.insert_parent(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_children();
        REQUIRE(result.size() == 3);
        vector<int> expected({2, 3, 4});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::is_follows()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    pkb.insert_follows(3, 4);

    SECTION("true")
    {
        REQUIRE(pkb.is_follows(1, 2));
    }

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.is_follows(1, 4));
        REQUIRE_FALSE(pkb.is_follows(2, 1));
    }
}

TEST_CASE("PKB::is_parent()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);
    pkb.insert_parent(3, 4);

    SECTION("true")
    {
        REQUIRE(pkb.is_parent(1, 2));
    }

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.is_parent(1, 4));
        REQUIRE_FALSE(pkb.is_parent(2, 1));
    }
}

TEST_CASE("PKB::is_follows_star()")
{
    PKB pkb;

    pkb.insert_follows(1, 2);
    pkb.insert_follows(2, 3);
    pkb.extract_design();

    SECTION("is_follows_star true")
    {
        REQUIRE(pkb.is_follows_star(1, 2));
        REQUIRE(pkb.is_follows_star(1, 3));
        REQUIRE(pkb.is_follows_star(2, 3));
    }

    SECTION("is_follows_star false")
    {
        REQUIRE_FALSE(pkb.is_follows_star(1, 4));
        REQUIRE_FALSE(pkb.is_follows_star(3, 2));
    }
}

TEST_CASE("PKB::is_parent_star()")
{
    PKB pkb;

    pkb.insert_parent(1, 2);
    pkb.insert_parent(2, 3);
    pkb.extract_design();
    
    SECTION("is_parent_star true")
    {
        REQUIRE(pkb.is_parent_star(1, 2));
        REQUIRE(pkb.is_parent_star(1, 3));
        REQUIRE(pkb.is_parent_star(2, 3));
    }

    SECTION("is_parent_star false")
    {
        REQUIRE_FALSE(pkb.is_parent_star(1, 4));
        REQUIRE_FALSE(pkb.is_parent_star(3, 2));
    }
}

TEST_CASE("PKB::get_all_follows_star()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_follows_star().empty());
    }


    SECTION("return size of 1")
    {
        pkb.insert_follows(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.get_all_follows_star().size() == 1);
        REQUIRE(pkb.get_all_follows_star()[0] == 1);
    }

    SECTION("return size of >1")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_follows_star().size() == 2);
        std::vector<int> expected({1, 2});
        std::vector<int> result = pkb.get_all_follows_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_followed_star()")
{
    PKB pkb;
    
    SECTION("empty")
    {
        REQUIRE(pkb.get_all_followed_star().empty());
    }


    SECTION("return size of 1")
    {
        pkb.insert_follows(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.get_all_followed_star().size() == 1);
        REQUIRE(pkb.get_all_followed_star()[0] == 2);
    }

    SECTION("return size of >1")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_followed_star().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = pkb.get_all_followed_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_parent_star()")
{
    PKB pkb;
    
    SECTION("empty")
    {
        REQUIRE(pkb.get_all_parent_star().empty());
    }

    SECTION("return size of 1")
    {
        pkb.insert_parent(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.get_all_parent_star().size() == 1);
        REQUIRE(pkb.get_all_parent_star() == std::vector<int>({1}));
    }

    SECTION("return size of >1")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(2, 3);
        pkb.insert_parent(2, 4);
        pkb.extract_design();
        REQUIRE(pkb.get_all_parent_star().size() == 2);
        std::vector<int> expected({1, 2});
        std::vector<int> result = pkb.get_all_parent_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_children_star()")
{
    PKB pkb;
    
    SECTION("empty")
    {
        REQUIRE(pkb.get_all_children_star().empty());
    }

    SECTION("return size of 1")
    {
        pkb.insert_parent(1, 2);
        pkb.extract_design();
        REQUIRE(pkb.get_all_children_star().size() == 1);
        REQUIRE(pkb.get_all_children_star() == std::vector<int>({2}));
    }

    SECTION("return size of >1, 1 parent")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(1, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_children_star().size() == 2);
        std::vector<int> expected({2, 3});
        std::vector<int> result = pkb.get_all_children_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }

    SECTION("return size of >1, >1 parent")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(2, 3);
        pkb.insert_parent(2, 4);
        pkb.extract_design();
        REQUIRE(pkb.get_all_children_star().size() == 3);
        std::vector<int> expected({2, 3, 4});
        std::vector<int> result = pkb.get_all_children_star();
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::assign_to_variable()")
{
    PKB pkb;

    pkb.insert_assign(1, "a", "b");

    SECTION("success")
    {
        REQUIRE(pkb.assign_to_variable(1) == "a");
    }

    SECTION("fail")
    {
        REQUIRE(pkb.assign_to_variable(2).empty());
    }
}

TEST_CASE("PKB::assigns_to_variables()")
{
    PKB pkb;

    pkb.insert_assign(1, "a", "b");
    pkb.insert_assign(2, "b", "c");
    pkb.insert_assign(3, "b", "b");

    SECTION("success return")
    {
        // in-order request
        vector<int> request({1, 2});
        vector<string> expected({"a", "b"});
        vector<string> result = pkb.assigns_to_variables(request);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);

        // out-of-order request
        vector<int> request_reverse({2, 1});
        vector<string> expected_reverse({"b", "a"});
        vector<string> result_reverse = pkb.assigns_to_variables(request_reverse);
        sort(result_reverse.begin(), result_reverse.end());
        sort(expected_reverse.begin(), expected_reverse.end());
        REQUIRE(result_reverse == expected_reverse);

        // return same variable
        vector<int> request_dup({2, 3});
        vector<string> expected_dup({"b"});
        vector<string> result_dup = pkb.assigns_to_variables(request_dup);
        sort(result_dup.begin(), result_dup.end());
        sort(expected_dup.begin(), expected_dup.end());
        REQUIRE(result_dup == expected_dup);
    }

    SECTION("empty return")
    {
        REQUIRE(pkb.assigns_to_variables(vector<int>({10})).empty());
        REQUIRE(pkb.assigns_to_variables(vector<int>()).empty());
    }

}

TEST_CASE("PKB::insert_type()")
{
    PKB pkb;
    
    SECTION("success")
    {
        REQUIRE(pkb.insert_type(1, EntityType::ASSIGN));
    }

    SECTION("fail")
    {
        // insert when already exists
        REQUIRE(pkb.insert_type(1, EntityType::ASSIGN));
        // insert invalid EntityType
        REQUIRE_FALSE(pkb.insert_type(1, EntityType::VARIABLE));
    }
}

TEST_CASE("PKB::get_all_whiles()")
{
    PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_whiles().empty());
    }

    pkb.insert_type(1, EntityType::WHILE);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_whiles();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::WHILE);
    pkb.insert_type(3, EntityType::WHILE);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_whiles();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_ifs()")
{
    PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_ifs().empty());
    }

    pkb.insert_type(1, EntityType::IF);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_ifs();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::IF);
    pkb.insert_type(3, EntityType::IF);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_ifs();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_assigns()")
{
    PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_assigns().empty());
    }

    pkb.insert_type(1, EntityType::ASSIGN);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_assigns();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_type(3, EntityType::ASSIGN);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_assigns();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_reads()")
{
  PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_reads().empty());
    }

    pkb.insert_type(1, EntityType::READ);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_reads();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::READ);
    pkb.insert_type(3, EntityType::READ);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_reads();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_prints()")
{
  PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_prints().empty());
    }

    pkb.insert_type(1, EntityType::PRINT);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_prints();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::PRINT);
    pkb.insert_type(3, EntityType::PRINT);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_prints();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_calls()")
{
  PKB pkb;

    SECTION("return 0")
    {
        REQUIRE(pkb.get_all_calls().empty());
    }

    pkb.insert_type(1, EntityType::CALL);

    SECTION("return 1")
    {
        vector<int> result = pkb.get_all_calls();
        REQUIRE(result.size() == 1);
        REQUIRE(result == vector<int>({1}));
    }

    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(3, EntityType::CALL);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_calls();
        vector<int> expected({1, 2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}
