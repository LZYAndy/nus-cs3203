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
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::STRING
                || param.get_entity_type() == EntityType::PATTEXPR || param.get_entity_type() == EntityType::INVALID)
            {
                throw std::runtime_error("Invalid Follows Relationship First Parameter Type!");
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::STRING
                || param.get_entity_type() == EntityType::PATTEXPR || param.get_entity_type() == EntityType::INVALID)
            {
                throw std::runtime_error("Invalid Follows Relationship Second Parameter Type!");
            }

            if ((first_param.get_entity_type() == EntityType::STMT && !first_param.is_entity_declared())
                && (param.get_entity_type() == EntityType::STMT && !param.is_entity_declared())
                && std::stoi(first_param.get_entity_name()) >= std::stoi(param.get_entity_name()))
            {
                throw std::runtime_error("First param for Follows Relationship is greater than the second param.");
            }

            second_param = param;
        }
    };
}
