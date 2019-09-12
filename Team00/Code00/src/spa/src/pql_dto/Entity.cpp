#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

#include "Entity.h"

namespace pql_dto
{
    Entity::Entity()
    {
    }

    Entity::Entity(string entity_type, string entity_name, bool is_declared)
    {
        set_entity_type(entity_type);
        set_is_declared(is_declared);
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
        if (type == "any")
        {
            entity_type = ANY;
        }
        else if (type == "stmt")
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
        else if (type == "string")
        {
            entity_type = STRING;
        }
        else if (type == "pattexpr")
        {
            entity_type = PATTEXPR;
        }
        else
        {
            throw std::runtime_error("Invalid Entity Type!");
        }
    }

    void Entity::set_entity_name(string name)
    {
        //checks entity names
        if (entity_type == ANY)
        {
            if (name != "_")
            {
                throw std::runtime_error("Invalid Entity Name For Any!");
            }
            entity_name = "_";
        }
        else if (entity_type == PATTEXPR)
        {
            if (entity_name.find_first_of("_\"") == std::string::npos || entity_name.find_last_of("\"_") == std::string::npos)
            {
                throw std::runtime_error("Invalid Entity Name For Pattern Expression!");
            }
            entity_name = name;
        }
        else if (entity_type == STMT && !is_declared_entity)
        {
            /// Checks if var_name is integer
        }
        else
        {
            /// Checks if var_name is alphanumeric
        }
        entity_name = name;
    }

    void Entity::set_is_declared(bool is_declared)
    {
        is_declared_entity = is_declared;
    }
}
