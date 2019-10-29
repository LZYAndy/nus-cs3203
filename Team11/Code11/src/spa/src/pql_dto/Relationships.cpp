#include <string>

using namespace std;

#include "Relationships.h"

namespace pql_dto
{
    RelationshipType Relationships::get_relationship_type()
    {
        return relationship_type;
    }

    Entity Relationships::get_first_param()
    {
        return first_param;
    }

    Entity Relationships::get_second_param()
    {
        return second_param;
    }

    bool Relationships::is_relationship_star()
    {
        return is_star;
    }

    void Relationships:: set_relationship(RelationshipType type)
    {
        relationship_type = type;
    }

    void Relationships::update_first_param(std::string value)
    {
        if (first_param.get_entity_type() == EntityType::CALL || first_param.get_entity_type() == EntityType::READ
            || first_param.get_entity_type() == EntityType::PRINT)
        {
            return;
        }

        first_param.set_is_declared(false);
        if (!value.empty() && std::all_of(value.begin(), value.end(), ::isdigit))
        {
            if (relationship_type == RelationshipType::NEXT)
            {
                first_param.set_entity_type(EntityType::PROG_LINE);
            }
            else
            {
                first_param.set_entity_type(EntityType::STMT);
            }
        }
        else
        {
            first_param.set_entity_type(EntityType::VARIABLE);
        }
        first_param.set_entity_name(value);
    }

    void Relationships::update_second_param(std::string value)
    {
        if (second_param.get_entity_type() == EntityType::CALL || second_param.get_entity_type() == EntityType::READ
            || second_param.get_entity_type() == EntityType::PRINT)
        {
            return;
        }

        second_param.set_is_declared(false);
        if (!value.empty() && std::all_of(value.begin(), value.end(), ::isdigit))
        {
            if (relationship_type == RelationshipType::NEXT)
            {
                second_param.set_entity_type(EntityType::PROG_LINE);
            }
            else
            {
                second_param.set_entity_type(EntityType::STMT);
            }
        }
        else
        {
            second_param.set_entity_type(EntityType::VARIABLE);
        }
        second_param.set_entity_name(value);
    }

    void Relationships::set_relationship_star(bool is_relationship_star)
    {
        is_star = is_relationship_star;
    }

    bool Relationships::equals(Relationships relationship)
    {
        return relationship_type == relationship.relationship_type
               && first_param.equals(relationship.first_param)
               && second_param.equals(relationship.second_param)
               && is_star == relationship.is_star;
    }
}
