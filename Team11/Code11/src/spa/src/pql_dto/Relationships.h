#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Entity.h"
#include "../ErrorMessages.h"

enum class RelationshipType
{
    FOLLOWS,
    PARENT,
    USES,
    MODIFIES,
    CALLS,
    NEXT,
    AFFECTS,
    NEXTBIP,
    AFFECTSBIP
};

namespace pql_dto
{
class Relationships
{
protected:
    RelationshipType relationship_type = RelationshipType::FOLLOWS;
    Entity first_param;
    Entity second_param;

    bool is_star = false;

public:
    // Returns the Relationship Type.
    RelationshipType get_relationship();

    // Returns the First Parameter in the Relationship.
    Entity get_first_param();

    // Returns the Second Parameter in the Relationship.
    Entity get_second_param();

    // Returns true if the Relationship is a Relationship Star. Defaults value to false.
    bool is_relationship_star();

    /** Sets the type of the Relationship Object.
     *  @param relationship_type The type of the relationship.
     */
    void set_relationship(RelationshipType relationship_type);

    /** Updates the first param of the Relationship Object.
     *  @param value The value of the synonym.
     */
    void update_first_param(std::string value);

    /** Updates the second param of the Relationship Object.
     *  @param value The value of the synonym.
     */
    void update_second_param(std::string value);

    /** Sets is_relationship_star of the Relationship Object.
     *  @param is_declared The boolean value of the Relationship if it is a star.
     */
    void set_relationship_star(bool is_relationship_star);

    /** Checks if both relationship are the same.
     *  @param relationship The relationship to be compared.
     */
    bool equals(Relationships relationship);

    // Table containing the valid parameters for each relationship.
    std::unordered_map<RelationshipType, std::vector<std::vector<EntityType>>, EnumClassHash> relationships_table
    {
        {
            RelationshipType::FOLLOWS,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
        {
            RelationshipType::PARENT,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
        {
            RelationshipType::MODIFIES,
            {
                {
                    EntityType::STMT, EntityType::READ, EntityType::CALL, EntityType::PROCEDURE,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::VARIABLE
                }
            }
        },
        {
            RelationshipType::USES,
            {
                {
                    EntityType::STMT, EntityType::PRINT, EntityType::CALL, EntityType::PROCEDURE,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::VARIABLE
                }
            }
        },
        {
            RelationshipType::CALLS,
            {
                {
                    EntityType::ANY, EntityType::PROCEDURE
                },
                {
                    EntityType::ANY, EntityType::PROCEDURE
                }
            }
        },
        {
            RelationshipType::NEXT,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
        {
            RelationshipType::AFFECTS,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
        {
            RelationshipType::NEXTBIP,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::READ, EntityType::PRINT, EntityType::CALL,
                    EntityType::WHILE, EntityType::IF, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
        {
            RelationshipType::AFFECTSBIP,
            {
                {
                    EntityType::ANY, EntityType::STMT, EntityType::ASSIGN, EntityType::PROG_LINE
                },
                {
                    EntityType::ANY, EntityType::STMT, EntityType::ASSIGN, EntityType::PROG_LINE
                }
            }
        },
    };
};
}

#endif
