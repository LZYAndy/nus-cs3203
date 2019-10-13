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
        pkb.insert_type(2, EntityType::IF);
        pkb.insert_type(3, EntityType::PRINT);
        REQUIRE(pkb.get_all_statement_nums().size() == 3);
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

    SECTION("calls* no cyclic")
    {
        pkb.insert_calls("e", "f");
        pkb.insert_calls("f", "h");
        REQUIRE(pkb.extract_design());

        REQUIRE(pkb.is_calls_star("e", "h"));
    }

    SECTION("calls* cyclic")
    {
        pkb.insert_calls("a", "b");
        pkb.insert_calls("b", "a");
        REQUIRE_FALSE(pkb.extract_design());
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
        vector<int> result = pkb.get_follows_star(1);
        vector<int> expected({2, 3});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        vector<int> result = pkb.get_followed_star_by(3);
        vector<int> expected({2, 1});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        REQUIRE(pkb.get_parent_star(2)[0] == 1);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_parent_star(3).size() == 2);
        vector<int> result = pkb.get_parent_star(3);
        vector<int> expected({1, 2});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        REQUIRE(pkb.get_children_star(11).empty());
    }

    SECTION("return size of 1")
    {
        REQUIRE(pkb.get_children_star(2).size() == 1);
        REQUIRE(pkb.get_children_star(2)[0] == 3);
    }

    SECTION("return size of >1")
    {
        REQUIRE(pkb.get_children_star(1).size() == 3);
        vector<int> result = pkb.get_children_star(1);
        vector<int> expected({2, 3, 11});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        REQUIRE(result[0] == 2);
    }

    pkb.insert_follows(2, 3);
    pkb.insert_follows(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_follows();
        REQUIRE(result.size() == 3);
        vector<int> expected({3, 2, 4});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}
TEST_CASE("PKB::get_all_variables()")
{
    PKB pkb;
    unordered_set<string> var_table;

    SECTION("0 variable")
    {
        var_table = pkb.get_all_variables();
        REQUIRE(var_table.size() == 0);
    }

    pkb.insert_variable("x");
    pkb.insert_variable("y");
    pkb.insert_variable("y");

    SECTION("more than 0 variable")
    {
        var_table = pkb.get_all_variables();
        REQUIRE(var_table.size() == 2);
        REQUIRE(var_table.count("x") == 1);
        REQUIRE(var_table.count("y") == 1);
    }
}

TEST_CASE("PKB::get_all_procedures()")
{
    PKB pkb;
    unordered_set<string> proc_table;

    SECTION("0 procedure")
    {
        proc_table = pkb.get_all_procedures();
        REQUIRE(proc_table.size() == 0);
    }

    pkb.insert_procedure("main");
    pkb.insert_procedure("procX");
    pkb.insert_procedure("procX");

    SECTION("more than 0 procedure")
    {
        proc_table = pkb.get_all_procedures();
        REQUIRE(proc_table.size() == 2);
        REQUIRE(proc_table.count("main") == 1);
        REQUIRE(proc_table.count("procX") == 1);
    }
}

TEST_CASE("PKB::get_statements_uses()")
{
    PKB pkb;
    pkb.insert_uses(1, "a");
    pkb.insert_uses(2, "b");
    pkb.insert_uses(7, "a");
    pkb.insert_uses(7, "d");
    pkb.insert_uses(9, "c");

    vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_uses("nya");
        REQUIRE(result.empty());

        result = pkb.get_statements_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);

        result = pkb.get_statements_uses("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);

        result = pkb.get_statements_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_uses("a");
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_procedures_uses()")
{
    PKB pkb;
    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    vector<string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_procedures_uses("nya");
        REQUIRE(result.empty());

        result = pkb.get_procedures_uses("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 procedure")
    {
        result = pkb.get_procedures_uses("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);

        result = pkb.get_procedures_uses("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_procedures_uses("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("PKB::get_used_by_statement()")
{
    PKB pkb;
    pkb.insert_uses(1, "a");
    pkb.insert_uses(2, "b");
    pkb.insert_uses(5, "a");
    pkb.insert_uses(5, "d");
    pkb.insert_uses(100, "c");

    vector<string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_used_by_statement(3);
        REQUIRE(result.empty());

        result = pkb.get_used_by_statement(233);
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_used_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);

        result = pkb.get_used_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_used_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_used_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("PKB::get_used_by_procedure()")
{
    PKB pkb;
    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    vector<string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_used_by_procedure("nya");
        REQUIRE(result.empty());

        result = pkb.get_used_by_procedure("procx");
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_used_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_used_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_used_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("PKB::is_uses() for stmt")
{
    PKB pkb;
    pkb.insert_uses(1, "a");
    pkb.insert_uses(2, "a");

    SECTION("return true")
    {
        REQUIRE(pkb.is_uses(1, "a"));
        REQUIRE(pkb.is_uses(2, "a"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_uses(3, "a"));
        REQUIRE_FALSE(pkb.is_uses(2, "b"));
    }
}

TEST_CASE("PKB::is_uses() for proc")
{
    PKB pkb;
    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");

    SECTION("return true")
    {
        REQUIRE(pkb.is_uses("main", "a"));
        REQUIRE(pkb.is_uses("main", "b"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_uses("proc", "a"));
        REQUIRE_FALSE(pkb.is_uses("main", "B"));
    }
}

TEST_CASE("PKB::get_all_uses_procedures()")
{
    PKB pkb;

    vector<string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.empty());
    }

    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");

    SECTION("return 1 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }

    pkb.insert_uses("procX", "a");
    pkb.insert_uses("procY", "c");

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_all_uses_procedures();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("main");
        expected.push_back("procX");
        expected.push_back("procY");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_uses_statements()")
{
    PKB pkb;

    vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.empty());
    }

    pkb.insert_uses(1, "a");
    pkb.insert_uses(1, "b");

    SECTION("return 1 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    pkb.insert_uses(5, "a");
    pkb.insert_uses(6, "c");

    SECTION("return more than 1 statement")
    {
        result = pkb.get_all_uses_statements();
        REQUIRE(result.size() == 3);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_uses_statements_relationship()")
{
    PKB pkb;

    unordered_map<int, vector<string>> result;
    unordered_map<int, vector<string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_uses_statements_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_uses(1, "a");
    pkb.insert_uses(1, "b");
    pkb.insert_uses(5, "b");

    SECTION("bank with element(s)")
    {
        vector<string> value1;
        vector<string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5, value2);
        result = pkb.get_all_uses_statements_relationship();
        REQUIRE(result.size() == expected.size());
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
        REQUIRE(result[0] == 1);
    }

    pkb.insert_follows(2, 3);
    pkb.insert_follows(3, 4);

    SECTION("return >1")
    {
        vector<int> result = pkb.get_all_followed();
        REQUIRE(result.size() == 3);
        vector<int> expected({2, 3, 1});
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
        REQUIRE(pkb.get_all_follows_star()[0] == 2);
    }

    SECTION("return size of >1")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_follows_star().size() == 2);
        vector<int> expected({3, 2});
        vector<int> result = pkb.get_all_follows_star();
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_uses_procedures_relationship()")
{
    PKB pkb;

    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_uses_procedures_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_uses("main", "a");
    pkb.insert_uses("main", "b");
    pkb.insert_uses("procX", "b");

    SECTION("bank with element(s)")
    {
        vector<string> value1;
        vector<string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX", value2);
        result = pkb.get_all_uses_procedures_relationship();
        REQUIRE(result.size() == expected.size());
        REQUIRE(result == expected);
    }
}
TEST_CASE("PKB::get_statements_modifies()")
{
    PKB pkb;
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(2, "b");
    pkb.insert_modifies(7, "a");
    pkb.insert_modifies(7, "d");
    pkb.insert_modifies(9, "c");

    vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_modifies("nya");
        REQUIRE(result.empty());

        result = pkb.get_statements_modifies("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);

        result = pkb.get_statements_modifies("d");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 7);

        result = pkb.get_statements_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 9);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_modifies("a");
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(7);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
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
        REQUIRE(pkb.get_all_followed_star()[0] == 1);
    }

    SECTION("return size of >1")
    {
        pkb.insert_follows(1, 2);
        pkb.insert_follows(2, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_followed_star().size() == 2);
        vector<int> expected({2, 1});
        vector<int> result = pkb.get_all_followed_star();
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        REQUIRE(pkb.get_all_parent_star() == vector<int>({1}));
    }

    SECTION("return size of >1")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(2, 3);
        pkb.insert_parent(2, 4);
        pkb.extract_design();
        REQUIRE(pkb.get_all_parent_star().size() == 2);
        vector<int> expected({1, 2});
        vector<int> result = pkb.get_all_parent_star();
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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
        REQUIRE(pkb.get_all_children_star() == vector<int>({2}));
    }

    SECTION("return size of >1, 1 parent")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(1, 3);
        pkb.extract_design();
        REQUIRE(pkb.get_all_children_star().size() == 2);
        vector<int> expected({2, 3});
        vector<int> result = pkb.get_all_children_star();
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }

    SECTION("return size of >1, >1 parent")
    {
        pkb.insert_parent(1, 2);
        pkb.insert_parent(2, 3);
        pkb.insert_parent(2, 4);
        pkb.extract_design();
        REQUIRE(pkb.get_all_children_star().size() == 3);
        vector<int> expected({2, 3, 4});
        vector<int> result = pkb.get_all_children_star();
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
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

TEST_CASE("PKB::get_procedures_modifies()")
{
    PKB pkb;
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");

    vector<string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_procedures_modifies("nya");
        REQUIRE(result.empty());

        result = pkb.get_procedures_modifies("A");
        REQUIRE(result.empty());
    }

    SECTION("return 1 procedure")
    {
        result = pkb.get_procedures_modifies("b");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);

        result = pkb.get_procedures_modifies("c");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("procY") == 0);
    }

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_procedures_modifies("a");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("main") == 0);
        REQUIRE(result[1].compare("procX") == 0);
    }
}

TEST_CASE("PKB::get_modified_by_statement()")
{
    PKB pkb;
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(2, "b");
    pkb.insert_modifies(5, "a");
    pkb.insert_modifies(5, "d");
    pkb.insert_modifies(100, "c");

    vector<string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_modified_by_statement(3);
        REQUIRE(result.empty());

        result = pkb.get_modified_by_statement(233);
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_modified_by_statement(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("b") == 0);

        result = pkb.get_modified_by_statement(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_modified_by_statement(100);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_modified_by_statement(5);
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("d") == 0);
    }
}

TEST_CASE("PKB::get_modified_by_procedure()")
{
    PKB pkb;
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");

    vector<string> result;

    SECTION("return 0 variable")
    {
        result = pkb.get_modified_by_procedure("nya");
        REQUIRE(result.empty());

        result = pkb.get_modified_by_procedure("procx");
        REQUIRE(result.empty());
    }

    SECTION("return 1 variable")
    {
        result = pkb.get_modified_by_procedure("procX");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("a") == 0);

        result = pkb.get_modified_by_procedure("procY");
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("c") == 0);
    }

    SECTION("return more than 1 variable")
    {
        result = pkb.get_modified_by_procedure("main");
        REQUIRE(result.size() == 2);
        REQUIRE(result[0].compare("a") == 0);
        REQUIRE(result[1].compare("b") == 0);
    }
}

TEST_CASE("PKB::is_modifies() for stmt")
{
    PKB pkb;
    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(2, "a");

    SECTION("return true")
    {
        REQUIRE(pkb.is_modifies(1, "a"));
        REQUIRE(pkb.is_modifies(2, "a"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_modifies(3, "a"));
        REQUIRE_FALSE(pkb.is_modifies(2, "b"));
    }
}

TEST_CASE("PKB::is_modifies() for proc")
{
    PKB pkb;
    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");

    SECTION("return true")
    {
        REQUIRE(pkb.is_modifies("main", "a"));
        REQUIRE(pkb.is_modifies("main", "b"));
    }

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_modifies("proc", "a"));
        REQUIRE_FALSE(pkb.is_modifies("main", "B"));
    }
}

TEST_CASE("PKB::get_all_modifies_procedures()")
{
    PKB pkb;

    vector<string> result;

    SECTION("return 0 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.empty());
    }

    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");

    SECTION("return 1 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0].compare("main") == 0);
    }

    pkb.insert_modifies("procX", "a");
    pkb.insert_modifies("procY", "c");

    SECTION("return more than 1 procedure")
    {
        result = pkb.get_all_modifies_procedures();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("main");
        expected.push_back("procX");
        expected.push_back("procY");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_modifies_statements()")
{
    PKB pkb;

    vector<int> result;

    SECTION("return 0 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.empty());
    }

    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(1, "b");

    SECTION("return 1 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    pkb.insert_modifies(5, "a");
    pkb.insert_modifies(6, "c");

    SECTION("return more than 1 statement")
    {
        result = pkb.get_all_modifies_statements();
        REQUIRE(result.size() == 3);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(5);
        expected.push_back(6);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_modifies_statements_relationship()")
{
    PKB pkb;

    unordered_map<int, vector<string>> result;
    unordered_map<int, vector<string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_modifies_statements_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_modifies(1, "a");
    pkb.insert_modifies(1, "b");
    pkb.insert_modifies(5, "b");

    SECTION("bank with element(s)")
    {
        vector<string> value1;
        vector<string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace(1, value1);
        expected.emplace(5, value2);
        result = pkb.get_all_modifies_statements_relationship();
        REQUIRE(result.size() == expected.size());
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

TEST_CASE("PKB::get_all_modifies_procedures_relationship()")
{
    PKB pkb;

    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> expected;

    SECTION("bank without element")
    {
        result = pkb.get_all_modifies_procedures_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_modifies("main", "a");
    pkb.insert_modifies("main", "b");
    pkb.insert_modifies("procX", "b");

    SECTION("bank with element(s)")
    {
        vector<string> value1;
        vector<string> value2;
        value1.push_back("a");
        value1.push_back("b");
        value2.push_back("b");
        expected.emplace("main", value1);
        expected.emplace("procX", value2);
        result = pkb.get_all_modifies_procedures_relationship();
        REQUIRE(result.size() == expected.size());
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

TEST_CASE("PKB::does_uses_exist()")
{
    PKB pkb1;
    PKB pkb2;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb1.does_uses_exist());
        REQUIRE_FALSE(pkb2.does_uses_exist());
    }

    pkb1.insert_uses(1, "x");
    pkb2.insert_uses("main", "y");

    SECTION("exists")
    {
        REQUIRE(pkb1.does_uses_exist());
        REQUIRE(pkb2.does_uses_exist());
    }

    pkb1.insert_uses("main", "x");

    SECTION("exists multiple uses relationships")
    {
        REQUIRE(pkb1.does_uses_exist());
    }
}

TEST_CASE("PKB::does_modifies_exist()")
{
    PKB pkb1;
    PKB pkb2;

    SECTION("does not exist")
    {
        REQUIRE_FALSE(pkb1.does_modifies_exist());
        REQUIRE_FALSE(pkb2.does_modifies_exist());
    }

    pkb1.insert_modifies(1, "x");
    pkb2.insert_modifies("main", "y");

    SECTION("exists")
    {
        REQUIRE(pkb1.does_modifies_exist());
        REQUIRE(pkb2.does_modifies_exist());
    }

    pkb1.insert_modifies("main", "x");

    SECTION("exists multiple uses relationships")
    {
        REQUIRE(pkb1.does_modifies_exist());
    }
}

TEST_CASE("PKB::insert_constant()")
{
    PKB pkb;
    SECTION("success")
    {
        REQUIRE(pkb.insert_constant("1"));
        REQUIRE(pkb.insert_constant("-1"));
    }

    SECTION("fail")
    {
        REQUIRE(pkb.insert_constant("1"));
        REQUIRE_FALSE(pkb.insert_constant("1"));
    }
}

TEST_CASE("PKB::get_all_constants()")
{
    PKB pkb;
    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_constants().empty());
    }

    SECTION("return 1")
    {
        pkb.insert_constant("1");
        pkb.insert_constant("1");
        REQUIRE(pkb.get_all_constants().size() == 1);
        REQUIRE(pkb.get_all_constants()[0] == "1");
    }

    SECTION("return >1")
    {
        pkb.insert_constant("1");
        pkb.insert_constant("2");
        pkb.insert_constant("3");
        vector<string> result = pkb.get_all_constants();
        vector<string> expected({"1", "2", "3"});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result.size() == 3);
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::insert_next()")
{
    PKB pkb;
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.insert_next(3, 3));
        REQUIRE_FALSE(pkb.insert_next(0, 1));
        REQUIRE_FALSE(pkb.insert_next(1, 0));
    }

    SECTION("return false")
    {
        REQUIRE(pkb.insert_next(3, 4));
    }
}

TEST_CASE("PKB::is_next()")
{
    PKB pkb;
    pkb.insert_next(3, 4);
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_next(3, 5));
        REQUIRE_FALSE(pkb.is_next(4, 3));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.is_next(3, 4));
    }
}

TEST_CASE("PKB::does_next_exists()")
{
    PKB pkb;
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.does_next_exists());
    }

    pkb.insert_next(1, 2);
    SECTION("return true")
    {
        REQUIRE(pkb.does_next_exists());
    }
}

TEST_CASE("PKB::get_statements_previous()")
{
    PKB pkb;
    pkb.insert_next(3, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(1, 2);
    SECTION("return 0 statement")
    {
        std::vector<int> result = pkb.get_statements_previous(3);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        std::vector<int> result = pkb.get_statements_previous(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statements")
    {
        std::vector<int> result = pkb.get_statements_previous(10);
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(9);
        expected.push_back(3);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_statements_next()")
{
    PKB pkb;
    pkb.insert_next(3, 10);
    pkb.insert_next(3, 4);
    pkb.insert_next(1, 2);
    SECTION("return 0 statement")
    {
        std::vector<int> result = pkb.get_statements_next(2);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        std::vector<int> result = pkb.get_statements_next(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    SECTION("return more than 1 statement")
    {
        std::vector<int> result = pkb.get_statements_next(3);
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(10);
        expected.push_back(4);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_previous()")
{
    PKB pkb;
    SECTION("return 0 statement")
    {
        std::vector<int> result = pkb.get_all_previous();
        REQUIRE(result.empty());
    }

    pkb.insert_next(5, 10);
    SECTION("return 1 statement")
    {
        std::vector<int> result = pkb.get_all_previous();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 5);
    }

    pkb.insert_next(9, 10);
    SECTION("return more than 1 statement")
    {
        std::vector<int> result = pkb.get_all_previous();
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(5);
        expected.push_back(9);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_next()")
{
    PKB pkb;
    SECTION("return 0 statement")
    {
        std::vector<int> result = pkb.get_all_next();
        REQUIRE(result.empty());
    }

    pkb.insert_next(1, 2);
    SECTION("return 1 statement")
    {
        std::vector<int> result = pkb.get_all_next();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    pkb.insert_next(1, 10);
    SECTION("return more than 1 statement")
    {
        std::vector<int> result = pkb.get_all_next();
        REQUIRE(result.size() == 2);
        std::vector<int> expected;
        expected.push_back(2);
        expected.push_back(10);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::insert_while()")
{
    PKB pkb;
    pkb.insert_while(1, {"x"});
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.insert_while(0, {"y"}));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.insert_while(5, {"y"}));
    }
}

TEST_CASE("PKB::insert_stmt_in_while_stmtLst()")
{
    PKB pkb;
    pkb.insert_while(2, {"x"});
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.insert_stmt_in_while_stmtLst(3, 5));
        REQUIRE_FALSE(pkb.insert_stmt_in_while_stmtLst(0, 5));
        REQUIRE_FALSE(pkb.insert_stmt_in_while_stmtLst(2, 2));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.insert_stmt_in_while_stmtLst(2, 5));
    }
}

TEST_CASE("PKB::is_while()")
{
    PKB pkb;
    pkb.insert_while(10, {"x"});
    SECTION("return true")
    {
        REQUIRE_FALSE(pkb.is_while(1));
    }

    SECTION("return false")
    {
        REQUIRE(pkb.is_while(10));
    }
}

TEST_CASE("PKB::get_while_stmtLst()")
{
    PKB pkb;
    pkb.insert_while(3, {"x"});
    pkb.insert_stmt_in_while_stmtLst(3, 4);
    SECTION("return 1 statement")
    {
        std::vector<int> result = pkb.get_while_stmtLst(3);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 4);
    }
    pkb.insert_stmt_in_while_stmtLst(3, 5);
    pkb.insert_stmt_in_while_stmtLst(3, 6);
    SECTION("return more than 1 statements")
    {
        std::vector<int> result = pkb.get_while_stmtLst(3);
        REQUIRE(result.size() == 3);
        std::vector<int> expected;
        expected.push_back(6);
        expected.push_back(5);
        expected.push_back(4);
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_while_with_control_var()")
{
PKB pkb;
pkb.insert_while(1, {"x", "y"});
pkb.insert_while(10, {"x"});

SECTION("return 0 statement")
{
std::vector<int> result = pkb.get_while_with_control_var("y");
REQUIRE(result.size() == 1);
REQUIRE(result[0] == 1);
}

SECTION("return more than 0 statements")
{
std::vector<int> result = pkb.get_while_with_control_var("x");
REQUIRE(result.size() == 2);
std::vector<int> expected;
expected.push_back(1);
expected.push_back(10);
std::sort(expected.begin(), expected.end());
std::sort(result.begin(), result.end());
REQUIRE(expected == result);
}
}

TEST_CASE("PKB::get_all_whilestmt_and_control_var()")
{
PKB pkb;
SECTION("return 0 relationship")
{
std::unordered_map<int, std::vector<std::string>> result = pkb.get_all_whilestmt_and_control_var();
REQUIRE(result.empty());
}

pkb.insert_while(1, {"x", "y"});
pkb.insert_while(10, {"x"});
SECTION("return more than 0 relationships")
{
std::unordered_map<int, std::vector<std::string>> result = pkb.get_all_whilestmt_and_control_var();
REQUIRE(result.size() == 2);
std::unordered_map<int, std::vector<std::string>> expected;
std::vector<std::string> value1;
std::vector<std::string> value2;
value1.push_back("x");
value1.push_back("y");
value2.push_back("x");
expected.emplace(1, value1);
expected.emplace(10, value2);
REQUIRE(expected == result);
}
}

TEST_CASE("PKB::does_calls_exist()")
{
    PKB pkb;

    SECTION("empty")
    {
        pkb.insert_calls("hello", "hello");
        REQUIRE_FALSE(pkb.does_calls_exist());
    }

    SECTION(">1")
    {
        pkb.insert_calls("hello", "helloWorld");
        REQUIRE(pkb.does_calls_exist());
    }
}

TEST_CASE("PKB::is_calls()")
{
    PKB pkb;
    pkb.insert_calls("hello", "world");
    pkb.insert_calls("foo", "bar");
    pkb.insert_calls("chocolate", "vanilla");
    pkb.insert_calls("hello", "chocolate");

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_calls("hello", "vanilla"));
        REQUIRE_FALSE(pkb.is_calls("Foo", "Bar"));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.is_calls("foo", "bar"));
        REQUIRE(pkb.is_calls("hello", "world"));
        REQUIRE(pkb.is_calls("hello", "chocolate"));
    }
}

TEST_CASE("PKB::get_all_procedures_calls()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_calls().empty());
    }

    SECTION("return 1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("bye", "world");
        vector<string> result = pkb.get_all_procedures_calls();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "banana");
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        vector<string> result = pkb.get_all_procedures_calls();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("banana");
        expected.push_back("pie");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_if_pattern_contains()")
{
    PKB pkb;

    pkb.insert_if(1, {"y"});
    pkb.insert_if(2, {"x", "y"});
    pkb.insert_if(2, {"x", "y"});
    pkb.insert_if(3, {"y"});

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_if_pattern_contains("DONTEXIST").empty());
        REQUIRE(pkb.get_all_if_pattern_contains("X").empty());
    }

    SECTION("return 1 result")
    {
        REQUIRE(pkb.get_all_if_pattern_contains("x").size() == 1);
        REQUIRE(pkb.get_all_if_pattern_contains("x")[0] == 2);
    }

    SECTION("return >1 result")
    {
        std::vector<int> result = pkb.get_all_if_pattern_contains("y");
        REQUIRE(result.size() == 3);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_procedures_called()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_called().empty());
    }

    SECTION("return 1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "itsMe");
        vector<string> result = pkb.get_all_procedures_called();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "banana");
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        vector<string> result = pkb.get_all_procedures_called();
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("hello");
        expected.push_back("chocolate");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_procedures_called_by()")
{
    PKB pkb;
    pkb.insert_calls("hello", "world");
    pkb.insert_calls("hello", "itsMe");
    pkb.insert_calls("hello", "banana");
    pkb.insert_calls("chocolate", "banana");
    pkb.insert_calls("chocolate", "pie");
    pkb.insert_calls("banana", "pie");

    SECTION("return empty")
    {
        REQUIRE(pkb.get_procedures_called_by("bye").empty());
    }

    SECTION("return 1")
    {
        vector<string> result = pkb.get_procedures_called_by("banana");
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("pie");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        vector<string> result = pkb.get_procedures_called_by("chocolate");
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("banana");
        expected.push_back("pie");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_if_and_control_variables_map()")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_if_and_control_variables_map().empty());
    }

    pkb.insert_if(1, {"y"});
    pkb.insert_if(2, {"x", "y"});
    pkb.insert_if(2, {"x", "y"});
    pkb.insert_if(3, {"y"});

    SECTION(">1")
    {
        std::unordered_map<int, std::vector<std::string>> expected;
        expected.insert({1, {"y"}});
        expected.insert({2, {"x", "y"}});
        expected.insert({3, {"y"}});
        REQUIRE(expected == pkb.get_all_if_and_control_variables_map());
    }
}

TEST_CASE("PKB::get_all_procedures_calls_relationship()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_calls_relationship().empty());
    }

    pkb.insert_calls("hello", "world");
    pkb.insert_calls("hello", "itsMe");
    pkb.insert_calls("hello", "banana");

    SECTION("return 1")
    {
        unordered_map<string, vector<string>> result = pkb.get_all_procedures_calls_relationship();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        vector<string> result_values = result["hello"];
        sort(expected.begin(), expected.end());
        sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        pkb.insert_calls("banana", "pie");
        unordered_map<string, vector<string>> result = pkb.get_all_procedures_calls_relationship();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        vector<string> result_values = result["hello"];
        sort(expected.begin(), expected.end());
        sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);

        vector<string> expected2;
        expected2.push_back("pie");
        expected2.push_back("banana");
        vector<string> result_values2 = result["chocolate"];
        sort(expected2.begin(), expected2.end());
        sort(result_values2.begin(), result_values2.end());
        REQUIRE(expected2 == result_values2);

        vector<string> expected3;
        expected3.push_back("pie");
        vector<string> result_values3 = result["banana"];
        sort(expected3.begin(), expected3.end());
        sort(result_values3.begin(), result_values3.end());
        REQUIRE(expected3 == result_values3);
    }
}

TEST_CASE("PKB::does_calls_star_exist()")
{
    PKB pkb;

    SECTION("empty")
    {
        pkb.insert_calls("hello", "hello");
        pkb.extract_design();
        REQUIRE_FALSE(pkb.does_calls_star_exist());
    }

    SECTION(">1")
    {
        pkb.insert_calls("hello", "helloWorld");
        pkb.extract_design();
        REQUIRE(pkb.does_calls_star_exist());
    }
}

TEST_CASE("PKB::is_calls_star()")
{
    PKB pkb;
    pkb.insert_calls("hello", "world");
    pkb.insert_calls("foo", "bar");
    pkb.insert_calls("chocolate", "vanilla");
    pkb.insert_calls("hello", "chocolate");
    pkb.extract_design();

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_calls_star("Foo", "Bar"));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.is_calls_star("hello", "vanilla"));
        REQUIRE(pkb.is_calls_star("foo", "bar"));
        REQUIRE(pkb.is_calls_star("hello", "world"));
        REQUIRE(pkb.is_calls_star("hello", "chocolate"));
    }
}

TEST_CASE("PKB::get_all_procedures_calls_star()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_calls_star().empty());
    }

    SECTION("return 1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("bye", "world");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_calls_star();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "banana");
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_calls_star();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("banana");
        expected.push_back("pie");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_procedures_called_star()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_called_star().empty());
    }

    SECTION("return 1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "itsMe");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_called_star();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("hello", "world");
        pkb.insert_calls("hello", "banana");
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_called_star();
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("hello");
        expected.push_back("chocolate");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_procedures_called_by_star()")
{
    PKB pkb;
    pkb.insert_calls("hello", "world");
    pkb.insert_calls("hello", "itsMe");
    pkb.insert_calls("hello", "banana");
    pkb.insert_calls("chocolate", "banana");
    pkb.insert_calls("chocolate", "pie");
    pkb.insert_calls("banana", "pie");
    pkb.extract_design();

    SECTION("return empty")
    {
        REQUIRE(pkb.get_procedures_called_by_star("bye").empty());
    }

    SECTION("return 1")
    {
        vector<string> result = pkb.get_procedures_called_by_star("banana");
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("pie");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        vector<string> result = pkb.get_procedures_called_by_star("chocolate");
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("banana");
        expected.push_back("pie");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_procedures_calls_star_relationship()")
{
    PKB pkb;

    SECTION("return empty")
    {
        REQUIRE(pkb.get_all_procedures_calls_star_relationship().empty());
    }

    pkb.insert_calls("hello", "world");
    pkb.insert_calls("hello", "itsMe");
    pkb.insert_calls("hello", "banana");
    pkb.extract_design();

    SECTION("return 1")
    {
        unordered_map<string, vector<string>> result = pkb.get_all_procedures_calls_star_relationship();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        vector<string> result_values = result["hello"];
        sort(expected.begin(), expected.end());
        sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);
    }

    SECTION("return >1")
    {
        pkb.insert_calls("chocolate", "banana");
        pkb.insert_calls("chocolate", "pie");
        pkb.insert_calls("banana", "pie");
        pkb.extract_design();
        unordered_map<string, vector<string>> result = pkb.get_all_procedures_calls_star_relationship();
        REQUIRE(result.size() == 3);
        vector<string> expected;
        expected.push_back("world");
        expected.push_back("itsMe");
        expected.push_back("banana");
        expected.push_back("pie");
        vector<string> result_values = result["hello"];
        sort(expected.begin(), expected.end());
        sort(result_values.begin(), result_values.end());
        REQUIRE(expected == result_values);

        vector<string> expected2;
        expected2.push_back("pie");
        expected2.push_back("banana");
        vector<string> result_values2 = result["chocolate"];
        sort(expected2.begin(), expected2.end());
        sort(result_values2.begin(), result_values2.end());
        REQUIRE(expected2 == result_values2);

        vector<string> expected3;
        expected3.push_back("pie");
        vector<string> result_values3 = result["banana"];
        sort(expected3.begin(), expected3.end());
        sort(result_values3.begin(), result_values3.end());
        REQUIRE(expected3 == result_values3);
    }
}

TEST_CASE("PKB::get_all_next_relationship()")
{
    PKB pkb;
    SECTION("return 0 relationship")
    {
        REQUIRE(pkb.get_all_next_relationship().empty());
    }

    pkb.insert_next(1, 2);
    pkb.insert_next(2, 3);
    SECTION("return more than 0 relationship")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_next_relationship();
        REQUIRE(result.size() == 2);
        std::unordered_map<int, std::vector<int>> expected;
        std::vector<int> value1;
        std::vector<int> value2;
        value1.push_back(2);
        value2.push_back(3);
        expected.emplace(1, value1);
        expected.emplace(2, value2);
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::insert_modifies_for_call()")
{
    PKB pkb;
    pkb.insert_modifies("main", "x");
    pkb.insert_modifies("procY", "y");
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.insert_modifies_for_call("main", "procX"));
    }
    SECTION("return true")
    {
        pkb.insert_modifies_for_call("main", "procY");
        std::vector<std::string> result = pkb.get_modified_by_procedure("main");
        REQUIRE(pkb.insert_modifies_for_call("main", "procY"));
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("x");
        expected.push_back("y");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::insert_uses_for_call()")
{
    PKB pkb;
    pkb.insert_uses("main", "x");
    pkb.insert_uses("procY", "y");
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.insert_uses_for_call("main", "procX"));
    }
    SECTION("return true")
    {
        pkb.insert_uses_for_call("main", "procY");
        std::vector<std::string> result = pkb.get_used_by_procedure("main");
        REQUIRE(pkb.insert_uses_for_call("main", "procY"));
        REQUIRE(result.size() == 2);
        std::vector<std::string> expected;
        expected.push_back("x");
        expected.push_back("y");
        std::sort(expected.begin(), expected.end());
        std::sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}
