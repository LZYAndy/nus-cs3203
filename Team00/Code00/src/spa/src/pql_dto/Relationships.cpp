#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Relationships.h"

namespace pql_dto {
	string Relationships::get_relationship() {
		return relationship_type;
	}
	string Relationships::get_first_param() {
		return first_param;
	}
	string Relationships::get_second_param() {
		return second_param;
	}
}