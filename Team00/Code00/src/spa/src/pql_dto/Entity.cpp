#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Entity.h"

namespace pql_dto 
{
    Entity::Entity()
    {
    }

    Entity::Entity(string entity_type, string entity_name)
    {
        set_entity_type(entity_type);
        set_entity_name(entity_name);
    }

    EntityType Entity::get_entity_type()
    {
        return entity_type;
    }

    string Entity::get_entity_name() 
    {
        return entity_name;
    }

    bool Entity::is_entity_declared()
    {
        return is_declared_entity;
    }

    void Entity::set_entity_type(string type) 
    {
        if (type == "stmt")
        {
            entity_type = STMT;
        }
        else if (type == "read")
        {
            entity_type = READ;
        }
        else if (type == "print")
        {
            entity_type = PRINT;
        }
        else if (type == "call")
        {
            entity_type = CALL;
        }
        else if (type == "while")
        {
            entity_type = WHILE;
        }
        else if (type == "if")
        {
            entity_type = IF;
        }
        else if (type == "assign")
        {
            entity_type = ASSIGN;
        }
        else if (type == "variable")
        {
            entity_type = VARIABLE;
        }
        else if (type == "constant")
        {
            entity_type = CONSTANT;
        }
        else if (type == "procedure")
        {
            entity_type = PROCEDURE;
        }
        else
        {
            throw std::exception("Invalid Entity Name!");
        }
    }

    void Entity::set_entity_name(string name) 
    {
        //checks entity names
        entity_name = name;
    }

    void Entity::set_is_declared(bool is_declared)
    {
        is_declared_entity = is_declared;
    }
}
