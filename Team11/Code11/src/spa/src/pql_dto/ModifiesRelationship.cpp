#include "Relationships.h"

namespace pql_dto
{
class ModifiesRelationship : public Relationships
{
public:
    /** Constructor for ModifiesRelationship. Throws a runtime exception if not properly initialised.
     *  @param first_param The first parameter of the ModifiesRelationship.
     *  @param second_param The second parameter of the ModifiesRelationship.
     *  @param is_star The is_star value of the ModifiesRelationship.
     */
    ModifiesRelationship(Entity first_param, Entity second_param, bool is_star)
    {
        if (first_param.get_entity_type() == EntityType::VARIABLE && !first_param.is_entity_declared())
        {
            first_param.set_entity_type("procedure");
        }

        set_relationship(RelationshipType::MODIFIES);
        set_first_param(first_param);
        set_second_param(second_param);
        set_relationship_star(is_star);
    }

private:
    void set_first_param(Entity param)
    {
        std::vector<EntityType> modifies_first_param_type = relationships_table.at(RelationshipType::MODIFIES).front();
        if (std::find(modifies_first_param_type.begin(), modifies_first_param_type.end(), param.get_entity_type()) == modifies_first_param_type.end())
        {
            if (param.is_entity_declared())
            {
                throw std::runtime_error(error_messages::invalid_modifies_relationship_first_param);
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_modifies_relationship_first_param_syntax);
            }
        }

        first_param = param;
    }

    void set_second_param(Entity param)
    {
        std::vector<EntityType> modifies_second_param_type = relationships_table.at(RelationshipType::MODIFIES).back();
        if (std::find(modifies_second_param_type.begin(), modifies_second_param_type.end(), param.get_entity_type()) == modifies_second_param_type.end())
        {
            if (param.is_entity_declared())
            {
                throw std::runtime_error(error_messages::invalid_modifies_relationship_second_param);
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_modifies_relationship_second_param_syntax);
            }
        }

        second_param = param;
    }
};
}
