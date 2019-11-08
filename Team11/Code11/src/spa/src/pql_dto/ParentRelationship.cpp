#include "Relationships.h"

namespace pql_dto
{
class ParentRelationship : public Relationships
{
public:
    /** Constructor for ParentRelationship. Throws a runtime exception if not properly initialised.
     *  @param first_param The first parameter of the ParentRelationship.
     *  @param second_param The second parameter of the ParentRelationship.
     *  @param is_star The is_star value of the ParentRelationship.
     */
    ParentRelationship(Entity first_param, Entity second_param, bool is_star)
    {
        set_relationship(RelationshipType::PARENT);
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
        std::vector<EntityType> parent_first_param_type = relationships_table.at(RelationshipType::PARENT).front();
        if (std::find(parent_first_param_type.begin(), parent_first_param_type.end(), param.get_entity_type()) == parent_first_param_type.end())
        {
            if (param.is_entity_declared())
            {
                throw std::runtime_error(error_messages::invalid_parent_relationship_first_param);
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_parent_relationship_first_param_syntax);
            }
        }

        first_param = param;
    }

    void set_second_param(Entity param)
    {
        std::vector<EntityType> parent_second_param_type = relationships_table.at(RelationshipType::PARENT).back();
        if (std::find(parent_second_param_type.begin(), parent_second_param_type.end(), param.get_entity_type()) == parent_second_param_type.end())
        {
            if (param.is_entity_declared())
            {
                throw std::runtime_error(error_messages::invalid_parent_relationship_second_param);
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_parent_relationship_second_param_syntax);
            }
        }

        second_param = param;
    }
};
}
