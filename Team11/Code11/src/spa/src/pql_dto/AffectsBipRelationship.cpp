#include "Relationships.h"

namespace pql_dto
{
    class AffectsBipRelationship : public Relationships
    {
    public:
        /** Constructor for AffectsBipRelationship. Throws a runtime exception if not properly initialised.
         *  @param first_param The first parameter of the AffectsBipRelationship.
         *  @param second_param The second parameter of the AffectsBipRelationship.
         *  @param is_star The is_star value of the AffectsBipRelationship.
         */
        AffectsBipRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            set_relationship(RelationshipType::AFFECTSBIP);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            std::vector<EntityType> affects_bip_first_param_type = relationships_table.at(RelationshipType::AFFECTSBIP).front();
            if (std::find(affects_bip_first_param_type.begin(), affects_bip_first_param_type.end(), param.get_entity_type()) == affects_bip_first_param_type.end())
            {
                if (param.is_entity_declared())
                {
                    throw std::runtime_error(error_messages::invalid_affects_bip_relationship_first_param);
                }
                else
                {
                    throw std::runtime_error(error_messages::invalid_affects_bip_relationship_first_param_syntax);
                }
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            std::vector<EntityType> affects_bip_second_param_type = relationships_table.at(RelationshipType::AFFECTS).back();
            if (std::find(affects_bip_second_param_type.begin(), affects_bip_second_param_type.end(), param.get_entity_type()) == affects_bip_second_param_type.end())
            {
                if (param.is_entity_declared())
                {
                    throw std::runtime_error(error_messages::invalid_affects_bip_relationship_second_param);
                }
                else
                {
                    throw std::runtime_error(error_messages::invalid_affects_bip_relationship_second_param_syntax);
                }
            }

            second_param = param;
        }
    };
}
