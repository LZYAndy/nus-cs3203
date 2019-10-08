#include "catch.hpp"
#include "CallParser.h"
#include "pql_dto/Entity.h"

TEST_CASE("CallParser integration with PKB")
{
    SECTION("insert_parent")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 25, "call ProcEdur310;");
        CallParser (pkb, stmt, "2");
        int result = pkb.get_parent(25);
        int expected = 2;
        REQUIRE(result == expected);
    }
    SECTION("insert_type")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 1, "call proc9;");
        CallParser (pkb, stmt, "Proc1");
        EntityType result = pkb.get_statement_type(1);
        EntityType expected(EntityType::CALL);
        REQUIRE(result == expected);
    }
    SECTION("insert_calls")
    {
        PKB pkb;
        Statement stmt = Statement(EntityType::CALL, 1, "call secondProc;");
        stmt.set_procedure("currentProc");
        CallParser (pkb, stmt, "parentProc");

        Statement stmt2 = Statement(EntityType::CALL, 1, "call secondProc2;");
        stmt2.set_procedure("currentProc2");
        CallParser (pkb, stmt2, "parentProc2");

        std::vector<std::string> procedures_call = pkb.get_all_procedures_calls();
        sort(procedures_call.begin(), procedures_call.end());
        REQUIRE(procedures_call[0] == "secondProc");
        REQUIRE(procedures_call[1] == "secondProc2");

        std::vector<std::string> procedures_called = pkb.get_all_procedures_called();
        sort(procedures_called.begin(), procedures_called.end());
        REQUIRE(procedures_called[0] == "currentProc");
        REQUIRE(procedures_called[1] == "currentProc2");
    }
}
