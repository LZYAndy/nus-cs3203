#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"

namespace pql_dto
{
    class Pattern
    {
    private:
        Entity pattern_entity;
        Entity first_param;
        Entity second_param;

    public:
        Pattern();

        // Constructor for Pattern. Throws an exception if not properly initialised.
        Pattern(Entity pattern_entity, Entity first_param, Entity second_param);

        // Returns the Pattern Entity.
        Entity get_pattern_entity();

        // Returns the First Parameter in the Pattern.
        Entity get_first_param();

        // Returns the Second Parameter in the Pattern.
        Entity get_second_param();

        // Sets and validates the pattern entity of the Pattern Object.
        void set_pattern_entity(Entity entity);

        // Sets and validates the first parameter of the Pattern Object.
        void set_first_param(Entity first_entity_param);

        // Sets and validates the second parameter of the Pattern Object.
        void set_second_param(Entity second_entity_param);
    };
}

#endif
