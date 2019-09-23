#include "Relationships.h"

namespace pql_dto
{
class ModifiesRelationship : public Relationships
{
public:
    ModifiesRelationship(Entity first_param, Entity second_param, bool is_star)
    {
        set_relationship(RelationshipType::MODIFIES);
        set_first_param(first_param);
        set_second_param(second_param);
        set_relationship_star(is_star);
    }

private:
    void set_first_param(Entity param)
    {
        if (param.get_entity_type() == EntityType::VARIABLE && !param.is_entity_declared())
        {
            param.set_entity_type("procedure");
        }

        if (param.get_entity_type() == EntityType::CONSTANT || param.get_entity_type() == EntityType::PATTEXPR
                || param.get_entity_type() == EntityType::ANY || param.get_entity_type() == EntityType::PRINT
                || param.get_entity_type() == EntityType::INVALID || param.get_entity_type() == EntityType::VARIABLE
                || param.get_entity_type() == EntityType::MATCHEXPR)
        {
            throw std::runtime_error(error_messages::invalid_modifies_relationship_first_param);
        }

        first_param = param;
    }

    void set_second_param(Entity param)
    {
        if (param.get_entity_type() == EntityType::VARIABLE || param.get_entity_type() == EntityType::ANY)
        {
            second_param = param;
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_modifies_relationship_second_param);
        }
    }
};
}
