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
    if (entity.get_entity_type() == EntityType::ASSIGN || entity.get_entity_type() == EntityType::IF || entity.get_entity_type() == EntityType::WHILE)
    {
        pattern_entity = entity;
    }
    else
    {
        throw std::runtime_error(error_messages::invalid_pattern_entity);
    }
}

void Pattern::set_first_param(Entity first_entity_param)
{
    std::vector<EntityType> pattern_first_param_type = pattern_table.at(pattern_entity.get_entity_type()).front();
    if (std::find(pattern_first_param_type.begin(), pattern_first_param_type.end(), first_entity_param.get_entity_type())
        == pattern_first_param_type.end())
    {
        if (first_entity_param.is_entity_declared())
        {
            throw std::runtime_error(error_messages::invalid_pattern_first_param);
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_pattern_first_param_syntax);
        }
    }

    first_param = first_entity_param;
}

void Pattern::set_second_param(Entity second_entity_param)
{
    std::vector<EntityType> pattern_second_param_type = pattern_table.at(pattern_entity.get_entity_type()).back();
    if (std::find(pattern_second_param_type.begin(), pattern_second_param_type.end(), second_entity_param.get_entity_type())
        == pattern_second_param_type.end())
    {
        throw std::runtime_error(error_messages::invalid_pattern_second_param_syntax);
    }

    second_param = second_entity_param;
}

void Pattern::update_first_param(std::string value)
{
    first_param.set_is_declared(false);
    first_param.set_entity_type(EntityType::VARIABLE);
    first_param.set_entity_name(value);
}

void Pattern::update_second_param(std::string value)
{
    second_param.set_is_declared(false);
    second_param.set_entity_type(EntityType::VARIABLE);
    second_param.set_entity_name(value);
}

bool Pattern::equals(Pattern pattern)
{
    return pattern_entity.equals(pattern.pattern_entity)
           && first_param.equals(pattern.first_param)
           && second_param.equals(pattern.second_param);
}

std::string Pattern::to_string()
{
    return pattern_entity.to_string() + first_param.to_string() + second_param.to_string();
}
}
