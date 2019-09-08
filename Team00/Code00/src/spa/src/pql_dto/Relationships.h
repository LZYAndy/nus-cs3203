#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Entity.h"

enum RelationshipType
{
    FOLLOWS,
    PARENT,
    USES,
    MODIFIES
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

        // Returns true if the Relationship is a Star. 
        // Default value is false.
        bool is_relationship_star();

        // Sets and validates the relationship of the Relationship Object.
        void set_relationship(RelationshipType relationship_type);

        // Sets the @param is_star value to true if Relationship is Star.
        void set_relationship_star(bool is_relationship_star);

        // Sets and validates the first parameter of the Relationship Object.
        virtual void set_first_param(string param) = 0;

        // Sets and validates the second parameter of the Relationship Object.
        virtual void set_second_param(string param) = 0;
    };
}

#endif