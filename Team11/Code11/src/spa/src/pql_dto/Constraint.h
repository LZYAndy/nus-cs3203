#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#pragma once

#include "Pattern.h"
#include "Relationships.h"

namespace pql_dto
{
    class Constraint
    {
    private:
        Pattern pattern;
        Relationships relationship;

        bool is_pattern_object = false;
        bool is_relationship_object = false;

    public:
        void set_pattern(Pattern other);

        void set_relationship(Relationships other);

        bool is_pattern();

        bool is_relationship();

        Pattern get_pattern();

        Relationships get_relationship();
    };
}

#endif
