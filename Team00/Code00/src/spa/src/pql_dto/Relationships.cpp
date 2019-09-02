#include <string>

using namespace std;

#include "Relationships.h"

namespace pql_dto 
{
	string Relationships::get_relationship() 
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
}
