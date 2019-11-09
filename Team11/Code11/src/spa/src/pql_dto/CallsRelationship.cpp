#include "Relationships.h"

namespace pql_dto
{
    class CallsRelationship : public Relationships
    {
    public:
        /** Constructor for CallsRelationship. Throws a runtime exception if not properly initialised.
         *  @param first_param The first parameter of the CallsRelationship.
         *  @param second_param The second parameter of the CallsRelationship.
         *  @param is_star The is_star value of the CallsRelationship.
         */
        CallsRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            if (first_param.get_entity_type() == EntityType::VARIABLE && !first_param.is_entity_declared())
            {
                first_param.set_entity_type("procedure");
            }

            if (second_param.get_entity_type() == EntityType::VARIABLE && !second_param.is_entity_declared())
            {
                second_param.set_entity_type("procedure");
            }

            set_relationship(RelationshipType::CALLS);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            std::vector<EntityType> calls_first_param_type = relationships_table.at(RelationshipType::CALLS).front();
            if (std::find(calls_first_param_type.begin(), calls_first_param_type.end(), param.get_entity_type()) == calls_first_param_type.end())
            {
                if (param.is_entity_declared())
                {
                    throw std::runtime_error(error_messages::invalid_calls_relationship_first_param);
                }
                else
                {
                    throw std::runtime_error(error_messages::invalid_calls_relationship_first_param_syntax);
                }
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            std::vector<EntityType> calls_second_param_type = relationships_table.at(RelationshipType::CALLS).back();
            if (std::find(calls_second_param_type.begin(), calls_second_param_type.end(), param.get_entity_type()) == calls_second_param_type.end())
            {
                if (param.is_entity_declared())
                {
                    throw std::runtime_error(error_messages::invalid_calls_relationship_second_param);
                }
                else
                {
                    throw std::runtime_error(error_messages::invalid_calls_relationship_second_param_syntax);
                }   
            }

            second_param = param;
        }
    };
}
