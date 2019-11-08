#include "catch.hpp"
#include "PKB.h"

TEST_CASE("PKB::insert_procedure()")
{
    PKB pkb;

    SECTION("insert success")
    {
        REQUIRE(pkb.insert_procedure("test", 1, {3}));
        REQUIRE(pkb.insert_procedure("extra", 5, {2, 4}));
    }

    SECTION("insert fail")
    {
        REQUIRE(pkb.insert_procedure("test", 1, {3}));
        REQUIRE_FALSE(pkb.insert_procedure("test", 1, {3}));
        REQUIRE_FALSE(pkb.insert_procedure("something", 1, {3}));
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
        pkb.insert_calls(1, "e", "f");
        pkb.insert_calls(2, "f", "h");
        REQUIRE(pkb.extract_design());

        REQUIRE(pkb.is_calls_star("e", "h"));
    }

    SECTION("calls* cyclic")
    {
        pkb.insert_calls(1, "a", "b");
        pkb.insert_calls(2, "b", "a");
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
    pkb.insert_assign(4, "a", "+ b c");

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

    pkb.insert_procedure("main", 1, {3});
    pkb.insert_procedure("procX", 6 , {2, 4});
    pkb.insert_procedure("procX", 1, {3, 5} );

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

TEST_CASE("PKB::does_next_exist()")
{
    PKB pkb;
    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.does_next_exist());
    }

    pkb.insert_next(1, 2);
    SECTION("return true")
    {
        REQUIRE(pkb.does_next_exist());
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
        vector<int> result = pkb.get_statements_previous(3);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        vector<int> result = pkb.get_statements_previous(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statements")
    {
        vector<int> result = pkb.get_statements_previous(10);
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(9);
        expected.push_back(3);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
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
        vector<int> result = pkb.get_statements_next(2);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        vector<int> result = pkb.get_statements_next(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    SECTION("return more than 1 statement")
    {
        vector<int> result = pkb.get_statements_next(3);
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(10);
        expected.push_back(4);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_previous()")
{
    PKB pkb;
    SECTION("return 0 statement")
    {
        vector<int> result = pkb.get_all_previous();
        REQUIRE(result.empty());
    }

    pkb.insert_next(5, 10);
    SECTION("return 1 statement")
    {
        vector<int> result = pkb.get_all_previous();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 5);
    }

    pkb.insert_next(9, 10);
    SECTION("return more than 1 statement")
    {
        vector<int> result = pkb.get_all_previous();
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(5);
        expected.push_back(9);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_all_next()")
{
    PKB pkb;
    SECTION("return 0 statement")
    {
        vector<int> result = pkb.get_all_next();
        REQUIRE(result.empty());
    }

    pkb.insert_next(1, 2);
    SECTION("return 1 statement")
    {
        vector<int> result = pkb.get_all_next();
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 2);
    }

    pkb.insert_next(1, 10);
    SECTION("return more than 1 statement")
    {
        vector<int> result = pkb.get_all_next();
        REQUIRE(result.size() == 2);
        vector<int> expected;
        expected.push_back(2);
        expected.push_back(10);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
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
        vector<int> result = pkb.get_while_stmtLst(3);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 4);
    }
    pkb.insert_stmt_in_while_stmtLst(3, 5);
    pkb.insert_stmt_in_while_stmtLst(3, 6);
    SECTION("return more than 1 statements")
    {
        vector<int> result = pkb.get_while_stmtLst(3);
        REQUIRE(result.size() == 3);
        vector<int> expected;
        expected.push_back(6);
        expected.push_back(5);
        expected.push_back(4);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
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
vector<int> result = pkb.get_while_with_control_var("y");
REQUIRE(result.size() == 1);
REQUIRE(result[0] == 1);
}

SECTION("return more than 0 statements")
{
vector<int> result = pkb.get_while_with_control_var("x");
REQUIRE(result.size() == 2);
vector<int> expected;
expected.push_back(1);
expected.push_back(10);
sort(expected.begin(), expected.end());
sort(result.begin(), result.end());
REQUIRE(expected == result);
}
}

TEST_CASE("PKB::get_all_whilestmt_and_control_var()")
{
PKB pkb;
SECTION("return 0 relationship")
{
unordered_map<int, vector<string>> result = pkb.get_all_whilestmt_and_control_var();
REQUIRE(result.empty());
}

pkb.insert_while(1, {"x", "y"});
pkb.insert_while(10, {"x"});
SECTION("return more than 0 relationships")
{
unordered_map<int, vector<string>> result = pkb.get_all_whilestmt_and_control_var();
REQUIRE(result.size() == 2);
unordered_map<int, vector<string>> expected;
vector<string> value1;
vector<string> value2;
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
        pkb.insert_calls(1, "hello", "hello");
        REQUIRE_FALSE(pkb.does_calls_exist());
    }

    SECTION(">1")
    {
        pkb.insert_calls(1, "hello", "helloWorld");
        REQUIRE(pkb.does_calls_exist());
    }
}

TEST_CASE("PKB::is_calls()")
{
    PKB pkb;
    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "foo", "bar");
    pkb.insert_calls(3, "chocolate", "vanilla");
    pkb.insert_calls(4, "hello", "chocolate");

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
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "bye", "world");
        vector<string> result = pkb.get_all_procedures_calls();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "banana");
        pkb.insert_calls(3, "chocolate", "banana");
        pkb.insert_calls(4, "chocolate", "pie");
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
        vector<int> result = pkb.get_all_if_pattern_contains("y");
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
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "itsMe");
        vector<string> result = pkb.get_all_procedures_called();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "banana");
        pkb.insert_calls(3, "chocolate", "banana");
        pkb.insert_calls(4, "chocolate", "pie");
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
    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "hello", "itsMe");
    pkb.insert_calls(3, "hello", "banana");
    pkb.insert_calls(4, "chocolate", "banana");
    pkb.insert_calls(5, "chocolate", "pie");
    pkb.insert_calls(6, "banana", "pie");

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
        unordered_map<int, vector<string>> expected;
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

    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "hello", "itsMe");
    pkb.insert_calls(3, "hello", "banana");

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
        pkb.insert_calls(1, "chocolate", "banana");
        pkb.insert_calls(2, "chocolate", "pie");
        pkb.insert_calls(3, "banana", "pie");
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
        pkb.insert_calls(1, "hello", "hello");
        pkb.extract_design();
        REQUIRE_FALSE(pkb.does_calls_star_exist());
    }

    SECTION(">1")
    {
        pkb.insert_calls(1, "hello", "helloWorld");
        pkb.extract_design();
        REQUIRE(pkb.does_calls_star_exist());
    }
}

TEST_CASE("PKB::is_calls_star()")
{
    PKB pkb;
    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "foo", "bar");
    pkb.insert_calls(3, "chocolate", "vanilla");
    pkb.insert_calls(4, "hello", "chocolate");
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
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "bye", "world");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_calls_star();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("world");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "banana");
        pkb.insert_calls(3, "chocolate", "banana");
        pkb.insert_calls(4, "chocolate", "pie");
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
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "itsMe");
        pkb.extract_design();
        vector<string> result = pkb.get_all_procedures_called_star();
        REQUIRE(result.size() == 1);
        vector<string> expected;
        expected.push_back("hello");
        REQUIRE(expected == result);
    }

    SECTION("return >1")
    {
        pkb.insert_calls(1, "hello", "world");
        pkb.insert_calls(2, "hello", "banana");
        pkb.insert_calls(3, "chocolate", "banana");
        pkb.insert_calls(4, "chocolate", "pie");
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
    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "hello", "itsMe");
    pkb.insert_calls(3, "hello", "banana");
    pkb.insert_calls(4, "chocolate", "banana");
    pkb.insert_calls(5, "chocolate", "pie");
    pkb.insert_calls(6, "banana", "pie");
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

    pkb.insert_calls(1, "hello", "world");
    pkb.insert_calls(2, "hello", "itsMe");
    pkb.insert_calls(3, "hello", "banana");
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
        pkb.insert_calls(1, "chocolate", "banana");
        pkb.insert_calls(2, "chocolate", "pie");
        pkb.insert_calls(3, "banana", "pie");
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
        unordered_map<int, vector<int>> result = pkb.get_all_next_relationship();
        REQUIRE(result.size() == 2);
        unordered_map<int, vector<int>> expected;
        vector<int> value1;
        vector<int> value2;
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
        vector<string> result = pkb.get_modified_by_procedure("main");
        REQUIRE(pkb.insert_modifies_for_call("main", "procY"));
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("x");
        expected.push_back("y");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
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
        vector<string> result = pkb.get_used_by_procedure("main");
        REQUIRE(pkb.insert_uses_for_call("main", "procY"));
        REQUIRE(result.size() == 2);
        vector<string> expected;
        expected.push_back("x");
        expected.push_back("y");
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);

    }
}

TEST_CASE("PKB::get_all_assigns_affect()")
{
    PKB pkb;
    vector<int> result;
    vector<int> expected;

    SECTION("return 0 statement")
    {
        result = pkb.get_all_assigns_affect();
        REQUIRE(result.empty());
    }

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");
    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return more than 0 statements")
    {
        result = pkb.get_all_assigns_affect();
        REQUIRE(result.size() == 8);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(4);
        expected.push_back(6);
        expected.push_back(8);
        expected.push_back(9);
        expected.push_back(10);
        expected.push_back(11);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_assigns_affect()")
{
    PKB pkb;
    vector<int> result;
    vector<int> expected;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");
    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return 0 statement")
    {
        result = pkb.get_assigns_affect(1);
        REQUIRE(result.empty());
        result = pkb.get_assigns_affect(5);
        REQUIRE(result.empty());
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_assigns_affect(11);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 10);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_assigns_affect(4);
        REQUIRE(result.size() == 2);
        expected.push_back(1);
        expected.push_back(4);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);

        expected.pop_back();
        expected.pop_back();
        result = pkb.get_assigns_affect(12);
        REQUIRE(result.size() == 5);
        expected.push_back(1);
        expected.push_back(4);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(11);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_affects_relationship()")
{
    PKB pkb;

    vector<int> affected1;
    affected1.push_back(4);
    affected1.push_back(8);
    affected1.push_back(10);
    affected1.push_back(12);
    vector<int> affected2;
    affected2.push_back(6);
    affected2.push_back(10);
    vector<int> affected4;
    affected4.push_back(4);
    affected4.push_back(8);
    affected4.push_back(10);
    affected4.push_back(12);
    vector<int> affected6;
    affected6.push_back(6);
    affected6.push_back(10);
    vector<int> affected8;
    affected8.push_back(10);
    affected8.push_back(12);
    vector<int> affected9;
    affected9.push_back(10);
    vector<int> affected10;
    affected10.push_back(11);
    affected10.push_back(12);
    vector<int> affected11;
    affected11.push_back(12);

    unordered_map<int, vector<int>> result;
    unordered_map<int, vector<int>> expected;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");

    SECTION("return empty map")
    {
        result = pkb.get_all_affects_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return non-empty map")
    {
        result = pkb.get_all_affects_relationship();
        expected.emplace(1, affected1);
        expected.emplace(2, affected2);
        expected.emplace(4, affected4);
        expected.emplace(6, affected6);
        expected.emplace(8, affected8);
        expected.emplace(9, affected9);
        expected.emplace(10, affected10);
        expected.emplace(11, affected11);
        for (int i = 1; i <= 15; i++)
        {
            if(result.find(i) != result.end())
            {
                sort(expected.at(i).begin(), expected.at(i).end());
                sort(result.at(i).begin(), result.at(i).end());
                REQUIRE(expected.at(i) == result.at(i));
            }
        }
    }
}

TEST_CASE("PKB::get_all_assigns_affected()")
{
    PKB pkb;
    vector<int> result;
    vector<int> expected;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");

    SECTION("return 0 statement")
    {
        result = pkb.get_all_assigns_affected();
        REQUIRE(result.empty());
    }

    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return more than 0 statement")
    {
        result = pkb.get_all_assigns_affected();
        REQUIRE(result.size() == 6);
        expected.push_back(4);
        expected.push_back(6);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(11);
        expected.push_back(12);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_assigns_affected_by()")
{
    PKB pkb;
    vector<int> result;
    vector<int> expected;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");

    SECTION("return 0 statement")
    {
        result = pkb.get_assigns_affected_by(1);
        REQUIRE(result.empty());
    }

    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return more than 0 statements")
    {
        result = pkb.get_assigns_affected_by(1);
        REQUIRE(result.size() == 4);
        expected.push_back(4);
        expected.push_back(8);
        expected.push_back(10);
        expected.push_back(12);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);

        result = pkb.get_assigns_affected_by(4);
        REQUIRE(result.size() == 4);
        REQUIRE(expected == result);
        expected.clear();

        result = pkb.get_assigns_affected_by(6);
        REQUIRE(result.size() == 2);
        expected.push_back(6);
        expected.push_back(10);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::does_affects_exist()")
{
    PKB pkb;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.does_affects_exist());
    }

    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return true")
    {
        REQUIRE(pkb.does_affects_exist());
    }
}

TEST_CASE("PKB::is_affects()")
{
    PKB pkb;

    pkb.insert_next(1, 2); // Code 5 procedure Second and Third on wiki
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 7);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 3);
    pkb.insert_next(7, 8);
    pkb.insert_next(7, 9);
    pkb.insert_next(8, 10);
    pkb.insert_next(9, 10);
    pkb.insert_next(10, 11);
    pkb.insert_next(11, 12);
    pkb.insert_next(13, 14);
    pkb.insert_next(14, 15);

    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_type(3, EntityType::WHILE);
    pkb.insert_type(4, EntityType::ASSIGN);
    pkb.insert_type(5, EntityType::CALL);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::IF);
    pkb.insert_type(8, EntityType::ASSIGN);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_type(12, EntityType::ASSIGN);
    pkb.insert_type(13, EntityType::ASSIGN);
    pkb.insert_type(14, EntityType::ASSIGN);
    pkb.insert_type(15, EntityType::PRINT);

    pkb.insert_modifies(1, "x");
    pkb.insert_modifies(2, "i");
    pkb.insert_modifies(3, "x");
    pkb.insert_modifies(3, "i");
    pkb.insert_modifies(4, "x");
    pkb.insert_modifies(6, "i");
    pkb.insert_modifies(7, "x");
    pkb.insert_modifies(7, "z");
    pkb.insert_modifies(8, "x");
    pkb.insert_modifies(9, "z");
    pkb.insert_modifies(10, "z");
    pkb.insert_modifies(11, "y");
    pkb.insert_modifies(12, "x");
    pkb.insert_modifies(13, "z");
    pkb.insert_modifies(14, "v");
    pkb.insert_modifies("Third", "z");
    pkb.insert_modifies("Third", "v");

    pkb.insert_uses(3, "i");
    pkb.insert_uses(3, "x");
    pkb.insert_uses(3, "y");
    pkb.insert_uses(3, "v");
    pkb.insert_uses(4, "x");
    pkb.insert_uses(4, "y");
    pkb.insert_uses(5, "v");
    pkb.insert_uses(6, "i");
    pkb.insert_uses(7, "x");
    pkb.insert_uses(8, "x");
    pkb.insert_uses(10, "z");
    pkb.insert_uses(10, "x");
    pkb.insert_uses(10, "i");
    pkb.insert_uses(11, "z");
    pkb.insert_uses(12, "x");
    pkb.insert_uses(12, "y");
    pkb.insert_uses(12, "z");
    pkb.insert_uses(15, "v");

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_affects(9, 11));
        REQUIRE_FALSE(pkb.is_affects(9, 12));
        REQUIRE_FALSE(pkb.is_affects(2, 3));
        REQUIRE_FALSE(pkb.is_affects(9, 6));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.is_affects(2, 6));
        REQUIRE(pkb.is_affects(4, 8));
        REQUIRE(pkb.is_affects(4, 10));
        REQUIRE(pkb.is_affects(6, 6));
        REQUIRE(pkb.is_affects(1, 4));
        REQUIRE(pkb.is_affects(1, 8));
        REQUIRE(pkb.is_affects(1, 10));
        REQUIRE(pkb.is_affects(1, 12));
        REQUIRE(pkb.is_affects(2, 10));
        REQUIRE(pkb.is_affects(9, 10));
        REQUIRE(pkb.is_affects(4, 4));
    }
}

TEST_CASE("PKB::is_affects_star()")
{
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");
    pkb.insert_while(4, {"x"});
    pkb.insert_next(3, 4);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_parent(4, 5);
    pkb.insert_parent(4, 6);
    pkb.insert_assign(5, "forever", "loop");
    pkb.insert_next(4, 5);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_modifies(5, "forever");
    pkb.insert_uses(5, "loop");
    pkb.insert_assign(6, "loop", "+ is true");
    pkb.insert_next(5, 6);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_modifies(6, "loop");
    pkb.insert_uses(6, "is");
    pkb.insert_uses(6, "true");
    pkb.insert_next(6, 7);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_assign(6, "true", "forever");
    pkb.insert_modifies(7, "true");
    pkb.insert_uses(7, "forever");
    pkb.insert_next(7, 8);
    pkb.insert_type(8, EntityType::IF);
    pkb.insert_next(8, 9);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_modifies(9, "if");
    pkb.insert_uses(9, "else");
    pkb.insert_next(8, 10);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_modifies(10, "else");
    pkb.insert_uses(10, "if");
    pkb.insert_next(9, 4);
    pkb.insert_next(10, 4);
    pkb.insert_next(4, 11);
    pkb.insert_type(11, EntityType::ASSIGN);
    pkb.insert_modifies(11, "a");
    pkb.insert_uses(11, "if");

    SECTION("fails")
    {
        REQUIRE_FALSE(pkb.is_affects_star(1, 4));
        REQUIRE_FALSE(pkb.is_affects_star(5, 2));
    }

    SECTION("success")
    {
        REQUIRE(pkb.is_affects_star(1, 2));
        REQUIRE(pkb.is_affects_star(2, 3));
        REQUIRE(pkb.is_affects_star(1, 3));
        REQUIRE(pkb.is_affects_star(6, 5));
        REQUIRE(pkb.is_affects_star(5, 6));
        REQUIRE(pkb.is_affects_star(10, 11));
    }
}

TEST_CASE("PKB::get_affected_star()")
{
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");
    pkb.insert_while(4, {"x"});
    pkb.insert_next(3, 4);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_parent(4, 5);
    pkb.insert_parent(4, 6);
    pkb.insert_assign(5, "forever", "loop");
    pkb.insert_next(4, 5);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_modifies(5, "forever");
    pkb.insert_uses(5, "loop");
    pkb.insert_assign(6, "loop", "+ is true");
    pkb.insert_next(5, 6);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_modifies(6, "loop");
    pkb.insert_uses(6, "is");
    pkb.insert_uses(6, "true");
    pkb.insert_next(6, 7);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_assign(6, "true", "forever");
    pkb.insert_modifies(7, "true");
    pkb.insert_uses(7, "forever");
    pkb.insert_next(7, 8);


    SECTION("fails")
    {
        REQUIRE(pkb.get_affected_star(3).empty());
    }

    SECTION("success")
    {
        vector<int> result = pkb.get_affected_star(1);
        vector<int> expected;
        expected.push_back(2);
        expected.push_back(3);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_affects_star()")
{
    PKB pkb;
    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("fails")
    {
        REQUIRE(pkb.get_affects_star(1).empty());
    }

    SECTION("success")
    {
        vector<int> result = pkb.get_affects_star(3);
        vector<int> expected;
        expected.push_back(2);
        expected.push_back(1);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_affects_star_relationship()")
{
    PKB pkb;

    SECTION("fails")
    {
        REQUIRE(pkb.get_all_affects_star_relationship().empty());
    }

    pkb.insert_assign(1, "x", "+ y z");
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_uses(1, "y");
    pkb.insert_uses(1, "z");
    pkb.insert_modifies(1, "x");
    pkb.insert_assign(2, "h", "+ ello x");
    pkb.insert_next(1, 2);
    pkb.insert_type(2, EntityType::ASSIGN);
    pkb.insert_uses(2, "ello");
    pkb.insert_uses(2, "x");
    pkb.insert_modifies(2, "h");
    pkb.insert_assign(3, "a", "h");
    pkb.insert_next(2, 3);
    pkb.insert_type(3, EntityType::ASSIGN);
    pkb.insert_uses(3, "h");
    pkb.insert_modifies(3, "a");

    SECTION("success")
    {
        unordered_map<int, ::vector<int>> result = pkb.get_all_affects_star_relationship();
        unordered_map<int, ::vector<int>> expected;
        expected.insert({1, {2, 3}});
        expected.insert({2, {3}});
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_statements_previous_star()")
{
    PKB pkb;
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4); // stmt3 is while
    pkb.insert_next(3, 9); // stmt9 is the first stmt out of while stmtList
    pkb.insert_next(4, 5); // stmt4 is if
    pkb.insert_next(4, 7); // stmt7 is in else
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 8); // stmt8 is not in else
    pkb.insert_next(7, 8);
    pkb.insert_next(8, 3);
    pkb.insert_type(9, EntityType::STMT);
    vector<int> result;
    vector<int> expected;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_previous_star(1);
        REQUIRE(result.size() == 0);
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_previous_star(2);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 1);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_previous_star(9);
        REQUIRE(result.size() == 8);
        for(int i = 1; i <= 8; i++)
        {
        expected.push_back(i);
        }
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_statements_next_star()")
{
    PKB pkb;
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(4, 7);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 8);
    pkb.insert_next(7, 8);
    pkb.insert_next(8, 3);
    pkb.insert_next(9, 10);
    pkb.insert_type(10, EntityType::STMT);

    vector<int> result;
    vector<int> expected;

    SECTION("return 0 statement")
    {
        result = pkb.get_statements_next_star(10);
        REQUIRE(result.size() == 0);
    }

    SECTION("return 1 statement")
    {
        result = pkb.get_statements_next_star(9);
        REQUIRE(result.size() == 1);
        REQUIRE(result[0] == 10);
    }

    SECTION("return more than 1 statement")
    {
        result = pkb.get_statements_next_star(3);
        for(int i = 3; i <= 10; i++)
        {
            expected.push_back(i);
        }
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::is_next_star()")
{
    PKB pkb;
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(4, 7);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 8);
    pkb.insert_next(7, 8);
    pkb.insert_next(8, 3);
    pkb.insert_type(9, EntityType::STMT);

    SECTION("return false")
    {
        REQUIRE_FALSE(pkb.is_next_star(2, 1));
        REQUIRE_FALSE(pkb.is_next_star(3, 2));
        REQUIRE_FALSE(pkb.is_next_star(3, 1));
        REQUIRE_FALSE(pkb.is_next_star(10, 9));
        REQUIRE_FALSE(pkb.is_next_star(9, 7));
    }

    SECTION("return true")
    {
        REQUIRE(pkb.is_next_star(3, 3));
        REQUIRE(pkb.is_next_star(5, 5));
        REQUIRE(pkb.is_next_star(6, 3));
        REQUIRE(pkb.is_next_star(7, 9));
        REQUIRE(pkb.is_next_star(5, 7));
    }
}

TEST_CASE("PKB::get_all_next_star_relationship()")
{
    PKB pkb;
    unordered_map<int, vector<int>> result;
    unordered_map<int, vector<int>> expected;
    vector<int> vec;
    vector<int> vec1;
    vector<int> vec2;
    vector<int> vec3;

    SECTION("return empty map")
    {
        result = pkb.get_all_next_star_relationship();
        REQUIRE(result.empty());
    }

    pkb.insert_next(1, 2);

    SECTION("return map with one pair")
    {
        pkb.insert_type(2, EntityType::STMT);
        result = pkb.get_all_next_star_relationship();
        vec.push_back(2);
        expected.emplace(1, vec);
        REQUIRE(result.size() == 1);
        REQUIRE(result.at(1)[0] == 2);
        REQUIRE(result == expected);
    }

    pkb.insert_next(2, 3);
    pkb.insert_next(3, 4);
    pkb.insert_next(3, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(4, 7);
    pkb.insert_next(5, 6);
    pkb.insert_next(6, 8);
    pkb.insert_next(7, 8);
    pkb.insert_next(8, 3);
    pkb.insert_next(9, 10);

    SECTION("return map with more than one pair")
    {
        pkb.insert_type(10, EntityType::STMT);
        result = pkb.get_all_next_star_relationship();
        vec3.push_back(10);
        for(int i = 3; i <= 10; i++)
        {
            vec1.push_back(i);
        }
        for(int i = 2; i <= 10; i++)
        {
            vec2.push_back(i);
        }
        REQUIRE(result.size() == 9);
        for (int i = 1; i <= 9; i++)
        {
            sort(result.at(i).begin(), result.at(i).end());
            if(i == 1)
            {
                REQUIRE(result.at(i) == vec2);
            }
            else if(i == 9)
            {
                REQUIRE(result.at(i) == vec3);
            }
            else
            {
                REQUIRE(result.at(i) == vec1);
            }
        }
    }
}

TEST_CASE("PKB::get_procedure_first_line")
{
    PKB pkb;
    SECTION("no first line")
    {
        REQUIRE(pkb.get_procedure_first_line("a") == -1);
    }

    pkb.insert_procedure("main", 1, {3});
    pkb.insert_procedure("procX", 6 , {2, 4});
    pkb.insert_procedure("procX", 1, {3, 5} );

    SECTION("return first line")
    {
        int result = pkb.get_procedure_first_line("main");
        REQUIRE(1 == result);
    }
}

TEST_CASE("PKB::get_procedure_last_lines")
{
    PKB pkb;
    SECTION("no last_lines")
    {
        REQUIRE(pkb.get_procedure_last_lines("a").empty());
    }

    pkb.insert_procedure("main", 1, {3});
    pkb.insert_procedure("procX", 6 , {2, 4});
    pkb.insert_procedure("procX", 1, {3, 5} );

    SECTION("return last_lines")
    {
        vector<int> result = pkb.get_procedure_last_lines("procX");
        vector<int> expected;
        expected.push_back(4);
        expected.push_back(2);
        sort(expected.begin(), expected.end());
        sort(result.begin(), result.end());
        REQUIRE(expected == result);
          }
}

TEST_CASE("PKB::get_called_by_statement()")
{
    PKB pkb;
    SECTION("fail")
    {
        REQUIRE(pkb.get_called_by_statement(1).empty());
    }
    SECTION("success")
    {
        pkb.insert_calls(1, "hello", "world");
        REQUIRE(pkb.get_called_by_statement(1).compare("world") == 0);
    }
}

TEST_CASE("PKB::get_next_bip")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION("no next bip")
    {
        REQUIRE(pkb.get_next_bip(7).empty());
        REQUIRE(pkb.get_next_bip(0).empty());
    }

    SECTION("1 next bip")
    {
        std::vector<int> result = pkb.get_next_bip(1);
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({2}));
    }

    SECTION(">1 next bip")
    {
        std::vector<int> result = pkb.get_next_bip(4);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({5, 6});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_previous_bip")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION("no previous bip")
    {
        REQUIRE(pkb.get_previous_bip(1).empty());
        REQUIRE(pkb.get_previous_bip(8).empty());
    }

    SECTION("1 previous bip")
    {
        std::vector<int> result = pkb.get_previous_bip(7);
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({6}));
    }

    SECTION(">1 previous bip")
    {
        std::vector<int> result = pkb.get_previous_bip(4);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({5, 2});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_next_bip")
{
    PKB pkb;
    
    SECTION("no next bip")
    {
        REQUIRE(pkb.get_all_next_bip().empty());
    }
    
    pkb.insert_next_bip(1, 2);
   
    SECTION("1 next bip")
    {
        std::vector<int> result = pkb.get_all_next_bip();
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({2}));
    }

    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION(">1 next bip")
    {
        std::vector<int> result = pkb.get_all_next_bip();
        REQUIRE(result.size() == 5);
        std::vector<int> expected({2, 4, 5, 6, 7});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_previous_bip")
{
    PKB pkb;
    
    SECTION("no previous bip")
    {
        REQUIRE(pkb.get_all_previous_bip().empty());
    }
    
    pkb.insert_next_bip(1, 2);
   
    SECTION("1 previous bip")
    {
        std::vector<int> result = pkb.get_all_previous_bip();
        REQUIRE(result.size() == 1);
        REQUIRE(result == std::vector<int>({1}));
    }

    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION(">1 previous bip")
    {
        std::vector<int> result = pkb.get_all_previous_bip();
        REQUIRE(result.size() == 5);
        std::vector<int> expected({2, 4, 5, 6, 1});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_next_bip_relationship")
{
    PKB pkb;
    
    SECTION("no next bip")
    {
        REQUIRE(pkb.get_all_next_bip_relationship().empty());
    }
    
    pkb.insert_next_bip(1, 2);
   
    SECTION("1 next bip")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_next_bip_relationship();
        REQUIRE(result.size() == 1);
        REQUIRE(result[1] == std::vector<int>({2}));
    }

    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION(">1 next bip")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_next_bip_relationship();
        REQUIRE(result.size() == 5);

        std::unordered_map<int, std::vector<int>> expected;
        expected.insert({1, {2}});
        expected.insert({2, {4}});
        expected.insert({4, {5, 6}});
        expected.insert({5, {4}});
        expected.insert({6, {7}});
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::is_next_bip")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.is_next_bip(1, 4));
        REQUIRE_FALSE(pkb.is_next_bip(4, 4));
    }

    SECTION("true")
    {
        REQUIRE(pkb.is_next_bip(1, 2));
        REQUIRE(pkb.is_next_bip(4, 6));
    }
}

TEST_CASE("PKB::does_next_bip_exists")
{
    PKB pkb;

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.does_next_bip_exists());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);

    SECTION("true")
    {
        REQUIRE(pkb.does_next_bip_exists());
    }
}

TEST_CASE("PKB::is_next_bip_star")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 6);
    pkb.insert_next(6, 7);
    pkb.insert_next(8, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 4);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);

    SECTION("fail")
    {
        REQUIRE_FALSE(pkb.is_next_bip_star(4, 2));
        REQUIRE_FALSE(pkb.is_next_bip_star(1, 9));
        REQUIRE_FALSE(pkb.is_next_bip_star(8, 7));
    }

    SECTION("success")
    {
        REQUIRE(pkb.is_next_bip_star(1, 7));
        REQUIRE(pkb.is_next_bip_star(4, 7));
        REQUIRE(pkb.is_next_bip_star(5, 5));
        REQUIRE(pkb.is_next_bip_star(4, 4));
        REQUIRE(pkb.is_next_bip_star(5, 9));
        REQUIRE(pkb.is_next_bip_star(5, 9));
    }
}

TEST_CASE("PKB::get_next_bip_star")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 6);
    pkb.insert_next(6, 7);
    pkb.insert_next(8, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 4);

    SECTION("empty")
    {
        REQUIRE(pkb.get_next_bip_star(7).empty());
    }

    SECTION(">1")
    {
        std::vector<int> result = pkb.get_next_bip_star(5);
        REQUIRE(result.size() == 5);
        std::vector<int> expected({9, 4, 5, 6, 7});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);

        std::vector<int> result1 = pkb.get_next_bip_star(2);
        REQUIRE(result1.size() == 4);
        std::vector<int> expected1({ 4, 5, 6, 7});
        std::sort(result1.begin(), result1.end());
        std::sort(expected1.begin(), expected1.end());
        REQUIRE(expected1 == result1);
    }
}

TEST_CASE("PKB::get_previous_bip_star")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 6);
    pkb.insert_next(6, 7);
    pkb.insert_next(8, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 4);

    SECTION("empty")
    {
        REQUIRE(pkb.get_previous_bip_star(8).empty());
    }

    SECTION(">1")
    {
        std::vector<int> result = pkb.get_previous_bip_star(9);
        REQUIRE(result.size() == 3);
        std::vector<int> expected({4, 5, 8});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);

        std::vector<int> result1 = pkb.get_previous_bip_star(4);
        REQUIRE(result1.size() == 5);
        std::vector<int> expected1({1, 2, 8, 5, 4});
        std::sort(result1.begin(), result1.end());
        std::sort(expected1.begin(), expected1.end());
        REQUIRE(expected1 == result1);
    }
}

TEST_CASE("PKB::get_all_next_bip_star_relationship")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_next_bip_star_relationship().empty());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_next(1, 2);
    pkb.insert_next(2, 6);
    pkb.insert_next(6, 7);
    pkb.insert_next(8, 9);
    pkb.insert_next(4, 5);
    pkb.insert_next(5, 4);

    SECTION(">1")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_next_bip_star_relationship();
        std::unordered_map<int, std::vector<int>> expected;
        expected.insert({1, {2, 4, 5, 6, 7}});
        expected.insert({2, {4, 5, 6, 7}});
        expected.insert({4, {4, 5, 6, 7, 9}});
        expected.insert({5, {4, 5, 6, 7, 9}});
        expected.insert({6, {7}});
        expected.insert({8, {4, 5, 9}});
        REQUIRE(result.size() == 6);
        for (auto result_pair : result)
        {
            auto result_values = result_pair.second;
            auto expected_values = expected[result_pair.first];
            std::sort(result_values.begin(), result_values.end());
            std::sort(expected_values.begin(), expected_values.end());
            REQUIRE(expected_values == result_values);
        }
    }
}

TEST_CASE("PKB::is_affects_bip()", "[.]")
{
    PKB pkb;

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.is_affects_bip(1, 9));
        REQUIRE_FALSE(pkb.is_affects_bip(7, 1));
    }

    SECTION("true")
    {
        REQUIRE(pkb.is_affects_bip(5, 5));
        REQUIRE(pkb.is_affects_bip(1, 6));
        REQUIRE(pkb.is_affects_bip(6, 7));
        REQUIRE(pkb.is_affects_bip(10, 9));
    }
}

TEST_CASE("PKB::get_all_assigns_affects_bip()", "[.]")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_assigns_affects_bip().empty());
    }
    
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION(">1")
    {
       std::vector<int> result = pkb.get_all_assigns_affects_bip();
         REQUIRE(result.size() == 4);
        std::vector<int> expected({1, 5, 6, 10});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_assigns_affected_bip()", "[.]")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_assigns_affected_bip().empty());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION(">1")
    {
        std::vector<int> result = pkb.get_all_assigns_affected_bip();
        REQUIRE(result.size() == 4);
        std::vector<int> expected({5, 6, 7, 9});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_affects_bip_relationship()", "[.]")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_affects_bip_relationship().empty());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION(">1")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_affects_bip_relationship();
        REQUIRE(result.size() == 4);
        std::unordered_map<int, std::vector<int>>  expected;
        expected.insert({1, {6}});
        expected.insert({5, {5}});
        expected.insert({6, {7}});
        expected.insert({10, {9}});
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::does_affects_bip_exist()", "[.]")
{
    PKB pkb;

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.does_affects_bip_exist());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION("true")
    {
        REQUIRE(pkb.does_affects_bip_exist());
    }
}

TEST_CASE("PKB::get_assigns_affected_bip_by()", "[.]")
{
    PKB pkb;

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION("empty")
    {
        REQUIRE(pkb.get_assigns_affected_bip_by(2).empty());
        REQUIRE(pkb.get_assigns_affected_bip_by(9).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(pkb.get_assigns_affected_bip_by(10) == std::vector<int>({9}));
        REQUIRE(pkb.get_assigns_affected_bip_by(5) == std::vector<int>({5}));
    }
}

TEST_CASE("PKB::get_assigns_affects_bip()", "[.]")
{
    PKB pkb;

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");


    SECTION("empty")
    {
        REQUIRE(pkb.get_assigns_affects_bip(2).empty());
        REQUIRE(pkb.get_assigns_affects_bip(10).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(pkb.get_assigns_affects_bip(9) == std::vector<int>({10}));
        REQUIRE(pkb.get_assigns_affects_bip(5) == std::vector<int>({5}));
    }
}

TEST_CASE("PKB::is_affects_bip_star()", "[.]")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");

    SECTION("false")
    {
        REQUIRE_FALSE(pkb.is_affects_bip_star(1, 9));
        REQUIRE_FALSE(pkb.is_affects_bip_star(10, 7));
        REQUIRE_FALSE(pkb.is_affects_bip_star(5, 7));
    }

    SECTION("true")
    {
        REQUIRE(pkb.is_affects_bip_star(1, 7));
        REQUIRE(pkb.is_affects_bip_star(5, 5));
    }
}

TEST_CASE("PKB::get_affects_bip_star()", "[.]")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");
    
    SECTION("empty")
    {
        REQUIRE(pkb.get_affects_bip_star(2).empty());
        REQUIRE(pkb.get_affects_bip_star(10).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(pkb.get_affects_bip_star(5) == std::vector<int>({5}));
        REQUIRE(pkb.get_affects_bip_star(9) == std::vector<int>({10}));
        std::vector<int> result = pkb.get_affects_bip_star(7);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({1, 6});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_affected_bip_star()", "[.]")
{
    PKB pkb;
    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");

    SECTION("empty")
    {
        REQUIRE(pkb.get_affected_bip_star(2).empty());
        REQUIRE(pkb.get_affected_bip_star(9).empty());
    }

    SECTION("return 1")
    {
        REQUIRE(pkb.get_affected_bip_star(5) == std::vector<int>({5}));
        REQUIRE(pkb.get_affected_bip_star(10) == std::vector<int>({9}));
        std::vector<int> result = pkb.get_affected_bip_star(1);
        REQUIRE(result.size() == 2);
        std::vector<int> expected({7, 6});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(expected == result);
    }
}

TEST_CASE("PKB::get_all_affects_bip_star_relationship()", "[.]")
{
    PKB pkb;

    SECTION("empty")
    {
        REQUIRE(pkb.get_all_affects_bip_star_relationship().empty());
    }

    pkb.insert_next_bip(1, 2);
    pkb.insert_next_bip(2, 4);
    pkb.insert_next_bip(4, 5);
    pkb.insert_next_bip(4, 6);
    pkb.insert_next_bip(5, 4);
    pkb.insert_next_bip(6, 7);
    pkb.insert_next_bip(8, 4);
    pkb.insert_next_bip(4, 9);
    pkb.insert_next_bip(10, 8);
    pkb.insert_type(1, EntityType::ASSIGN);
    pkb.insert_type(2, EntityType::CALL);
    pkb.insert_type(4, EntityType::WHILE);
    pkb.insert_type(5, EntityType::ASSIGN);
    pkb.insert_type(6, EntityType::ASSIGN);
    pkb.insert_type(7, EntityType::ASSIGN);
    pkb.insert_type(8, EntityType::CALL);
    pkb.insert_type(9, EntityType::ASSIGN);
    pkb.insert_type(10, EntityType::ASSIGN);
    pkb.insert_call_ingress_egress(2, 6);
    pkb.insert_call_ingress_egress(8, 9);
    pkb.insert_modifies(1, "one");
    pkb.insert_modifies(5, "five");
    pkb.insert_modifies(6, "yellow");
    pkb.insert_modifies(7, "one");
    pkb.insert_modifies(9, "one");
    pkb.insert_modifies(10, "red");
    pkb.insert_uses(1, "yellow");
    pkb.insert_uses(5, "five");
    pkb.insert_uses(6, "one");
    pkb.insert_uses(7, "yellow");
    pkb.insert_uses(9, "red");
    pkb.insert_uses(9, "one");

    pkb.insert_uses(2, "five");
    pkb.insert_uses(4, "five");
    pkb.insert_uses(8, "five");
    pkb.insert_modifies(2, "five");
    pkb.insert_modifies(4, "five");
    pkb.insert_modifies(8, "five");

    SECTION(">1")
    {
        std::unordered_map<int, std::vector<int>> result = pkb.get_all_affects_bip_star_relationship();
        REQUIRE(result.size() == 4);
        std::unordered_map<int, std::vector<int>>  expected;
        expected.insert({1, {6, 7}});
        expected.insert({5, {5}});
        expected.insert({6, {7}});
        expected.insert({10, {9}});
        for (auto result_pair : result)
        {
            auto result_values = result_pair.second;
            auto expected_values = expected[result_pair.first];
            std::sort(result_values.begin(), result_values.end());
            std::sort(expected_values.begin(), expected_values.end());
            REQUIRE(expected_values == result_values);
        }
    }
}
