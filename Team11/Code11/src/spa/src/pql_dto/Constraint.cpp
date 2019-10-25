#include "Constraint.h"

namespace pql_dto
{
    void Constraint::set_pattern(Pattern other)
    {
        pattern = other;
        is_pattern_object = true;
    }

    void Constraint::set_relationship(Relationships other)
    {
        relationship = other;
        is_relationship_object = true;
    }

    void Constraint::set_with(With other)
    {
        with = other;
        is_with_object = true;
    }

    bool Constraint::is_pattern()
    {
        return is_pattern_object;
    }

    bool Constraint::is_relationship()
    {
        return is_relationship_object;
    }

    bool Constraint::is_with()
    {
        return is_with_object;
    }

    Pattern Constraint::get_pattern()
    {
        return pattern;
    }

    Relationships Constraint::get_relationship()
    {
        return relationship;
    }

    With Constraint::get_with()
    {
        return with;
    }

    Entity Constraint::get_first_param()
    {
        if (is_relationship_object)
        {
            return relationship.get_first_param();
        }
        
        if (is_pattern_object)
        {
            return pattern.get_first_param();
        }

        if (is_with_object)
        {
            return with.get_first_param();
        }
    }

    Entity Constraint::get_second_param()
    {
        if (is_relationship_object)
        {
            return relationship.get_second_param();
        }

        if (is_pattern_object)
        {
            return pattern.get_second_param();
        }

        if (is_with_object)
        {
            return with.get_second_param();
        }
    }

    Entity Constraint::get_pattern_entity()
    {
        if (is_pattern_object)
        {
            return pattern.get_pattern_entity();
        }

        throw std::runtime_error(error_messages::not_a_pattern_object);
    }
}