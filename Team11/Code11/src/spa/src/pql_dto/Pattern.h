#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

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

    /** Checks if both pattern are the same.
     *  @param pattern The pattern to be compared.
     */
    bool equals(Pattern pattern);
};
}

#endif
