#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Pattern.h"

namespace pql_dto {
	string Pattern::get_pattern_type() {
		return pattern_type;
	}
	string Pattern::get_pattern_name() {
		return pattern_name;
	}
	string Pattern::get_first_param() {
		return first_param;
	}
	string Pattern::get_second_param() {
		return second_param;
	}

	void Pattern::set_pattern_type() {};
	void Pattern::set_pattern_name() {};
	void Pattern::set_first_param() {};
	void Pattern::set_second_param() {};
}