#include "catch.hpp"
#include "PQLParser.h"
#include "Optimizer.h"

TEST_CASE("Optimizer split no synonym clause correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;
    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    SECTION("3 synonym clauses and 2 no synonym such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, v) and Follows(1,2) and Uses(6, v) and Parent(3, 4) such that Modifies(5,v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("2 synonym clauses and 3 no synonym such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, \"v\") and Follows(1,2) and Uses(6, v) and Parent(3, 4) such that Modifies(5,v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 3);
        REQUIRE(synonym_clauses.size() == 2);
    }

    SECTION("5 pattern clauses.")
    {
        std::string test_query = "assign a; if ifs; while w; Select a pattern a(_,_) and ifs (_,_,_) and w (_,_) pattern w (\"v\", _) pattern a (\"x\", _\"x+u\"_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 5);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 5);
    }

    SECTION("5 with clauses.")
    {
        std::string test_query = "assign a, a1; if ifs; procedure proc; variable v; Select a with a.stmt# = 6 and ifs.stmt# = 5 with a1.stmt# = 1 and v.varName = \"y\" and proc.procName = \"main\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 5);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 5);
    }
}

TEST_CASE("Optimizer split remove duplicates correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;
    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    SECTION("3 same clauses and 2 other different such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, v) and Follows(1,2) and Modifies(6, v) and Parent(3, 4) such that Modifies(6,v)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 1);
    }

    SECTION("5 same such that clauses.")
    {
        std::string test_query = "variable v; Select v such that Follows(1,2) and Follows(1,2) and Follows(1,2) and Follows(1,2) such that Follows(1,2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 5);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 1);
        REQUIRE(synonym_clauses.size() == 0);
    }

    SECTION("2 same and 1 different pattern clauses.")
    {
        std::string test_query = "assign a; if ifs; while w; Select a pattern a (\"x\", _\"x+u\"_) and ifs (_,_,_) and w (\"v\", _) pattern w (\"v\", _) pattern a (\"x\", _\"x+u\"_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 5);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("5 same pattern clauses.")
    {
        std::string test_query = "assign a; if ifs; while w; Select a pattern ifs (_,_,_) and ifs (_,_,_) and ifs (_,_,_) pattern ifs (_,_,_) pattern ifs (_,_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 5);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 1);
    }

    SECTION("3 sets of same with clauses.")
    {
        std::string test_query = "assign a, a1; if ifs; procedure proc; variable v; Select a with a.stmt# = 6 and ifs.stmt# = 5 and ifs.stmt# = 5 with a.stmt# = 6 and v.varName = \"y\" and v.varName = \"y\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("3 sets of same with clauses permutated.")
    {
        std::string test_query = "assign a, a1; if ifs; procedure proc; variable v; Select a with 6 = a.stmt# and 5 = ifs.stmt# and ifs.stmt# = 5 with a.stmt# = 6 and \"y\" = v.varName and v.varName = \"y\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("1 sets of same with clauses, 1 set same relationship and 1 set same pattern.")
    {
        std::string test_query = "assign a, a1; if ifs; procedure proc; variable v; Select a with 6 = a.stmt# pattern ifs (_,_,_) and ifs (_,_,_)  with a.stmt# = 6 such that Follows(1,2) and Follows(1,2)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 2);
        CHECK(with_clause.size() == 2);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 1);
        REQUIRE(synonym_clauses.size() == 2);
    }
}

TEST_CASE("Optimizer replaces with synonyms correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;
    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    SECTION("1 such that and 1 with clause.")
    {
        std::string test_query = "variable v; Select v such that Modifies(6, v) with v.varName = \"variable\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 1);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 1);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 1);
        REQUIRE(synonym_clauses.size() == 1);
    }

    SECTION("1 pattern and 1 with clause.")
    {
        std::string test_query = "assign a; variable v; Select v pattern a (v,_) with v.varName = \"variable\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 1);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        
        pql_dto::Pattern pattern = pattern_clause.at(0);
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "variable", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Pattern expected_pattern = pql_dto::Pattern(pattern_entity, first_param_entity, second_param_entity);

        REQUIRE(pattern.equals(expected_pattern));
        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 2);
    }

    SECTION("1 such that, 1 pattern and 1 with clause.")
    {
        std::string test_query = "assign a; variable v; Select v pattern a (v,_) such that Follows(a, 6) with v.varName = \"variable\" and a.stmt# = 5";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 1);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 2);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        pql_dto::Pattern pattern = pattern_clause.at(0);
        pql_dto::Entity pattern_entity = pql_dto::Entity("assign", "a", true);
        pql_dto::Entity first_param_entity = pql_dto::Entity("variable", "variable", false);
        pql_dto::Entity second_param_entity = pql_dto::Entity("any", "_", false);
        pql_dto::Pattern expected_pattern = pql_dto::Pattern(pattern_entity, first_param_entity, second_param_entity);

        REQUIRE(pattern.equals(expected_pattern));
        REQUIRE(no_synonym_clauses.size() == 1);
        REQUIRE(synonym_clauses.size() == 3);
    }

    SECTION("Multiple such that, pattern and with clause.")
    {
        std::string test_query = "assign a; stmt s; while w; variable v; Select v pattern a (v,_) pattern w(v,_) such that Follows(a, s) and Modifies(s, \"x\") with v.varName = \"variable\" and a.stmt# = 5 and 6 = s.stmt#";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 2);
        CHECK(with_clause.size() == 3);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 5);
    }
}