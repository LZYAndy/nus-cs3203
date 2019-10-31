#include "Optimizer.h"

std::string Optimizer::split_clauses_with_no_synonyms(std::vector<pql_dto::Entity>& select_clause,
    std::vector<pql_dto::Relationships>& such_that_clause, std::vector<pql_dto::Pattern>& pattern_clause,
    std::vector<pql_dto::With>& with_clause, std::deque<pql_dto::Constraint>& no_synonym_clauses,
    std::deque<pql_dto::Constraint>& synonym_clauses)
{
    remove_duplicates(such_that_clause, pattern_clause, with_clause);
    replace_with_synonyms(select_clause, such_that_clause, pattern_clause, with_clause);

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

std::string Optimizer::split_clauses_into_groups(std::vector<pql_dto::Entity>& select_clause,
    std::deque<pql_dto::Constraint>& synonym_clauses,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses)
{
    std::unordered_set<std::string> select_synonyms_set = {};
    std::vector<std::vector<pql_dto::Constraint>> linked_entities_group = {};
    std::vector<std::unordered_set<std::string>> linked_entities_set = {};

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

        linked_entities_set.push_back(linked_synonyms_set);
        linked_entities_group.push_back(linked_entities);
        synonym_clauses = remaining_syn_clauses;
    }

    return "";
}

void Optimizer::remove_duplicates(std::vector<pql_dto::Relationships>& such_that_clause,
    std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause)
{
    std::unordered_set<pql_dto::Relationships, ObjectClassHash> relationship_set = {};
    std::unordered_set<pql_dto::Pattern, ObjectClassHash> pattern_set = {};
    std::unordered_set<pql_dto::With, ObjectClassHash> with_set = {};

    for (pql_dto::Relationships relationship : such_that_clause)
    {
        relationship_set.insert(relationship);
    }
    std::vector<pql_dto::Relationships> new_relationship_list(relationship_set.begin(), relationship_set.end());
    such_that_clause = new_relationship_list;

    for (pql_dto::Pattern pattern : pattern_clause)
    {
        pattern_set.insert(pattern);
    }
    std::vector<pql_dto::Pattern> new_pattern_list(pattern_set.begin(), pattern_set.end());
    pattern_clause = new_pattern_list;

    for (pql_dto::With with : with_clause)
    {
        pql_dto::With swap_with = pql_dto::With(with.get_second_param(), with.get_first_param());
        if (with_set.find(swap_with) != with_set.end())
        {
            continue;
        }
        with_set.insert(with);
    }
    std::vector<pql_dto::With> new_with_list(with_set.begin(), with_set.end());
    with_clause = new_with_list;
}

void Optimizer::replace_with_synonyms(std::vector<pql_dto::Entity>& select_clause, std::vector<pql_dto::Relationships>& such_that_clause,
    std::vector<pql_dto::Pattern>& pattern_clause, std::vector<pql_dto::With>& with_clause)
{
    std::unordered_map<std::string, int> select_map;
    int index = 0;
    for (pql_dto::Entity select_entity : select_clause)
    {
        select_map[select_entity.get_entity_name()] = index++;
    }

    for (pql_dto::With with_object : with_clause)
    {
        pql_dto::Entity right_ref = with_object.get_second_param();
        pql_dto::Entity left_ref = with_object.get_first_param();

        /// If left reference in With object is not declared
        if (!left_ref.is_entity_declared())
        {
            if (select_map.find(right_ref.get_entity_name()) != select_map.end())
            {
                pql_dto::Entity same_select_entity = select_clause.at(select_map.at(right_ref.get_entity_name()));
                same_select_entity.set_solution(left_ref.get_entity_name());
                same_select_entity.set_entity_type(EntityType::FIX);
                select_clause.at(select_map.at(right_ref.get_entity_name())) = same_select_entity;
            }

            int index = 0;
            for (pql_dto::Relationships relationship : such_that_clause)
            {
                if (relationship.get_first_param().equals(right_ref))
                {
                    /// Replace the left entity with value
                    relationship.update_first_param(left_ref.get_entity_name());
                    such_that_clause.at(index) = relationship;
                }

                if (relationship.get_second_param().equals(right_ref))
                {
                    /// Replace the right entity with value
                    relationship.update_second_param(left_ref.get_entity_name());
                    such_that_clause.at(index) = relationship;
                }

                index++;
            }

            /// Reinitialise the index
            index = 0;
            for (pql_dto::Pattern pattern : pattern_clause)
            {
                if (pattern.get_first_param().equals(right_ref))
                {
                    /// Replace the left entity with value
                    pattern.update_first_param(left_ref.get_entity_name());
                    pattern_clause.at(index) = pattern;
                }

                if (pattern.get_second_param().equals(right_ref))
                {
                    /// Replace the right entity with value
                    pattern.update_second_param(left_ref.get_entity_name());
                    pattern_clause.at(index) = pattern;
                }

                index++;
            }
        }
        else if (!right_ref.is_entity_declared())
        {
            if (select_map.find(left_ref.get_entity_name()) != select_map.end())
            {
                pql_dto::Entity same_select_entity = select_clause.at(select_map.at(left_ref.get_entity_name()));
                same_select_entity.set_solution(right_ref.get_entity_name());
                same_select_entity.set_entity_type(EntityType::FIX);
                select_clause.at(select_map.at(left_ref.get_entity_name())) = same_select_entity;
            }

            int index = 0;

            for (pql_dto::Relationships relationship : such_that_clause)
            {
                if (relationship.get_first_param().equals(left_ref))
                {
                    /// Replace the left entity with value
                    relationship.update_first_param(right_ref.get_entity_name());
                    such_that_clause.at(index) = relationship;
                }

                if (relationship.get_second_param().equals(left_ref))
                {
                    /// Replace the right entity with value
                    relationship.update_second_param(right_ref.get_entity_name());
                    such_that_clause.at(index) = relationship;
                }

                index++;
            }

            index = 0;
            for (pql_dto::Pattern pattern : pattern_clause)
            {
                if (pattern.get_first_param().equals(left_ref))
                {
                    /// Replace the left entity with value
                    pattern.update_first_param(right_ref.get_entity_name());
                    pattern_clause.at(index) = pattern;
                }

                if (pattern.get_second_param().equals(left_ref))
                {
                    /// Replace the right entity with value
                    pattern.update_second_param(right_ref.get_entity_name());
                    pattern_clause.at(index) = pattern;
                }
            }
        }
    }
}

void Optimizer::sort_clauses(std::unordered_set<std::string>& select_synonyms_set,
    std::vector<std::vector<pql_dto::Constraint>>& linked_entities_group,
    std::vector<std::unordered_set<std::string>>& linked_entities_set,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_in_select_clauses,
    std::vector<std::vector<pql_dto::Constraint>>& synonyms_not_in_select_clauses)
{
    for (size_t index = 0; index < linked_entities_set.size(); index++)
    {
        std::unordered_set<std::string> entities_set = linked_entities_set.at(index);
        bool is_in_select = false;

        for (auto i = entities_set.begin(); i != entities_set.end(); i++)
        {
            if (select_synonyms_set.find(*i) != select_synonyms_set.end())
            {
                std::vector<pql_dto::Constraint> entity_group = linked_entities_group.at(index);
                synonyms_in_select_clauses.push_back(entity_group);
                is_in_select = true;
                break;
            }
        }

        if (!is_in_select)
        {
            std::vector<pql_dto::Constraint> entity_group = linked_entities_group.at(index);
            synonyms_not_in_select_clauses.push_back(entity_group);
        }
    }
}

void Optimizer::sort(std::vector<pql_dto::Constraint>& entity_group, Cache& cache)
{
    auto cmp = [](pql_dto::Constraint c1, pql_dto::Constraint c2) { return c1.get_size() < c2.get_size(); };
    std::priority_queue<pql_dto::Constraint, std::vector<pql_dto::Constraint>, decltype(cmp)> one_synonym_group(cmp);
    std::priority_queue<pql_dto::Constraint, std::vector<pql_dto::Constraint>, decltype(cmp)> two_synonym_group(cmp);

    std::vector<pql_dto::Constraint> sorted_entity_group;
    std::unordered_set<std::string> synonyms_in_set;

    for (pql_dto::Constraint constraint : entity_group)
    {
        int clause_size = cache.get_clause_size(constraint);
        constraint.set_size(clause_size);

        pql_dto::Entity first_param = constraint.get_first_param();
        pql_dto::Entity second_param = constraint.get_second_param();

        /// Separates clauses with 1 and 2 synonyms.
        if (first_param.is_entity_declared() && second_param.is_entity_declared())
        {
            two_synonym_group.push(constraint);
        }
        else
        {
            /// Adds with clause with one syn into the start of the list
            if (constraint.is_with())
            {
                sorted_entity_group.push_back(constraint);
                if (first_param.is_entity_declared())
                {
                    synonyms_in_set.insert(first_param.get_entity_name());
                }
                else
                {
                    synonyms_in_set.insert(second_param.get_entity_name());
                }
            }
            else if (constraint.is_pattern())
            {
                if (!first_param.is_entity_declared())
                {
                    one_synonym_group.push(constraint);
                }
                else
                {
                    two_synonym_group.push(constraint);
                }
            }
            else
            {
                one_synonym_group.push(constraint);
            }
        }
    }

    std::priority_queue<pql_dto::Constraint, std::vector<pql_dto::Constraint>, decltype(cmp)> remaining_one_synonym_group(cmp);
    std::priority_queue<pql_dto::Constraint, std::vector<pql_dto::Constraint>, decltype(cmp)> remaining_two_synonym_group(cmp);
    bool is_added = false;

    while (!one_synonym_group.empty() || !two_synonym_group.empty())
    {
        if (!one_synonym_group.empty())
        {
            pql_dto::Constraint one_syn_clause = one_synonym_group.top();
            one_synonym_group.pop();

            pql_dto::Entity first_param = one_syn_clause.get_first_param();
            pql_dto::Entity second_param = one_syn_clause.get_second_param();

            if (one_syn_clause.is_pattern())
            {
                pql_dto::Entity pattern_entity = one_syn_clause.get_pattern_entity();
                if (synonyms_in_set.find(pattern_entity.get_entity_name()) != synonyms_in_set.end())
                {
                    sorted_entity_group.push_back(one_syn_clause);
                    continue;
                }
            }

            if (first_param.is_entity_declared())
            {
                if (synonyms_in_set.find(first_param.get_entity_name()) != synonyms_in_set.end())
                {
                    sorted_entity_group.push_back(one_syn_clause);
                    continue;
                }
            }
            else
            {
                if (synonyms_in_set.find(second_param.get_entity_name()) != synonyms_in_set.end())
                {
                    sorted_entity_group.push_back(one_syn_clause);
                    continue;
                }
            }

            remaining_one_synonym_group.push(one_syn_clause);
        }       
        else if (!remaining_one_synonym_group.empty() && is_added)
        {
            while (!remaining_one_synonym_group.empty())
            {
                one_synonym_group.push(remaining_one_synonym_group.top());
                remaining_one_synonym_group.pop();
            }
            is_added = false;
        }
        else if (!two_synonym_group.empty())
        {
            pql_dto::Constraint two_syn_clause = two_synonym_group.top();
            two_synonym_group.pop();

            pql_dto::Entity first_param = two_syn_clause.get_first_param();
            pql_dto::Entity second_param = two_syn_clause.get_second_param();

            if (first_param.is_entity_declared() && second_param.is_entity_declared())
            {
                if (synonyms_in_set.find(first_param.get_entity_name()) != synonyms_in_set.end()
                    || synonyms_in_set.find(second_param.get_entity_name()) != synonyms_in_set.end())
                {
                    sorted_entity_group.push_back(two_syn_clause);
                    synonyms_in_set.insert(first_param.get_entity_name());
                    synonyms_in_set.insert(second_param.get_entity_name());
                    is_added = true;
                    continue;
                }
            }
            else
            {
                pql_dto::Entity pattern_entity = two_syn_clause.get_pattern_entity();
                if (first_param.is_entity_declared())
                {
                    if (synonyms_in_set.find(pattern_entity.get_entity_name()) != synonyms_in_set.end()
                        || synonyms_in_set.find(first_param.get_entity_name()) != synonyms_in_set.end())
                    {
                        sorted_entity_group.push_back(two_syn_clause);
                        synonyms_in_set.insert(pattern_entity.get_entity_name());
                        synonyms_in_set.insert(first_param.get_entity_name());
                        is_added = true;
                        continue;
                    }
                }
                else
                {
                    if (synonyms_in_set.find(pattern_entity.get_entity_name()) != synonyms_in_set.end())
                    {
                        sorted_entity_group.push_back(two_syn_clause);
                        synonyms_in_set.insert(pattern_entity.get_entity_name());
                        is_added = true;
                        continue;
                    }
                }
            }
            remaining_two_synonym_group.push(two_syn_clause);
        }
        else if (!remaining_two_synonym_group.empty())
        {
            while (!remaining_two_synonym_group.empty())
            {
                two_synonym_group.push(remaining_two_synonym_group.top());
                remaining_two_synonym_group.pop();
            }
        }
    }
}