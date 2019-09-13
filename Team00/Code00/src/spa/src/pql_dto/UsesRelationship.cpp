#include "Relationships.h"

namespace pql_dto
{
    class UsesRelationship : public Relationships
    {
    public:
        UsesRelationship(Entity first_param, Entity second_param, bool is_star)
        {
            set_relationship(USES);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void set_first_param(Entity param)
        {
            if (param.get_entity_type() == CONSTANT || param.get_entity_type() == VARIABLE
                || param.get_entity_type() == STRING)
            {
                throw std::runtime_error("Invalid Uses Relationship First Parameter Type!");
            }

            first_param = param;
        }

        void set_second_param(Entity param)
        {
            if (param.get_entity_type() == CONSTANT || param.get_entity_type() == VARIABLE
                || param.get_entity_type() == STRING)
            {
                second_param = param;   
            }
            else
            {
                throw runtime_error("Invalid Uses Relationship Second Parameter Type!");
            }
        }
    };
}
