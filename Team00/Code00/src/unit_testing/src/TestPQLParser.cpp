#include "catch.hpp"
#include "pql_dto/Entity.h"
#include "pql_dto/Entity.cpp"
#include <string>

TEST_CASE("Entity stores and retrieve values correctly")
{
    pql_dto::Entity entity = pql_dto::Entity("stmt", "s", true);

    EntityType entity_type = entity.get_entity_type();
    std::string entity_name = entity.get_entity_name();
    bool is_declared = entity.is_entity_declared();

    REQUIRE(entity_type == EntityType::STMT);
    REQUIRE(entity_name == "s");
    REQUIRE(is_declared == true);
}
