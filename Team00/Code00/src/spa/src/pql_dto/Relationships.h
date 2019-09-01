#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pql_dto {
	class Relationships
	{
	protected:
		string relationship_type;
		string first_param;
		string second_param;

	public:	
		string get_relationship();
		string get_first_param();
		string get_second_param();

		virtual void set_relationship() = 0;
		virtual void set_first_param() = 0;
		virtual void set_second_param() = 0;
	};
}

#endif