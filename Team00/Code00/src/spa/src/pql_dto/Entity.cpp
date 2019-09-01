#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Entity.h"

namespace pql_dto {
	string Entity::get_entity_type() {
		return entity_type;
	}
	string Entity::get_entity_name() {
		return entity_name;
	}

	void Entity::set_entity_type() {};
	void Entity::set_entity_name() {};
}