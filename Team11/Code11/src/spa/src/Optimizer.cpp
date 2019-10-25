#include "Optimizer.h"

std::string Optimizer::split_clauses_into_groups(std::vector<pql_dto::Entity> select_clause,
    std::deque<pql_dto::Constraint>& synonym_clauses,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses)
{
    std::unordered_set<std::string> select_synonyms_set = {};
    std::vector<std::vector<pql_dto::Constraint>> linked_entities_group = {};

    /// Add synonyms in select clause to a set for lookup
    for (pql_dto::Entity entity : select_clause)
    {
        select_synonyms_set.insert(entity.get_entity_name());
    }

    /// Groups clauses together by overlapping synonyms
    while (synonym_clauses.size() != 0)
    {
        std::unordered_set<std::string> linked_synonyms_set = {};
        std::vector<pql_dto::Constraint> linked_entities = {};

        pql_dto::Constraint first_constraint = synonym_clauses.front();
        if (first_constraint.is_pattern())
        {
            linked_synonyms_set.insert(first_constraint.get_pattern_entity().get_entity_name());
        }

        if (first_constraint.get_first_param().is_entity_declared())
        {
            linked_synonyms_set.insert(first_constraint.get_first_param().get_entity_name());
        }

        if (first_constraint.get_second_param().is_entity_declared())
        {
            linked_synonyms_set.insert(first_constraint.get_second_param().get_entity_name());
        }

        linked_entities.push_back(first_constraint);
        synonym_clauses.pop_front();

        std::deque<pql_dto::Constraint> remaining_syn_clauses = {};

        for (auto iter = synonym_clauses.begin(); iter != synonym_clauses.end(); iter++)
        {
            std::unordered_set<std::string> constraint_syn_set = {};
            pql_dto::Constraint constraint = *iter;

            bool is_in_set = false;

            if (constraint.is_pattern())
            {
                std::string pattern_entity_syn = constraint.get_pattern_entity().get_entity_name();
                constraint_syn_set.insert(pattern_entity_syn);

                if (constraint.get_first_param().is_entity_declared())
                {
                    constraint_syn_set.insert(constraint.get_first_param().get_entity_name());
                }

                if (constraint.get_second_param().is_entity_declared())
                {
                    constraint_syn_set.insert(constraint.get_second_param().get_entity_name());
                }

                for (auto i = constraint_syn_set.begin(); i != constraint_syn_set.end(); i++)
                {
                    if (linked_synonyms_set.find(*i) != linked_synonyms_set.end())
                    {
                        linked_synonyms_set.insert(constraint_syn_set.begin(), constraint_syn_set.end());
                        linked_entities.push_back(constraint);
                        is_in_set = true;
                        break;
                    }
                }
            }
            else
            {
                if (constraint.get_first_param().is_entity_declared())
                {
                    constraint_syn_set.insert(constraint.get_first_param().get_entity_name());
                }

                if (constraint.get_second_param().is_entity_declared())
                {
                    constraint_syn_set.insert(constraint.get_second_param().get_entity_name());
                }

                for (auto i = constraint_syn_set.begin(); i != constraint_syn_set.end(); i++)
                {
                    if (linked_synonyms_set.find(*i) != linked_synonyms_set.end())
                    {
                        linked_synonyms_set.insert(constraint_syn_set.begin(), constraint_syn_set.end());
                        linked_entities.push_back(constraint);
                        is_in_set = true;
                        break;
                    }
                }
            }

            if (!is_in_set)
            {
                remaining_syn_clauses.push_back(constraint);
            }
        }

        linked_entities_group.push_back(linked_entities);
        synonym_clauses = remaining_syn_clauses;
    }

    return "";
}

std::string Optimizer::split_clauses_with_no_synonyms(std::vector<pql_dto::Relationships>& such_that_clause,
    std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause,
    std::deque<pql_dto::Constraint>& no_synonym_clauses, std::deque<pql_dto::Constraint>& synonym_clauses)
{
    replace_with_synonyms(such_that_clause, pattern_clause, with_clause);

    for (pql_dto::Relationships relationship : such_that_clause)
    {
        if (!relationship.get_first_param().is_entity_declared() && !relationship.get_second_param().is_entity_declared())
        {
            pql_dto::Constraint new_constraint = pql_dto::Constraint();
            new_constraint.set_relationship(relationship);
            no_synonym_clauses.push_back(new_constraint);
        }
        else
        {
            pql_dto::Constraint new_constraint = pql_dto::Constraint();
            new_constraint.set_relationship(relationship);
            synonym_clauses.push_back(new_constraint);
        }
    }

    for (pql_dto::Pattern pattern : pattern_clause)
    {
        pql_dto::Constraint new_constraint = pql_dto::Constraint();
        new_constraint.set_pattern(pattern);
        synonym_clauses.push_back(new_constraint);
    }

    for (pql_dto::With with : with_clause)
    {
        pql_dto::Constraint new_constraint = pql_dto::Constraint();
        new_constraint.set_with(with);
        synonym_clauses.push_back(new_constraint);
    }

    return "";
}

void Optimizer::replace_with_synonyms(std::vector<pql_dto::Relationships>& such_that_clause,
    std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause)
{
    for (pql_dto::With with_object : with_clause)
    {
        /// If left reference in With object is not declared
        if (!with_object.get_first_param().is_entity_declared())
        {
            pql_dto::Entity right_ref = with_object.get_second_param();
            for (pql_dto::Relationships relationship : such_that_clause)
            {
                if (relationship.get_first_param().equals(right_ref))
                {
                    /// Replace the left entity with value
                }

                if (relationship.get_second_param().equals(right_ref))
                {
                    /// Replace the right entity with value
                }
            }

            for (pql_dto::Pattern pattern : pattern_clause)
            {
                if (pattern.get_first_param().equals(right_ref))
                {
                    /// Replace the left entity with value
                }

                if (pattern.get_second_param().equals(right_ref))
                {
                    /// Replace the right entity with value
                }
            }
        }
        else if (!with_object.get_second_param().is_entity_declared())
        {
            pql_dto::Entity left_ref = with_object.get_first_param();
            for (pql_dto::Relationships relationship : such_that_clause)
            {
                if (relationship.get_first_param().equals(left_ref))
                {
                    /// Replace the left entity with value
                }

                if (relationship.get_second_param().equals(left_ref))
                {
                    /// Replace the right entity with value
                }
            }

            for (pql_dto::Pattern pattern : pattern_clause)
            {
                if (pattern.get_first_param().equals(left_ref))
                {
                    /// Replace the left entity with value
                }

                if (pattern.get_second_param().equals(left_ref))
                {
                    /// Replace the right entity with value
                }
            }
        }
    }
}
