#include "With.h"

namespace pql_dto
{
    With::With()
    {
    }

    With::With(Entity first_param, Entity second_param)
    {
        set_first_param(first_param);
        set_second_param(second_param);

        validate_parameters();
        set_undeclared_type();
    }

    Entity With::get_first_param()
    {
        return first_param;
    }

    Entity With::get_second_param()
    {
        return second_param;
    }

    void With::set_first_param(Entity first_entity_param)
    {
        std::vector<EntityType> with_left_ref_type = with_table.front();
        if (std::find(with_left_ref_type.begin(), with_left_ref_type.end(), first_entity_param.get_entity_type()) == with_left_ref_type.end())
        {
            throw std::runtime_error(error_messages::invalid_with_first_param);
        }
        
        first_param = first_entity_param;
    }

    void With::set_second_param(Entity second_entity_param)
    {
        std::vector<EntityType> with_right_ref_type = with_table.back();
        if (std::find(with_right_ref_type.begin(), with_right_ref_type.end(), second_entity_param.get_entity_type()) == with_right_ref_type.end())
        {
            throw std::runtime_error(error_messages::invalid_with_second_param);
        }

        second_param = second_entity_param;
    }

    void With::validate_parameters()
    {
        if ((first_param.is_entity_declared() && first_param.get_entity_type() != EntityType::PROG_LINE
            && first_param.get_entity_attr() == AttributeType::NONE) || (second_param.is_entity_declared()
            && second_param.get_entity_type() != EntityType::PROG_LINE && second_param.get_entity_attr() == AttributeType::NONE))
        {
            throw std::runtime_error(error_messages::invalid_query_with_clause_syntax);
        }

        if (!(is_integer_type(first_param) && is_integer_type(second_param))
            && !(is_string_type(first_param) && is_string_type(second_param)))
        {
            throw std::runtime_error(error_messages::invalid_with_mismatch_type);
        }
    }

    bool With::is_integer_type(Entity entity)
    {
        EntityType type = entity.get_entity_type();
        AttributeType attr = entity.get_entity_attr();

        if (attr == AttributeType::STMTNUM || attr == AttributeType::VALUE)
        {
            return true;
        }

        if (attr == AttributeType::NONE)
        {
            if (type == EntityType::CONSTANT || type == EntityType::CALL || type == EntityType::ASSIGN
                || type == EntityType::IF || type == EntityType::PRINT || type == EntityType::PROG_LINE
                || type == EntityType::READ || type == EntityType::STMT || type == EntityType::WHILE)
            return true;
        }

        return false;
    }

    bool With::is_string_type(Entity entity)
    {
        EntityType type = entity.get_entity_type();
        AttributeType attr = entity.get_entity_attr();

        if (attr == AttributeType::PROCNAME || attr == AttributeType::VARNAME)
        {
            return true;
        }

        if (attr == AttributeType::NONE)
        {
            if (type == EntityType::PROCEDURE || type == EntityType::VARIABLE)
                return true;
        }

        return false;
    }

    void With::set_undeclared_type()
    {
        if (!first_param.is_entity_declared())
        {
            if (second_param.is_entity_declared())
            {
                EntityType right_ref_type = second_param.get_entity_type();
                AttributeType right_ref_attr = second_param.get_entity_attr();

                first_param.set_entity_type(right_ref_type);
                first_param.set_entity_attr(right_ref_attr);
            }
            else
            {
                if (first_param.get_entity_name() != second_param.get_entity_name())
                {
                    throw std::runtime_error(error_messages::with_trivial_false);
                }
            }
        }
        else
        {
            if (!second_param.is_entity_declared())
            {
                EntityType left_ref_type = first_param.get_entity_type();
                AttributeType left_ref_attr = first_param.get_entity_attr();
                
                second_param.set_entity_type(left_ref_type);
                second_param.set_entity_attr(left_ref_attr);
            }
        }
    }

    bool With::equals(With with)
    {
        return first_param.equals(with.first_param)
            && second_param.equals(with.second_param);
    }
}
