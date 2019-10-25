#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <stdexcept>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/Constraint.h>

class Optimizer
{
public:
    std::string split_clauses_into_groups(std::vector<pql_dto::Entity> select_clause,
        std::deque<pql_dto::Constraint>& synonym_clauses,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses);

    std::string split_clauses_with_no_synonyms(std::vector<pql_dto::Relationships>& such_that_clause,
        std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause,
        std::deque<pql_dto::Constraint>& no_synonym_clauses, std::deque<pql_dto::Constraint>& synonym_clauses);

private:
    void replace_with_synonyms(std::vector<pql_dto::Relationships>& such_that_clause,
        std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause);
};
