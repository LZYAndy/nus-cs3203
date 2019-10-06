#include "Relationships.h"

namespace pql_dto
{
class FollowsRelationship : public Relationships
{
public:
    /** Constructor for FollowsRelationship. Throws a runtime exception if not properly initialised.
     *  @param first_param The first parameter of the FollowsRelationship.
     *  @param second_param The second parameter of the FollowsRelationship.
     *  @param is_star The is_star value of the FollowsRelationship.
     */
    FollowsRelationship(Entity first_param, Entity second_param, bool is_star)
    {
        set_relationship(RelationshipType::FOLLOWS);
        set_first_param(first_param);
        set_second_param(second_param);
        set_relationship_star(is_star);

        if ((first_param.get_entity_type() == EntityType::STMT && !first_param.is_entity_declared())
                && (second_param.get_entity_type() == EntityType::STMT && !second_param.is_entity_declared())
                && std::stoi(first_param.get_entity_name()) >= std::stoi(second_param.get_entity_name()))
        {
            throw std::runtime_error(error_messages::invalid_order_of_params);
        }
    }

private:
    void set_first_param(Entity param)
    {
        if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::PATTEXPR
                || param.get_entity_type() == EntityType::INVALID || param.get_entity_type() == EntityType::MATCHEXPR)
        {
            throw std::runtime_error(error_messages::invalid_follows_relationship_first_param);
        }

        first_param = param;
    }

    void set_second_param(Entity param)
    {
        if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::PROCEDURE || param.get_entity_type() == EntityType::PATTEXPR
                || param.get_entity_type() == EntityType::INVALID || param.get_entity_type() == EntityType::MATCHEXPR)
        {
            throw std::runtime_error(error_messages::invalid_follows_relationship_second_param);
        }

        second_param = param;
    }
};
}