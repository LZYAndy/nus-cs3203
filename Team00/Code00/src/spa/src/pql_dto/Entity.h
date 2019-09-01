#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pql_dto {
	class Entity
	{
	private:
		string entity_type;
		string entity_name;

	public:
		string get_entity_type();
		string get_entity_name();

		void set_entity_type();
		void set_entity_name();
	};
}

#endif
