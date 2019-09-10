#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Pattern.h"

namespace pql_dto
{
    Pattern::Pattern()
    {
    }

    Pattern::Pattern(Entity pattern_entity, Entity first_param, Entity second_param)
    {
        set_pattern_entity(pattern_entity);
        set_first_param(first_param);
        set_second_param(second_param);
    }

    Entity Pattern::get_pattern_entity()
    {
        return pattern_entity;
    }

    Entity Pattern::get_first_param()
    {
        return first_param;
    }

    Entity Pattern::get_second_param()
    {
        return second_param;
    }

    void Pattern::set_pattern_entity(Entity pattern_entity)
    {
    }

    void Pattern::set_first_param(Entity first_param)
    {
    }

    void Pattern::set_second_param(Entity second_param)
    {
    }
}
