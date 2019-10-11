#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "With.h"

namespace pql_dto
{
    With::With()
    {
    }

    With::With(Entity first_param, Entity second_param)
    {
        set_first_param(first_param);
        set_second_param(second_param);
    }

    Entity With::get_first_param()
    {
        return first_param;
    }

    Entity With::get_second_param()
    {
        return second_param;
    }

    void With::set_first_param(Entity first_entity_param)
    {
        if (first_entity_param.get_entity_type() == EntityType::ANY || first_entity_param.get_entity_type() == EntityType::VARIABLE)
        {
            first_param = first_entity_param;
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_pattern_first_param);
        }
    }

    void With::set_second_param(Entity second_entity_param)
    {
        if (second_entity_param.get_entity_type() == EntityType::ANY || second_entity_param.get_entity_type() == EntityType::PATTEXPR
            || second_entity_param.get_entity_type() == EntityType::MATCHEXPR)
        {
            second_param = second_entity_param;
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_pattern_second_param);
        }
    }

    bool With::equals(With with)
    {
        return first_param.equals(with.first_param)
            && second_param.equals(with.second_param);
    }
}
