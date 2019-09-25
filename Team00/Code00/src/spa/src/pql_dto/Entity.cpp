#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "Entity.h"
#include "../CheckerUtil.h"
#include "../ErrorMessages.h"

namespace pql_dto
{
    Entity::Entity()
    {
    }

    Entity::Entity(std::string entity_type, std::string entity_name, bool is_declared)
    {
        set_entity_type(entity_type);
        set_is_declared(is_declared);
        set_entity_name(entity_name);
    }

    EntityType Entity::get_entity_type()
    {
        return entity_type;
    }

    std::string Entity::get_entity_name()
    {
        return entity_name;
    }

    bool Entity::is_entity_declared()
    {
        return is_declared_entity;
    }

    void Entity::set_entity_type(std::string type)
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
        else if (type == "pattexpr")
        {
            entity_type = EntityType::PATTEXPR;
        }
        else if (type == "matchexpr")
        {
            entity_type = EntityType::MATCHEXPR;
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_entity_type);
        }
    }

    void Entity::set_entity_name(std::string name)
    {
        /// Validates entity names
        if (is_declared_entity)
        {
            /// Checks if var_name is alphanumeric
            if (!CheckerUtil::is_name_valid(name))
            {
                throw std::runtime_error(error_messages::invalid_declared_entity_name);
            }
            entity_name = name;
        }
        else
        {
            /// Entity is not declared
            if (entity_type == EntityType::ANY)
            {
                entity_name = name;
            }
            else if (entity_type == EntityType::PATTEXPR)
            {
                if (!CheckerUtil::is_expr_valid(name))
                {
                    if (name.length() <= 4 || name.find("_\"") != 0 || name.find("\"_") != name.length() - 2)
                    {
                        throw std::runtime_error(error_messages::invalid_pattern_expression_format);
                    }
                    name = name.substr(2, name.length() - 4);
                    if (!CheckerUtil::is_expr_valid(name))
                    {
                        throw std::runtime_error(error_messages::invalid_pattern_expression_format);
                    }
                    entity_name = name;
                }
                else
                {
                    throw std::runtime_error(error_messages::invalid_pattern_expression_format);
                }
            }
            else if (entity_type == EntityType::MATCHEXPR)
            {
                if (!CheckerUtil::is_expr_valid(name))
                {
                    throw std::runtime_error(error_messages::invalid_pattern_expression_format);
                }
                entity_name = name;
            }
            else if (entity_type == EntityType::PROCEDURE || entity_type == EntityType::VARIABLE)
            {
                if (!CheckerUtil::is_name_valid(name))
                {
                    throw std::runtime_error(error_messages::invalid_synonym_name);
                }
                entity_name = name;
            }
            else if (entity_type == EntityType::STMT)
            {
                /// Checks if var_name is integer
                if (!CheckerUtil::is_const_valid(name))
                {
                    throw std::runtime_error(error_messages::invalid_statement_number);
                }
                entity_name = name;
            }
            else
            {
                throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
            }
        }
    }

    void Entity::set_is_declared(bool is_declared)
    {
        is_declared_entity = is_declared;
    }

    bool Entity::equals(Entity entity)
    {
        return entity_type == entity.entity_type
               && entity_name == entity.entity_name
               && is_declared_entity == entity.is_declared_entity;
    }
}
