#ifndef WITH_H
#define WITH_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

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

        // Validates the first and second parameter of the With Object.
        void validate_parameters();

        /** Checks if the entity is of type integer.
         *  @param pattern The with to be compared.
         */
        bool is_integer_type(Entity entity);

        /** Checks if the entity is of type string.
         *  @param pattern The with to be compared.
         */
        bool is_string_type(Entity entity);

        // Sets the entity type of undeclared variables.
        void set_undeclared_type();

        /** Checks if both with are the same.
         *  @param pattern The with to be compared.
         */
        bool equals(With with);

        // Table containing the valid parameters for each pattern.
        std::vector<std::vector<EntityType>> with_table
        {
            {
                EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL, EntityType::WHILE,
                EntityType::IF, EntityType::ASSIGN, EntityType::VARIABLE, EntityType::CONSTANT, EntityType::PROG_LINE,
                EntityType::PROCEDURE
            },
            {
                EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL, EntityType::WHILE,
                EntityType::IF, EntityType::ASSIGN, EntityType::VARIABLE, EntityType::CONSTANT, EntityType::PROG_LINE,
                EntityType::PROCEDURE
            }
        };
    };
}

#endif
