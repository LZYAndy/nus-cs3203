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

    SECTION("Multiple such that, pattern and with clause with prog_line.")
    {
        std::string test_query = "if ifs; prog_line n; while w; variable v; Select v pattern ifs (v,_,_) pattern w(v,_) such that Follows(n, ifs) and Modifies(n, \"x\") with v.varName = \"variable\" and ifs.stmt# = 5 and 6 = n";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 2);
        CHECK(with_clause.size() == 3);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 5);
    }

    SECTION("Multiple such that, pattern and with clause with prog_line.")
    {
        std::string test_query = "if ifs; prog_line n; while w; variable v; Select v pattern ifs (v,_,_) pattern w(v,_) such that Next(n, ifs) and Modifies(n, \"x\") with v.varName = \"variable\" and ifs.stmt# = 5 and 6 = n";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 2);
        CHECK(with_clause.size() == 3);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 2);
        REQUIRE(synonym_clauses.size() == 5);
    }

    SECTION("Multiple such that and with clause does not replace call, read and print.")
    {
        std::string test_query = "print prt; call c1, c2; read r; Select <c1, r, prt> such that Modifies(c1, \"compute\") and Modifies(r, \"x\") and Uses(prt, \"y\") with c1.procName = \"MethodA\" and prt.stmt# = 5 with r.varName = \"c\"";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 3);
        CHECK(such_that_clause.size() == 3);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 3);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        REQUIRE(no_synonym_clauses.size() == 0);
        REQUIRE(synonym_clauses.size() == 6);
    }
}

//TEST_CASE("Optimizer add solution to select synonyms correctly.")
//{
//    std::vector<pql_dto::Entity> select_clause;
//    std::vector<pql_dto::Relationships> such_that_clause;
//    std::vector<pql_dto::Pattern> pattern_clause;
//    std::vector<pql_dto::With> with_clause;
//    std::deque<pql_dto::Constraint> no_synonym_clauses;
//    std::deque<pql_dto::Constraint> synonym_clauses;

//    SECTION("1 select and 1 with clause.")
//    {
//        std::string test_query = "variable v; Select v with v.varName = \"variable\"";
//        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);
//
//        CHECK(select_clause.size() == 1);
//        CHECK(such_that_clause.size() == 0);
//        CHECK(pattern_clause.size() == 0);
//        CHECK(with_clause.size() == 1);
//
//        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
//
//        pql_dto::Entity select_var = select_clause.at(0);
//        pql_dto::Entity expected_entity = pql_dto::Entity("variable", "v", true);
//        expected_entity.set_entity_type(EntityType::FIX);
//        expected_entity.set_solution("variable");
//
//        REQUIRE(select_var.equals(expected_entity));
//    }

//    SECTION("2 same select and 1 with clause.")
//    {
//        std::string test_query = "variable v; stmt s; Select <v,s,v> with v.varName = \"variable\"";
//        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);
//
//        CHECK(select_clause.size() == 3);
//        CHECK(such_that_clause.size() == 0);
//        CHECK(pattern_clause.size() == 0);
//        CHECK(with_clause.size() == 1);
//
//        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
//
//        pql_dto::Entity select_var_1 = select_clause.at(0);
//        pql_dto::Entity select_var_2 = select_clause.at(2);
//        pql_dto::Entity expected_entity = pql_dto::Entity("variable", "v", true);
//        expected_entity.set_entity_type(EntityType::FIX);
//        expected_entity.set_solution("variable");
//
//        REQUIRE(select_var_1.equals(expected_entity));
//        REQUIRE(select_var_2.equals(expected_entity));
//    }

//    SECTION("2 diff select and 2 with clause.")
//    {
//        std::string test_query = "stmt s; procedure p; Select <s,p> with p.procName = \"variable\" and s.stmt# = 7";
//        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);
//
//        CHECK(select_clause.size() == 2);
//        CHECK(such_that_clause.size() == 0);
//        CHECK(pattern_clause.size() == 0);
//        CHECK(with_clause.size() == 2);
//
//        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
//
//        pql_dto::Entity select_var_1 = select_clause.at(0);
//        pql_dto::Entity select_var_2 = select_clause.at(1);
//
//        pql_dto::Entity expected_entity_1 = pql_dto::Entity("stmt", "s", true);
//        expected_entity_1.set_entity_type(EntityType::FIX);
//        expected_entity_1.set_solution("7");
//
//        pql_dto::Entity expected_entity_2 = pql_dto::Entity("procedure", "p", true);
//        expected_entity_2.set_entity_type(EntityType::FIX);
//        expected_entity_2.set_solution("variable");
//
//        REQUIRE(select_var_1.equals(expected_entity_1));
//        REQUIRE(select_var_2.equals(expected_entity_2));
//    }
//}

TEST_CASE("Optimizer splits clauses into groups in select and not in select correctly.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;

    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    std::vector<std::vector<pql_dto::Constraint>> synonyms_in_select_clause;
    std::vector<std::vector<pql_dto::Constraint>> synonyms_not_in_select_clause;

    SECTION("1 in select and 1 not in select with clause.")
    {
        std::string test_query = "variable v; procedure p, p1; Select v with v.varName = \"variable\" with p.procName = p1.procName";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 2);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        
        CHECK(synonym_clauses.size() == 2);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 1);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 1);
        REQUIRE(synonyms_not_in_select_clause.size() == 1);
        REQUIRE(synonyms_not_in_select_clause.at(0).size() == 1);
    }

    SECTION("None in select clause.")
    {
        std::string test_query = "variable v; procedure p, p1; Select v with p.procName = p1.procName such that Calls(p, p1) and Modifies(p, \"v\")";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 1);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 3);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 0);
        REQUIRE(synonyms_not_in_select_clause.size() == 1);
        REQUIRE(synonyms_not_in_select_clause.at(0).size() == 3);
    }

    SECTION("Two diff groups not in select clause.")
    {
        std::string test_query = "assign a; variable v; procedure p, p1; Select v with p.procName = p1.procName such that Calls(p, p1) and Modifies(p, \"v\") pattern a(\"x\", \"x\")";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 2);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 1);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 4);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 0);
        REQUIRE(synonyms_not_in_select_clause.size() == 2);
        REQUIRE(synonyms_not_in_select_clause.at(0).size() == 3);
        REQUIRE(synonyms_not_in_select_clause.at(1).size() == 1);
    }

    SECTION("All in select clause.")
    {
        std::string test_query = "variable v; procedure p, p1; Select v with v.varName = \"variable\" with p.procName = p1.procName and v.varName = p.procName";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 3);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 3);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 1);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 3);
        REQUIRE(synonyms_not_in_select_clause.size() == 0);
    }

    SECTION("Two diff groups in select clause.")
    {
        std::string test_query = "stmt s, s1; read r1; assign a; constant c; Select <a,c> such that Follows*(a, s) and Affects(a, 6) with s1.stmt# = c.value such that Parent(s1, r1)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 2);
        CHECK(such_that_clause.size() == 3);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 1);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 4);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 2);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 2);
        REQUIRE(synonyms_in_select_clause.at(1).size() == 2);
        REQUIRE(synonyms_not_in_select_clause.size() == 0);
    }

    SECTION("Multiple links in select clause.")
    {
        std::string test_query = "stmt s, s1, s2, s3, s4, s5, s6; Select s1 such that Follows(s6, s5) and Follows(s4, s3) and Follows(s6, s2) and Follows(s1, s4) and Follows(s3, s5) and Follows(6, s3)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 6);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 6);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 1);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 6);
        REQUIRE(synonyms_not_in_select_clause.size() == 0);
    }

    SECTION("Multiple links in with and pattern clause.")
    {
        std::string test_query = "assign a; stmt s, s1, s2, s3, s4, s5, s6; Select s1 with a.stmt# = s5.stmt# and s6.stmt# = s5.stmt# and s4.stmt# = s3.stmt# and s6.stmt# = s2.stmt# and s4.stmt# = s5.stmt# and s2.stmt# = s1.stmt# ";
        test_query += "pattern a (_,_)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 7);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 1);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 7);
        REQUIRE(synonyms_not_in_select_clause.size() == 0);
    }

    SECTION("Two diff multiple links in select clause.")
    {
        std::string test_query = "assign a, a1, a2, a3, a4, a5, a6, a7; stmt s, s1, s2, s3, s4, s5, s6; Select <s1, a7> with a.stmt# = s5.stmt# and s6.stmt# = s5.stmt# ";
        test_query += "and s4.stmt# = s3.stmt# and s6.stmt# = s2.stmt# and s4.stmt# = s5.stmt# and s2.stmt# = s1.stmt# ";
        test_query += "pattern a (_,_) such that Follows(a6, a5) and Follows(a4, a3) and Follows(a6, a2) and Follows(a7, a4) and Follows(a3, a5) and Follows(6, a3)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 2);
        CHECK(such_that_clause.size() == 6);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 13);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 2);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 6);
        REQUIRE(synonyms_in_select_clause.at(1).size() == 7);
        REQUIRE(synonyms_not_in_select_clause.size() == 0);
    }

    SECTION("Two diff multiple links 1 in select clause and 1 not in select clause.")
    {
        std::string test_query = "assign a, a1, a2, a3, a4, a5, a6, a7; stmt s, s1, s2, s3, s4, s5, s6; Select <s1> with a.stmt# = s5.stmt# and s6.stmt# = s5.stmt# ";
        test_query += "and s4.stmt# = s3.stmt# and s6.stmt# = s2.stmt# and s4.stmt# = s5.stmt# and s2.stmt# = s1.stmt# ";
        test_query += "pattern a (_,_) such that Follows(a6, a5) and Follows(a4, a3) and Follows(a6, a2) and Follows(a7, a4) and Follows(a3, a5) and Follows(6, a3)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 6);
        CHECK(pattern_clause.size() == 1);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);

        CHECK(synonym_clauses.size() == 13);

        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        REQUIRE(synonyms_in_select_clause.size() == 1);
        REQUIRE(synonyms_in_select_clause.at(0).size() == 7);
        REQUIRE(synonyms_not_in_select_clause.size() == 1);
        REQUIRE(synonyms_not_in_select_clause.at(0).size() == 6);
    }
}

TEST_CASE("Optimizer sorts clauses correctly without table size.")
{
    std::vector<pql_dto::Entity> select_clause;
    std::vector<pql_dto::Relationships> such_that_clause;
    std::vector<pql_dto::Pattern> pattern_clause;
    std::vector<pql_dto::With> with_clause;

    std::deque<pql_dto::Constraint> no_synonym_clauses;
    std::deque<pql_dto::Constraint> synonym_clauses;

    std::vector<std::vector<pql_dto::Constraint>> synonyms_in_select_clause;
    std::vector<std::vector<pql_dto::Constraint>> synonyms_not_in_select_clause;

    Cache cache;

    SECTION("Sorting test 1.")
    {
        std::string test_query = "variable v; procedure p, p1; Select v with v.varName = \"variable\" with p.procName = p1.procName";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 2);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        CHECK(synonyms_in_select_clause.size() == 1);
        CHECK(synonyms_in_select_clause.at(0).size() == 1);
        CHECK(synonyms_not_in_select_clause.size() == 1);
        CHECK(synonyms_not_in_select_clause.at(0).size() == 1);

        std::vector<pql_dto::Constraint> entity_group_1 = synonyms_in_select_clause.at(0);
        std::vector<pql_dto::Constraint> entity_group_2 = synonyms_not_in_select_clause.at(0);

        Optimizer::sort(entity_group_1, cache);
        Optimizer::sort(entity_group_2, cache);

        REQUIRE(entity_group_1.size() == 1);
        REQUIRE(entity_group_2.size() == 1);
    }

    SECTION("Sorting test 2.")
    {
        std::string test_query = "stmt s, s1, s2, s3, s4, s5, s6; Select s1 such that Follows(s6, s5) and Follows(s4, s3) and Follows(s6, s2) and Follows(s1, s4) and Follows(s3, s5) and Follows(6, s3)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 6);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);
        
        std::vector<pql_dto::Constraint> entity_group = synonyms_in_select_clause.at(0);
        Optimizer::sort(entity_group, cache);

        REQUIRE(entity_group.size() == 6);
        /*REQUIRE(entity_group.at(0).equals(synonyms_in_select_clause.at(0).at(3)));
        REQUIRE(entity_group.at(1).equals(synonyms_in_select_clause.at(0).at(4)));
        REQUIRE(entity_group.at(2).equals(synonyms_in_select_clause.at(0).at(2)));
        REQUIRE(entity_group.at(3).equals(synonyms_in_select_clause.at(0).at(0)));
        REQUIRE(entity_group.at(4).equals(synonyms_in_select_clause.at(0).at(5)));
        REQUIRE(entity_group.at(5).equals(synonyms_in_select_clause.at(0).at(1)));*/
    }

    SECTION("Sorting test 3.")
    {
        std::string test_query = "stmt s, s1, s2, s3, s4, s5, s6; Select s1 such that Follows(s6, s5) and Follows(s4, s3) and Follows(s6, s1) and Follows(s1, s4) and Follows(s3, s4) and Follows(6, s3)";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 6);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 0);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        std::vector<pql_dto::Constraint> entity_group = synonyms_in_select_clause.at(0);
        Optimizer::sort(entity_group, cache);

        REQUIRE(entity_group.size() == 6);
        /*REQUIRE(entity_group.at(0).equals(synonyms_in_select_clause.at(0).at(1)));
        REQUIRE(entity_group.at(1).equals(synonyms_in_select_clause.at(0).at(0)));
        REQUIRE(entity_group.at(2).equals(synonyms_in_select_clause.at(0).at(2)));
        REQUIRE(entity_group.at(3).equals(synonyms_in_select_clause.at(0).at(3)));
        REQUIRE(entity_group.at(4).equals(synonyms_in_select_clause.at(0).at(4)));
        REQUIRE(entity_group.at(5).equals(synonyms_in_select_clause.at(0).at(5)));*/
    }

    SECTION("Sorting test 4.")
    {
        std::string test_query = "stmt s, s1, s2, s3, s4, s5, s6; Select s1 with 6 = s5.stmt# and s6.stmt# = s5.stmt# and s4.stmt# = s3.stmt# and s5.stmt# = s1.stmt# and s4.stmt# = s5.stmt# and s1.stmt# = 4";
        std::string error = PQLParser::pql_parse_query(test_query, select_clause, such_that_clause, pattern_clause, with_clause);

        CHECK(select_clause.size() == 1);
        CHECK(such_that_clause.size() == 0);
        CHECK(pattern_clause.size() == 0);
        CHECK(with_clause.size() == 6);

        error = Optimizer::split_clauses_with_no_synonyms(select_clause, such_that_clause, pattern_clause, with_clause, no_synonym_clauses, synonym_clauses);
        error = Optimizer::split_clauses_into_groups(select_clause, synonym_clauses, synonyms_in_select_clause, synonyms_not_in_select_clause);

        std::vector<pql_dto::Constraint> entity_group = synonyms_in_select_clause.at(0);
        Optimizer::sort(entity_group, cache);

        REQUIRE(entity_group.size() == 6);
        /*REQUIRE(entity_group.at(0).equals(synonyms_in_select_clause.at(0).at(0)));
        REQUIRE(entity_group.at(1).equals(synonyms_in_select_clause.at(0).at(4)));
        REQUIRE(entity_group.at(2).equals(synonyms_in_select_clause.at(0).at(2)));
        REQUIRE(entity_group.at(3).equals(synonyms_in_select_clause.at(0).at(1)));
        REQUIRE(entity_group.at(4).equals(synonyms_in_select_clause.at(0).at(3)));
        REQUIRE(entity_group.at(5).equals(synonyms_in_select_clause.at(0).at(5)));*/
    }
}
