#include "catch.hpp"
#include "pql_dto/Entity.h"
#include "ErrorMessages.h"

#include <string>

TEST_CASE("Entity variables can be set and get correctly")
{
    pql_dto::Entity entity = pql_dto::Entity("stmt", "s", true);

    EntityType entity_type = entity.get_entity_type();
    std::string entity_name = entity.get_entity_name();
    bool is_declared = entity.is_entity_declared();

    REQUIRE(entity_type == EntityType::STMT);
    REQUIRE(entity_name == "s");
    REQUIRE(is_declared == true);
}

TEST_CASE("Correct entity params does not throw error.")
{
    SECTION("Set entity with correct type.")
    {
        REQUIRE_NOTHROW(pql_dto::Entity("variable", "v", true));
        REQUIRE_NOTHROW(pql_dto::Entity("stmt", "v", true));
        REQUIRE_NOTHROW(pql_dto::Entity("procedure", "v", true));
    }

    SECTION("Set entity with correct name where entity is declared.")
    {
        REQUIRE_NOTHROW(pql_dto::Entity("constant", "s1", true));
        REQUIRE_NOTHROW(pql_dto::Entity("print", "v", true));
        REQUIRE_NOTHROW(pql_dto::Entity("read", "r", true));
    }

    SECTION("Set entity with correct name where entity is NOT declared.")
    {
        REQUIRE_NOTHROW(pql_dto::Entity("stmt", "5", false));
        REQUIRE_NOTHROW(pql_dto::Entity("any", "_", false));
        REQUIRE_NOTHROW(pql_dto::Entity("procedure", "main", false));
        REQUIRE_NOTHROW(pql_dto::Entity("matchexpr", "x+y", false));
        REQUIRE_NOTHROW(pql_dto::Entity("pattexpr", "x", false));
        REQUIRE_NOTHROW(pql_dto::Entity("pattexpr", "x + y", false));
    }
}

TEST_CASE("Wrong entity params throws error correctly")
{
    SECTION("Set entity with wrong type.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("varible", "v", true), error_messages::invalid_entity_type);
    }

    SECTION("Set declared entity with wrong name.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("stmt", "stre@2", true), error_messages::invalid_declared_entity_name);
        REQUIRE_THROWS_WITH(pql_dto::Entity("variable", "1s", true), error_messages::invalid_declared_entity_name);
        REQUIRE_THROWS_WITH(pql_dto::Entity("read", "", true), error_messages::invalid_declared_entity_name);
        REQUIRE_THROWS_WITH(pql_dto::Entity("constant", "0", true), error_messages::invalid_declared_entity_name);
    }

    SECTION("Set undeclared entity with wrong name.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("stmt", "a", false), error_messages::invalid_statement_number);
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"_", false), error_messages::invalid_pattern_expression_format);
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"\"_", false), error_messages::invalid_pattern_expression_format);
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"ser#\"_", false), error_messages::invalid_pattern_expression_format);
    }
}

TEST_CASE("Entity attributes can be set and get correctly")
{
    pql_dto::Entity stmt_entity = pql_dto::Entity("stmt", "s", true);
    stmt_entity.set_entity_attr("stmt#");

    EntityType entity_type = stmt_entity.get_entity_type();
    std::string entity_name = stmt_entity.get_entity_name();
    bool is_declared = stmt_entity.is_entity_declared();
    AttributeType entity_attr = stmt_entity.get_entity_attr();

    REQUIRE(entity_type == EntityType::STMT);
    REQUIRE(entity_name == "s");
    REQUIRE(is_declared == true);
    REQUIRE(entity_attr == AttributeType::STMTNUM);
}

TEST_CASE("Correct entity params and attributes does not throw error.")
{
    SECTION("Set entity with correct type.")
    {
        pql_dto::Entity var_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_NOTHROW(var_entity.set_entity_attr("varName"));

        pql_dto::Entity stmt_entity = pql_dto::Entity("stmt", "v", true);
        REQUIRE_NOTHROW(stmt_entity.set_entity_attr("stmt#"));

        pql_dto::Entity proc_entity = pql_dto::Entity("procedure", "v", true);
        REQUIRE_NOTHROW(proc_entity.set_entity_attr("procName"));

        pql_dto::Entity const_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_NOTHROW(const_entity.set_entity_attr("value"));

        pql_dto::Entity call_entity = pql_dto::Entity("call", "c", true);
        REQUIRE_NOTHROW(call_entity.set_entity_attr("procName"));
        REQUIRE_NOTHROW(call_entity.set_entity_attr("stmt#"));

        pql_dto::Entity print_entity = pql_dto::Entity("print", "v", true);
        REQUIRE_NOTHROW(print_entity.set_entity_attr("stmt#"));
        REQUIRE_NOTHROW(print_entity.set_entity_attr("varName"));

        pql_dto::Entity read_entity = pql_dto::Entity("read", "r", true);
        REQUIRE_NOTHROW(read_entity.set_entity_attr("stmt#"));
        REQUIRE_NOTHROW(read_entity.set_entity_attr("varName"));
    }
}

TEST_CASE("Entity params with wrong attribute value throws error correctly")
    {
        SECTION("Set entity with incorrect type.")
    {
        pql_dto::Entity var_entity = pql_dto::Entity("variable", "v", true);
        REQUIRE_THROWS_WITH(var_entity.set_entity_attr("stmt#"), error_messages::invalid_entity_attr);

        pql_dto::Entity stmt_entity = pql_dto::Entity("stmt", "v", true);
        REQUIRE_THROWS_WITH(stmt_entity.set_entity_attr("procName"), error_messages::invalid_entity_attr);

        pql_dto::Entity proc_entity = pql_dto::Entity("procedure", "v", true);
        REQUIRE_THROWS_WITH(proc_entity.set_entity_attr("stmt#"), error_messages::invalid_entity_attr);

        pql_dto::Entity const_entity = pql_dto::Entity("constant", "c", true);
        REQUIRE_THROWS_WITH(const_entity.set_entity_attr("stmt#"), error_messages::invalid_entity_attr);

        pql_dto::Entity call_entity = pql_dto::Entity("call", "c", true);
        REQUIRE_THROWS_WITH(call_entity.set_entity_attr("value"), error_messages::invalid_entity_attr);
        REQUIRE_THROWS_WITH(call_entity.set_entity_attr("varName"), error_messages::invalid_entity_attr);

        pql_dto::Entity print_entity = pql_dto::Entity("print", "v", true);
        REQUIRE_THROWS_WITH(print_entity.set_entity_attr("value"), error_messages::invalid_entity_attr);
        REQUIRE_THROWS_WITH(print_entity.set_entity_attr("procName"), error_messages::invalid_entity_attr);

        pql_dto::Entity read_entity = pql_dto::Entity("read", "r", true);
        REQUIRE_THROWS_WITH(read_entity.set_entity_attr("value"), error_messages::invalid_entity_attr);
        REQUIRE_THROWS_WITH(read_entity.set_entity_attr("procName"), error_messages::invalid_entity_attr);
    }
}
