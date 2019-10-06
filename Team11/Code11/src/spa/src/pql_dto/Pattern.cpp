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
    if (entity.get_entity_type() != EntityType::ASSIGN)
    {
        throw std::runtime_error(error_messages::invalid_pattern_entity);
    }
    pattern_entity = entity;
}

void Pattern::set_first_param(Entity first_entity_param)
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

void Pattern::set_second_param(Entity second_entity_param)
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

bool Pattern::equals(Pattern pattern)
{
    return pattern_entity.equals(pattern.pattern_entity)
           && first_param.equals(pattern.first_param)
           && second_param.equals(pattern.second_param);
}
}