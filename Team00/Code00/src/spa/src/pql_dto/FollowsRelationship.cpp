#include "Relationships.h"

namespace pql_dto
{
    class FollowsRelationship : public Relationships
    {
    public:
        FollowsRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            set_relationship(RelationshipType::FOLLOWS);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::STRING)
            {
                throw std::runtime_error("Invalid Follows Relationship First Parameter Type!");
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::STRING)
            {
                throw std::runtime_error("Invalid Follows Relationship Second Parameter Type!");
            }

            second_param = param;
        }
    };
}
