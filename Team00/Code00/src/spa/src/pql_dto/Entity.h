#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

enum class EntityType
{
    ANY,
    STMT,
    READ,
    PRINT,
    CALL,
    WHILE,
    IF,
    ASSIGN,
    VARIABLE,
    CONSTANT,
    PROCEDURE,
    PATTEXPR,
    MATCHEXPR,
    INVALID
};

namespace pql_dto
{
    class Entity
    {
    private:
        EntityType entity_type = EntityType::ANY;
        std::string entity_name;

        bool is_declared_entity = false;

    public:
        Entity();

        // Constructor for Entity. Throws an exception if not properly initialised.
        Entity(std::string entity_type, std::string entity_name, bool is_declared);

        // Returns the Entity Type.
        EntityType get_entity_type();

        // Returns the Entity Name.
        std::string get_entity_name();

        // Returns true if entity is declared in Query.
        // Default value is false.
        bool is_entity_declared();

        // Sets and validates the entity type of the Entity Object.
        void set_entity_type(std::string type);

        // Sets and validates the entity name of the Entity Object.
        void set_entity_name(std::string name);

        // Sets the @param is_declared_entity value to true if Entity is declared.
        void set_is_declared(bool is_declared);

        bool equals(Entity entity);
    };
}

#endif
