#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/Constraint.h>

class Optimizer
{
public:
    std::vector<std::vector<pql_dto::Constraint>> optimize();
};
