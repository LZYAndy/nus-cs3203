#include "ComputeAffectsStar.h"

bool ComputeAffectsStar::is_affects_star(PKB& pkb, int assignment1, int assignment2)
{
    std::unordered_set<std::string> states;
    return is_affects_star_helper(pkb, assignment1, assignment2, states); 
}

bool ComputeAffectsStar::is_affects_star_helper(PKB& pkb, int assignment1, int assignment2, std::unordered_set<std::string> &states)
{
    // check Affects(1,2)
    if (pkb.is_affects(assignment1, assignment2))
    {
        return true;
    }
    else
    {
        // add affects(assign1, assign2) into set of states checked.
        std::string relationship_entry = to_string(assignment1) + ',' + to_string(assignment2);
        auto result = states.emplace(relationship_entry);
        if (!result.second) // entry already exists in state. => LOOP!
        {
            return false;
        }
        // recursive depth-approach
        for (int affects_assignment : pkb.get_assigns_affected_by(assignment1))
        {
            if (is_affects_star_helper(pkb, affects_assignment, assignment2, states))
            {
                return true;
            }
        }
    }
    return false;
}

// affects*(1,a)
std::vector<int> ComputeAffectsStar::get_affects_star(PKB& pkb, int assignment)
{
    vector<int> result;
    vector<int> assign_stmts = pkb.get_all_assigns();
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_star(pkb, assignment, assign_stmt))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}

// affects*(a, 1)
std::vector<int> ComputeAffectsStar::get_affected_star(PKB& pkb, int assignment)
{
    vector<int> result;
    vector<int> assign_stmts = pkb.get_all_assigns();
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects_star(pkb, assign_stmt, assignment))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}

// affected(a, a1)
std::unordered_map<int, std::vector<int>> ComputeAffectsStar::get_all_affects_star_relationship(PKB &pkb)
{
    std::unordered_map<int, std::vector<int>> affects_star_map;
    std::vector<int> assign_stmts = pkb.get_all_assigns();
    for (int assign_stmt : assign_stmts)
    {
        std::vector<int> affected_stmts = get_affects_star(pkb, assign_stmt);
        if (affected_stmts.empty())
        {
            continue;
        }
        affects_star_map.insert({assign_stmt, affected_stmts});
    }
    return affects_star_map;
}
