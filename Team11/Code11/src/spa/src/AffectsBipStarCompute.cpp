
#include "AffectsBipStarCompute.h"

bool AffectsBipStarCompute::is_affects_bip_star(int assignment1, int assignment2)
{
    std::unordered_set<std::string> states;
    return is_affects_bip_star_helper(assignment1, assignment2, states); 
}

std::vector<int> AffectsBipStarCompute::get_affected_bip_star(int assignment)
{
    std::vector<int> result;
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_bip_star(assignment, assign_stmt))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}

std::vector<int> AffectsBipStarCompute::get_affects_bip_star(int assignment)
{
    std::vector<int> result;
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_bip_star(assign_stmt, assignment))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}

std::unordered_map<int, std::vector<int>> AffectsBipStarCompute::get_all_affects_bip_star_relationship()
{
    std::unordered_map<int, std::vector<int>> affects_bip_star_map;
    std::vector<int> assign_stmts = type_bank->get_all_of_type(EntityType::ASSIGN);
    for (int assign_stmt : assign_stmts)
    {
        std::vector<int> affected_stmts = get_affected_bip_star(assign_stmt);
        if (affected_stmts.empty())
        {
            continue;
        }
        affects_bip_star_map.insert({assign_stmt, affected_stmts});
    }
    return affects_bip_star_map;
}

bool AffectsBipStarCompute::is_affects_bip_star_helper(int assignment1, int assignment2, std::unordered_set<std::string> &states)
{
    // check Affects(1,2)
    if (affects_bip_compute->is_affects_bip(assignment1, assignment2))
    {
        return true;
    }
    else
    {
        // add affects(assign1, assign2) into set of states checked.
        std::string relationship_entry = std::to_string(assignment1) + ',' + std::to_string(assignment2);
        auto result = states.emplace(relationship_entry);
        if (!result.second) // entry already exists in state. => LOOP!
        {
            return false;
        }
        // recursive depth-approach
        for (int affects_assignment : affects_bip_compute->get_assigns_affected_bip_by(assignment1))
        {
            if (is_affects_bip_star_helper(affects_assignment, assignment2, states))
            {
                return true;
            }
        }
    }
    return false;
}
AffectsBipStarCompute::AffectsBipStarCompute(AffectsBipCompute* affects_bip_compute, TypeBank* type_bank)
{
    this->affects_bip_compute = affects_bip_compute;
    this->type_bank = type_bank;
}
