#include "Constraint.h"

namespace pql_dto
{
    void Constraint::set_pattern(Pattern other)
    {
        pattern = other;
    }

    void Constraint::set_relationship(Relationships other)
    {
        relationship = other;
    }

    bool Constraint::is_pattern()
    {
        return is_pattern;
    }
    bool Constraint::is_relationship()
    {
        return is_relationship;
    }

    Pattern Constraint::get_pattern()
    {
        return pattern;
    }

    Relationships Constraint::get_relationship()
    {
        return relationship;
    }
}