#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Pattern.h"

namespace pql_dto
{
    Pattern::Pattern()
    {
    }

    Pattern::Pattern(Entity pattern_entity, Entity first_param, Entity second_param)
    {
        set_pattern_entity(pattern_entity);
        set_first_param(first_param);
        set_second_param(second_param);
    }

    Entity Pattern::get_pattern_entity()
    {
        return pattern_entity;
    }

    Entity Pattern::get_first_param()
    {
        return first_param;
    }

    Entity Pattern::get_second_param()
    {
        return second_param;
    }

    void Pattern::set_pattern_entity(Entity entity)
    {
        if (pattern_entity.get_entity_type() != EntityType::ASSIGN)
        {
            throw std::runtime_error("Invalid Entity Type For Pattern Entity!");
        }
        pattern_entity = entity;
    }

    void Pattern::set_first_param(Entity first_entity_param)
    {
        if (pattern_entity.get_entity_type() != EntityType::ANY || pattern_entity.get_entity_type() != EntityType::STRING
            || pattern_entity.get_entity_type() != EntityType::VARIABLE)
        {
            throw std::runtime_error("Invalid Entity Type For Pattern Entity!");
        }
        first_param = first_entity_param;
    }

    void Pattern::set_second_param(Entity second_entity_param)
    {
        if (pattern_entity.get_entity_type() != EntityType::ANY || pattern_entity.get_entity_type() != EntityType::STRING
            || pattern_entity.get_entity_type() != EntityType::PATTEXPR)
        {
            throw std::runtime_error("Invalid Entity Type For Pattern Entity!");
        }
        second_param = second_entity_param;
    }
}
