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

TEST_CASE("PKB::insert_modifies()")
{
    PKB pkb;

    // TODO
}

TEST_CASE("PKB::get_all_variables()")
{
    PKB pkb;
    // TODO: STUB
    SECTION("get empty")
    {
        REQUIRE(pkb.get_all_variables().empty());
    }

    SECTION("get >1")
    {
        pkb.insert_variable("test");
        pkb.insert_variable("test");
        pkb.insert_variable("extra");        
        auto result = pkb.get_all_variables();
        REQUIRE(result.size() == 2);
        unordered_set<string> expected({"test", "extra"});
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("PKB::get_statement_type()")
{
    PKB pkb;
    // TODO: STUB
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
    // TODO: STUB
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

TEST_CASE("PKB::get_all_procedures()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_statements_modifies()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_procedures_modifies()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_modified_by_statement()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_modified_by_procedure()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_statements_uses()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_procedures_uses()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_used_by_statement()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_used_by_procedure()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_uses()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_modifies()")
{
    PKB pkb;
}

TEST_CASE("PKB::insert_follows()")
{
    PKB pkb;
}

TEST_CASE("PKB::extract_design()")
{
    PKB pkb;
}

TEST_CASE("PKB::insert_parent()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_follows_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_followed_star_by()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_parent_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_children_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_follows()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_followed_by()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_parent()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_children()")
{
    PKB pkb;
}

TEST_CASE("PKB::insert_assign()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_assign_pattern_matches()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_assign_pattern_contains()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_assign_pattern_matches()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_assign_pattern_contains()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_parent_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_follows_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_parent_star_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_follows_star_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_follows_exist()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_follows_star_exist()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_parent_exist()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_parent_star_exist()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_follows()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_followed()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_parent()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_children()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_follows()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_parent()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_follows_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::is_parent_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_follows_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_followed_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_parent_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_children_star()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_modifies_procedures()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_modifies_statements()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_uses_procedures()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_uses_statements()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_modifies_procedures_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_modifies_statements_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_uses_procedures_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_uses_statements_relationship()")
{
    PKB pkb;
}

TEST_CASE("PKB::assign_to_variable()")
{
    PKB pkb;
}

TEST_CASE("PKB::assigns_to_variables()")
{
    PKB pkb;
}

TEST_CASE("PKB::insert_type()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_whiles()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_ifs()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_assigns()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_reads()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_prints()")
{
    PKB pkb;
}

TEST_CASE("PKB::get_all_calls()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_uses_exist()")
{
    PKB pkb;
}

TEST_CASE("PKB::does_modifies_exist()")
{
    PKB pkb;
}
