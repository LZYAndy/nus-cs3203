#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#pragma once

#include "Pattern.h"
#include "Relationships.h"
#include "With.h"

namespace pql_dto
{
    class Constraint
    {
    private:
        Pattern pattern;
        Relationships relationship;
        With with;

        bool is_pattern_object = false;
        bool is_relationship_object = false;
        bool is_with_object = false;

    public:
        void set_pattern(Pattern other);

        void set_relationship(Relationships other);

        void set_with(With with);

        bool is_pattern();

        bool is_relationship();

        bool is_with();

        Pattern get_pattern();

        Relationships get_relationship();

        With get_with();
    };
}

#endif
