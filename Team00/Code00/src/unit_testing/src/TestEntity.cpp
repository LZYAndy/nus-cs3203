#include "catch.hpp"
#include "pql_dto/Entity.h"

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
        REQUIRE_NOTHROW(pql_dto::Entity("string", "5", false));
        REQUIRE_NOTHROW(pql_dto::Entity("any", "_", false));
        REQUIRE_NOTHROW(pql_dto::Entity("pattexpr", "_\"x\"_", false));
        REQUIRE_NOTHROW(pql_dto::Entity("pattexpr", "_\"x + y\"_", false));
    }
}

TEST_CASE("Wrong entity params throws error correctly")
{
    SECTION("Set entity with wrong type.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("varible", "v", true), "Invalid Entity Type!");
    }

    SECTION("Set declared entity with wrong name.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("stmt", "stre@2", true), "Invalid Entity Name!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("variable", "1s", true), "Invalid Entity Name!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("read", "", true), "Invalid Entity Name!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("constant", "0", true), "Invalid Entity Name!");
    }

    SECTION("Set undeclared entity with wrong name.")
    {
        REQUIRE_THROWS_WITH(pql_dto::Entity("stmt", "a", false), "Invalid Statement Number Value!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("string", "a2@", false), "Invalid String!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("any", "s", false), "Invalid Entity Name For Any!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "s", false), "Invalid Entity Name For Pattern Expression!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"_", false), "Invalid Entity Name For Pattern Expression!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"\"_", false), "Invalid Entity Name For Pattern Expression!");
        REQUIRE_THROWS_WITH(pql_dto::Entity("pattexpr", "_\"ser#\"_", false), "Invalid Entity Params For Pattern Expression!");
    }
}
