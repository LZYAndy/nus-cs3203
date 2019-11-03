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

        int size = 0;

        bool is_pattern_object = false;
        bool is_relationship_object = false;
        bool is_with_object = false;

    public:
        /** Sets the pattern object in the Constraint.
         *  @param other The pattern object.
         */
        void set_pattern(Pattern other);

        /** Sets the relationship object in the Constraint.
         *  @param other The relationship object.
         */
        void set_relationship(Relationships other);

        /** Sets the with object in the Constraint.
         *  @param other The with object.
         */
        void set_with(With with);

        /** Sets the size of the clause in the Constraint.
         *  @param size The size of the result.
         */
        void set_size(int size);

        // Returns true if it is a pattern object.
        bool is_pattern();

        // Returns true if it is a relationship object.
        bool is_relationship();

        // Returns true if it is a with object.
        bool is_with();

        // Returns the pattern object.
        Pattern get_pattern();

        // Returns the relationship object.
        Relationships get_relationship();

        // Returns the with object.
        With get_with();

        // Returns the First param of the object.
        Entity get_first_param();

        // Returns the second param of the object.
        Entity get_second_param();

        // Returns the pattern entity of the pattern object.
        Entity get_pattern_entity();

        // Returns the clause size of the constraint.
        int get_size();

        /** Checks if both constraints are the same.
         *  @param other The object to be compared.
         */
        bool equals(Constraint other);
    };
}

#endif
