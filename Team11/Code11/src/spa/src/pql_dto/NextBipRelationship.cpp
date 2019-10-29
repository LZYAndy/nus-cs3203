#include "Relationships.h"

namespace pql_dto
{
    class NextBipRelationship : public Relationships
    {
    public:
        /** Constructor for NextBipRelationship. Throws a runtime exception if not properly initialised.
         *  @param first_param The first parameter of the NextBipRelationship.
         *  @param second_param The second parameter of the NextBipRelationship.
         *  @param is_star The is_star value of the NextBipRelationship.
         */
        NextBipRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            if (first_param.get_entity_type() == EntityType::STMT && !first_param.is_entity_declared())
            {
                first_param.set_entity_type("prog_line");
            }

            if (second_param.get_entity_type() == EntityType::STMT && !second_param.is_entity_declared())
            {
                second_param.set_entity_type("prog_line");
            }

            set_relationship(RelationshipType::NEXTBIP);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            std::vector<EntityType> next_first_param_type = relationships_table.at(RelationshipType::NEXTBIP).front();
            if (std::find(next_first_param_type.begin(), next_first_param_type.end(), param.get_entity_type()) == next_first_param_type.end())
            {
                throw std::runtime_error(error_messages::invalid_next_bip_relationship_first_param);
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            std::vector<EntityType> next_second_param_type = relationships_table.at(RelationshipType::NEXTBIP).back();
            if (std::find(next_second_param_type.begin(), next_second_param_type.end(), param.get_entity_type()) == next_second_param_type.end())
            {
                throw std::runtime_error(error_messages::invalid_next_bip_relationship_second_param);
            }

            second_param = param;
        }
    };
}
