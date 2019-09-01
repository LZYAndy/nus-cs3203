#ifndef PATTERN_H
#define PATTERN_H

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace pql_dto {
	class Pattern
	{
	private:
		string pattern_type;
		string pattern_name;
		string first_param;
		string second_param;

	public:
		string get_pattern_type();
		string get_pattern_name();
		string get_first_param();
		string get_second_param();

		void set_pattern_type();
		void set_pattern_name();
		void set_first_param();
		void set_second_param();
	};
}

#endif