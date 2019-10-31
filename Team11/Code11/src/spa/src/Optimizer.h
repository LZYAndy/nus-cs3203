#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stdexcept>

#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <pql_dto/Constraint.h>
#include <Cache.h>

struct ObjectClassHash
{
    template<typename T>
    std::size_t operator()(T t) const
    {
        return std::hash<std::string>()(t.to_string());
    }
};

class Optimizer
{
public:
    /**
     * Splits the clauses into no synonyms and synonyms.
     * @param such_that_clause The pointer to the such that clause vector.
     * @param pattern_clause The pointer to the pattern clause vector.
     * @param with_clause The pointer to the with clause vector.
     * @param no_synonym_clauses The pointer to the vector containing clauses with no synonyms.
     * @param synonym_clauses The pointer to the vector containing clauses with synonyms.
     * @return The error string if the query is invalid.
     */
    static std::string split_clauses_with_no_synonyms(std::vector<pql_dto::Entity>& select_clause,
        std::vector<pql_dto::Relationships>& such_that_clause, std::vector<pql_dto::Pattern>& pattern_clause,
        std::vector<pql_dto::With>& with_clause, std::deque<pql_dto::Constraint>& no_synonym_clauses,
        std::deque<pql_dto::Constraint>& synonym_clauses);

    /**
     * Group and sort clauses into clauses in select clause and clauses not in select.
     * @param select_clause The pointer to the select clause vector.
     * @param synonym_clauses The pointer to the vector containing clauses with synonyms.
     * @param synonyms_in_select_clauses The pointer to the vector containing groups with synonyms in select clause.
     * @param synonyms_not_in_select_clauses The pointer to the vector containing groups with synonyms not in select clause.
     * @return The error string if the query is invalid.
     */
    static std::string split_clauses_into_groups(std::vector<pql_dto::Entity>& select_clause,
        std::deque<pql_dto::Constraint>& synonym_clauses,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses);

    /**
    * Splits the clauses in the groups.
    * @param select_synonyms_set The pointer to the set of synonyms in select clause.
    * @param linked_entities_group The pointer to the vector of all linked synonyms in groups.
    * @param linked_entities_set The pointer to the set of synonyms in each group of linked synonyms.
    * @param synonyms_in_select_clauses The pointer to the vector containing groups with synonyms in select clause.
    * @param synonyms_not_in_select_clauses The pointer to the vector containing groups with synonyms not in select clause.
    */
    static void split_clauses(std::unordered_set<std::string>& select_synonyms_set,
        std::vector<std::vector<pql_dto::Constraint>>& linked_entities_group,
        std::vector<std::unordered_set<std::string>>& linked_entities_set,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
        std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses);

    /**
     * Sorts the given group.
     * @param entity_group The pointer to the group to be sorted.
     */
    static void sort(std::vector<pql_dto::Constraint>& entity_group, Cache& cache);

private:
    /**
     * Remove duplicates in all clauses.
     * @param such_that_clause The pointer to the such that clause vector.
     * @param pattern_clause The pointer to the pattern clause vector.
     * @param with_clause The pointer to the with clause vector.
     */
    static void remove_duplicates(std::vector<pql_dto::Relationships>& such_that_clause,
        std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause);

    /**
     * Replaces patterns and relationship clauses with constant value in with clause.
     * @param such_that_clause The pointer to the such that clause vector.
     * @param pattern_clause The pointer to the pattern clause vector.
     * @param with_clause The pointer to the with clause vector.
     */
    static void replace_with_synonyms(std::vector<pql_dto::Entity>& select_clause, std::vector<pql_dto::Relationships>& such_that_clause,
        std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause);
};
