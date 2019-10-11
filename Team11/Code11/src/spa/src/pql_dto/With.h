#ifndef WITH_H
#define WITH_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
#include "ErrorMessages.h"

namespace pql_dto
{
    class With
    {
    private:
        Entity first_param;
        Entity second_param;

    public:
        // Default constructor for With.
        With();

        /** Constructor for With. Throws a runtime exception if not properly initialised.
         *  @param pattern_entity The type of the With.
         *  @param first_param The first parameter of the With.
         *  @param second_param The second parameter of the With.
         */
        With(Entity first_param, Entity second_param);

        // Returns the First Parameter in the With.
        Entity get_first_param();

        // Returns the Second Parameter in the With.
        Entity get_second_param();

        /** Sets the first parameter entity of the With Object.
         *  @param first_entity_param The first param entity for the with.
         */
        void set_first_param(Entity first_entity_param);

        /** Sets the second parameter entity of the With Object.
         *  @param second_entity_param The second param entity for the with.
         */
        void set_second_param(Entity second_entity_param);

        /** Checks if both with are the same.
         *  @param pattern The with to be compared.
         */
        bool equals(With with);
    };
}

#endif
