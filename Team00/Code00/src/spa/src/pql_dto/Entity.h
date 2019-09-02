#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pql_dto 
{
	class Entity
	{
	private:
		string entity_type;
		string entity_name;

		bool is_declared_entity = false;

	public:
		string get_entity_type();
		string get_entity_name();
		
		bool is_entity_declared();

		void set_entity_type();
		void set_entity_name();
		void set_is_declared(bool is_declared);
	};
}

#endif
