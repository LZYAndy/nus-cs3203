#include "Relationships.h"

namespace pql_dto
{
    class AffectsRelationship : public Relationships
    {
    public:
        /** Constructor for AffectsRelationship. Throws a runtime exception if not properly initialised.
         *  @param first_param The first parameter of the AffectsRelationship.
         *  @param second_param The second parameter of the AffectsRelationship.
         *  @param is_star The is_star value of the AffectsRelationship.
         */
        AffectsRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            set_relationship(RelationshipType::AFFECTS);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            std::vector<EntityType> affects_first_param_type = relationships_table.at(RelationshipType::AFFECTS).front();
            if (std::find(affects_first_param_type.begin(), affects_first_param_type.end(), param.get_entity_type()) == affects_first_param_type.end())
            {
                throw std::runtime_error(error_messages::invalid_affects_relationship_first_param);
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            std::vector<EntityType> affects_second_param_type = relationships_table.at(RelationshipType::AFFECTS).back();
            if (std::find(affects_second_param_type.begin(), affects_second_param_type.end(), param.get_entity_type()) == affects_second_param_type.end())
            {
                throw std::runtime_error(error_messages::invalid_affects_relationship_second_param);
            }

            second_param = param;
        }
    };
}
