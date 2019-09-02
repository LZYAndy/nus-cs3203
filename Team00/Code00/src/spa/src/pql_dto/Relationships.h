#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Entity.h"

namespace pql_dto 
{
	class Relationships
	{
	protected:
		string relationship_type;
		Entity first_param;
		Entity second_param;

	public:	
		string get_relationship();
		Entity get_first_param();
		Entity get_second_param();

		virtual void set_relationship() = 0;
		virtual void set_first_param() = 0;
		virtual void set_second_param() = 0;
	};
}

#endif