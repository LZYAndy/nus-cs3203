#include "Relationships.h"

namespace pql_dto
{
class UsesRelationship : public Relationships
{
public:
    /** Constructor for UsesRelationship. Throws a runtime exception if not properly initialised.
     *  @param first_param The first parameter of the UsesRelationship.
     *  @param second_param The second parameter of the UsesRelationship.
     *  @param is_star The is_star value of the UsesRelationship.
     */
    UsesRelationship(Entity first_param, Entity second_param, bool is_star)
    {
        if (first_param.get_entity_type() == EntityType::VARIABLE && !first_param.is_entity_declared())
        {
            first_param.set_entity_type("procedure");
        }

        set_relationship(RelationshipType::USES);
        set_first_param(first_param);
        set_second_param(second_param);
        set_relationship_star(is_star);
    }

private:
    void set_first_param(Entity param)
    {
        std::unordered_set<EntityType, EnumClassHash> uses_first_param_type = relationships_table.at(RelationshipType::USES).front();
        if (uses_first_param_type.find(param.get_entity_type()) == uses_first_param_type.end())
        {
            throw std::runtime_error(error_messages::invalid_uses_relationship_first_param);
        }

        first_param = param;
    }

    void set_second_param(Entity param)
    {
        std::unordered_set<EntityType, EnumClassHash> uses_second_param_type = relationships_table.at(RelationshipType::USES).back();
        if (uses_second_param_type.find(param.get_entity_type()) == uses_second_param_type.end())
        {
            throw std::runtime_error(error_messages::invalid_uses_relationship_second_param);
        }
        second_param = param;
    }
};
}
