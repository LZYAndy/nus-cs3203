#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Entity.h"
#include "ErrorMessages.h"

namespace pql_dto
{
class Pattern
{
private:
    Entity pattern_entity;
    Entity first_param;
    Entity second_param;

public:
    // Default constructor for Pattern.
    Pattern();

    /** Constructor for Pattern. Throws a runtime exception if not properly initialised.
     *  @param pattern_entity The type of the Pattern.
     *  @param first_param The first parameter of the Pattern.
     *  @param second_param The second parameter of the Pattern.
     */
    Pattern(Entity pattern_entity, Entity first_param, Entity second_param);

    // Returns the Pattern Entity.
    Entity get_pattern_entity();

    // Returns the First Parameter in the Pattern.
    Entity get_first_param();

    // Returns the Second Parameter in the Pattern.
    Entity get_second_param();

    /** Sets the pattern entity of the Pattern Object.
     *  @param entity The entity for the pattern.
     */
    void set_pattern_entity(Entity entity);

    /** Sets the first parameter entity of the Pattern Object.
     *  @param first_entity_param The first param entity for the pattern.
     */
    void set_first_param(Entity first_entity_param);

    /** Sets the second parameter entity of the Pattern Object.
     *  @param second_entity_param The second param entity for the pattern.
     */
    void set_second_param(Entity second_entity_param);

    /** Updates the first param of the Pattern Object.
     *  @param value The value of the synonym.
     */
    void update_first_param(std::string value);

    /** Updates the second param of the Pattern Object.
     *  @param value The value of the synonym.
     */
    void update_second_param(std::string value);

    /** Checks if both pattern are the same.
     *  @param pattern The pattern to be compared.
     */
    bool equals(Pattern pattern);

    bool operator ==(const Pattern& pattern) const
    {
        return pattern_entity == pattern.pattern_entity
            && first_param == pattern.first_param
            && second_param == pattern.second_param;
    }

    // Returns the string value of the object.
    std::string to_string();

    // Table containing the valid parameters for each pattern.
    std::unordered_map<EntityType, std::vector<std::vector<EntityType>>, EnumClassHash> pattern_table
    {
        {
            EntityType::ASSIGN,
            {
                {
                    EntityType::ANY, EntityType::VARIABLE
                },
                {
                    EntityType::ANY, EntityType::PATTEXPR, EntityType::MATCHEXPR
                }
            }
        },
        {
            EntityType::IF,
            {
                {
                    EntityType::ANY, EntityType::VARIABLE
                },
                {
                    EntityType::ANY
                }
            }
        },
        {
            EntityType::WHILE,
            {
                {
                    EntityType::ANY, EntityType::VARIABLE
                },
                {
                    EntityType::ANY
                }
            }
        }
    };
};
}

#endif
