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
}