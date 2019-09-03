#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Entity.h"

namespace pql_dto 
{
    EntityType Entity::get_entity_type()
    {
        return entity_type;
    }

    string Entity::get_entity_name() 
    {
        return entity_name;
    }

    bool Entity::is_entity_declared()
    {
        return is_declared_entity;
    }

    void Entity::set_entity_type() 
    {
    }

    void Entity::set_entity_name() 
    {
    }

    void Entity::set_is_declared(bool is_declared)
    {
        is_declared_entity = is_declared;
    }
}
