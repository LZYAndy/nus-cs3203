#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Defines the entity type of the given entity.
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
    PROG_LINE,
    PROCEDURE,
    PATTEXPR,
    MATCHEXPR,
    BOOLEAN,
    INVALID
};

// Defines the entity type of the given entity.
enum class AttributeType
{
    NONE,
    PROCNAME,
    VARNAME,
    VALUE,
    STMTNUM
};

struct EnumClassHash
{
    template<typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

namespace pql_dto
{
class Entity
{
private:
    EntityType entity_type = EntityType::ANY;
    AttributeType entity_attr = AttributeType::NONE;
    std::string entity_name;

    bool is_declared_entity = false;

public:
    // Default constructor for Entity.
    Entity();

    /** Constructor for Entity. Throws a runtime exception if not properly initialised.
     *  @param entity_type The type of the Entity.
     *  @param entity_name The name of the Entity.
     *  @param is_declared The is_declared value of the Entity.
     */
    Entity(std::string entity_type, std::string entity_name, bool is_declared);

    // Returns the Entity Type.
    EntityType get_entity_type();

    // Returns the Entity Attribute.
    AttributeType get_entity_attr();

    // Returns the Entity Name.
    std::string get_entity_name();

    // Returns true if entity is declared in Query. Defaults value to false.
    bool is_entity_declared();

    /** Sets and validates the entity type of the Entity Object.
     *  @param type The type of the Entity.
     */
    void set_entity_type(std::string type);

    /** Sets and validates the entity type of the declared Entity Object.
     *  @param type The type of the Entity.
     */
    void set_declared_entity_type(std::string type);

    /** Sets and validates the attribute type of the Entity Object.
     *  @param attr The attribute of the Entity.
     */
    void set_entity_attr(std::string attr);

    /** Sets and validates the entity name of the Entity Object.
     *  @param name The name of the Entity.
     */
    void set_entity_name(std::string name);

    /** Sets is_declared_entity of the Entity Object.
     *  @param is_declared The boolean value of the Entity if it is declared.
     */
    void set_is_declared(bool is_declared);

    /** Checks if both entity are the same.
     *  @param entity The entity to be compared.
     */
    bool equals(Entity entity);

    // Table containing the valid parameters for each relationship.
    std::unordered_map<AttributeType, std::vector<EntityType>, EnumClassHash> attributes_table
    {
        {
            AttributeType::PROCNAME,
            {
                {
                    EntityType::PROCEDURE, EntityType::CALL
                }
            }
        },
        {
            AttributeType::VARNAME,
            {
                {
                    EntityType::VARIABLE, EntityType::READ, EntityType::PRINT
                }
            }
        },
        {
            AttributeType::VALUE,
            {
                {
                    EntityType::CONSTANT
                }
            }
        },
        {
            AttributeType::STMTNUM,
            {
                {
                    EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN
                }
            }
        },
    };
};
}

#endif
