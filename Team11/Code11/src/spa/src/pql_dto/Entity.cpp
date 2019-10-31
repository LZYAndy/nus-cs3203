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
    if (is_declared)
    {
        set_declared_entity_type(entity_type);
    }
    else
    {
        set_entity_type(entity_type);
    }
    set_is_declared(is_declared);
    set_entity_name(entity_name);
}

EntityType Entity::get_entity_type()
{
    return entity_type;
}

AttributeType Entity::get_entity_attr()
{
    return entity_attr;
}

std::string Entity::get_entity_name()
{
    return entity_name;
}

std::string Entity::get_solution()
{
    return solution_value;
}

bool Entity::is_entity_declared()
{
    return is_declared_entity;
}

void Entity::set_entity_type(EntityType type)
{
    entity_type = type;
}

void Entity::set_entity_type(std::string type)
{
    if (type == any_keyword)
    {
        entity_type = EntityType::ANY;
    }
    else if (type == stmt_keyword)
    {
        entity_type = EntityType::STMT;
    }
    else if (type == read_keyword)
    {
        entity_type = EntityType::READ;
    }
    else if (type == print_keyword)
    {
        entity_type = EntityType::PRINT;
    }
    else if (type == call_keyword)
    {
        entity_type = EntityType::CALL;
    }
    else if (type == while_keyword)
    {
        entity_type = EntityType::WHILE;
    }
    else if (type == if_keyword)
    {
        entity_type = EntityType::IF;
    }
    else if (type == assign_keyword)
    {
        entity_type = EntityType::ASSIGN;
    }
    else if (type == constant_keyword)
    {
        entity_type = EntityType::CONSTANT;
    }
    else if (type == variable_keyword)
    {
        entity_type = EntityType::VARIABLE;
    }
    else if (type == prog_line_keyword)
    {
        entity_type = EntityType::PROG_LINE;
    }
    else if (type == procedure_keyword)
    {
        entity_type = EntityType::PROCEDURE;
    }
    else if (type == patt_expr_keyword)
    {
        entity_type = EntityType::PATTEXPR;
    }
    else if (type == match_expr_keyword)
    {
        entity_type = EntityType::MATCHEXPR;
    }
    else if (type == boolean_keyword)
    {
        entity_type = EntityType::BOOLEAN;
    }
    else
    {
        throw std::runtime_error(error_messages::invalid_entity_type);
    }
}

void Entity::set_declared_entity_type(std::string type)
{
    if (type == stmt_keyword)
    {
        entity_type = EntityType::STMT;
    }
    else if (type == read_keyword)
    {
        entity_type = EntityType::READ;
    }
    else if (type == print_keyword)
    {
        entity_type = EntityType::PRINT;
    }
    else if (type == call_keyword)
    {
        entity_type = EntityType::CALL;
    }
    else if (type == while_keyword)
    {
        entity_type = EntityType::WHILE;
    }
    else if (type == if_keyword)
    {
        entity_type = EntityType::IF;
    }
    else if (type == assign_keyword)
    {
        entity_type = EntityType::ASSIGN;
    }
    else if (type == variable_keyword)
    {
        entity_type = EntityType::VARIABLE;
    }
    else if (type == constant_keyword)
    {
        entity_type = EntityType::CONSTANT;
    }
    else if (type == prog_line_keyword)
    {
        entity_type = EntityType::PROG_LINE;
    }
    else if (type == procedure_keyword)
    {
        entity_type = EntityType::PROCEDURE;
    }
    else
    {
        throw std::runtime_error(error_messages::invalid_entity_type);
    }
}

void Entity::set_entity_attr(AttributeType attr)
{
    entity_attr = attr;
}

void Entity::set_entity_attr(std::string attr)
{
    if (attr == proc_name_keyword)
    {
        entity_attr = AttributeType::PROCNAME;
    }
    else if (attr == var_name_keyword)
    {
        entity_attr = AttributeType::VARNAME;
    }
    else if (attr == value_keyword)
    {
        entity_attr = AttributeType::VALUE;
    }
    else if (attr == stmt_num_keyword)
    {
        entity_attr = AttributeType::STMTNUM;
    }
    else
    {
        throw std::runtime_error(error_messages::invalid_entity_attr);
    }

    std::vector<EntityType> proc_name_attr = attributes_table.at(entity_attr);
    if (std::find(proc_name_attr.begin(), proc_name_attr.end(), entity_type) == proc_name_attr.end())
    {
        throw std::runtime_error(error_messages::invalid_entity_attr);
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
                throw std::runtime_error(error_messages::invalid_pattern_expression_format);
            }
            entity_name = name;
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
        else if (entity_type == EntityType::STMT || entity_type == EntityType::PROG_LINE)
        {
            /// Checks if var_name is integer
            if (!CheckerUtil::is_const_valid(name))
            {
                throw std::runtime_error(error_messages::invalid_statement_number);
            }
            entity_name = name;
        }
        else if (entity_type == EntityType::BOOLEAN)
        {
            /// Checks if var_name is integer
            if (name != "BOOLEAN")
            {
                throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
            }
            entity_name = name;
        }
        else
        {
            throw std::runtime_error(error_messages::invalid_undeclared_entity_name);
        }
    }
}

void Entity::set_solution(std::string value)
{
    solution_value = value;
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
