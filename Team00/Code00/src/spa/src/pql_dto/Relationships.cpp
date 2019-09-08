#include <string>

using namespace std;

#include "Relationships.h"

namespace pql_dto 
{
    Relationships::Relationships()
    {

    }

    RelationshipType Relationships::get_relationship()
    {
        return relationship_type;
    }

    Entity Relationships::get_first_param()
    {
        return first_param;
    }

    Entity Relationships::get_second_param()
    {
        return second_param;
    }

    bool Relationships::is_relationship_star()
    {
        return is_star;
    }

    std::string Relationships:: set_relationship()
    {

    }

    void Relationships::set_relationship_star(bool is_relationship_star)
    {
        is_star = is_relationship_star;
    }
}
