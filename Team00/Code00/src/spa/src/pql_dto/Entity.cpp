#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Entity.h"
#include "../CheckerUtil.h"

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
            entity_type = EntityType::ANY;
        }
        else if (type == "stmt")
        {
            entity_type = EntityType::STMT;
        }
        else if (type == "read")
        {
            entity_type = EntityType::READ;
        }
        else if (type == "print")
        {
            entity_type = EntityType::PRINT;
        }
        else if (type == "call")
        {
            entity_type = EntityType::CALL;
        }
        else if (type == "while")
        {
            entity_type = EntityType::WHILE;
        }
        else if (type == "if")
        {
            entity_type = EntityType::IF;
        }
        else if (type == "assign")
        {
            entity_type = EntityType::ASSIGN;
        }
        else if (type == "variable")
        {
            entity_type = EntityType::VARIABLE;
        }
        else if (type == "constant")
        {
            entity_type = EntityType::CONSTANT;
        }
        else if (type == "procedure")
        {
            entity_type = EntityType::PROCEDURE;
        }
        else if (type == "string")
        {
            entity_type = EntityType::STRING;
        }
        else if (type == "pattexpr")
        {
            entity_type = EntityType::PATTEXPR;
        }
        else
        {
            throw std::runtime_error("Invalid Entity Type!");
        }
    }

    void Entity::set_entity_name(string name)
    {
        //checks entity names
        if (entity_type == EntityType::ANY)
        {
            if (name != "_")
            {
                throw std::runtime_error("Invalid Entity Name For Any!");
            }
            entity_name = "_";
        }
        else if (entity_type == EntityType::PATTEXPR)
        {
            if (name.length() <= 4 || name.find("_\"") != 0 || name.find("\"_") != name.length() - 2)
            {
                throw std::runtime_error("Invalid Entity Name For Pattern Expression!");
            }
            std::string name_string = name.substr(2, name.length() - 4);
            if (!CheckerUtil::is_expr_valid(name_string))
            {
                throw std::runtime_error("Invalid Entity Params For Pattern Expression!");
            }
            entity_name = name_string;
        }
        else if (entity_type == EntityType::STMT && !is_declared_entity)
        {
            /// Checks if var_name is integer
            if (!CheckerUtil::is_const_valid(name))
            {
                throw std::runtime_error("Invalid Statement Number Value!");
            }
            entity_name = name;
        }
        else if (entity_type == EntityType::STRING && !is_declared_entity)
        {
            /// Checks if var_name is integer
            if (!CheckerUtil::is_const_valid(name) && !CheckerUtil::is_name_valid(name))
            {
                throw std::runtime_error("Invalid String!");
            }
            entity_name = name;
        }
        else
        {
            /// Checks if var_name is alphanumeric
            if (!CheckerUtil::is_name_valid(name))
            {
                throw std::runtime_error("Invalid Entity Name!");
            }
            entity_name = name;
        }
    }

    void Entity::set_is_declared(bool is_declared)
    {
        is_declared_entity = is_declared;
    }
}
