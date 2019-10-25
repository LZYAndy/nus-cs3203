#include "ComputeAffectsStar.h"
int is_affects(int a, int b);

bool ComputeAffectsStar::is_affects_star(PKB& pkb, int assignment1, int assignment2)
{
    // check Affects(1,2)
    if (is_affects(assignment1, assignment2))
    {
        return true;
    } else {
        // recursive depth-approach
        for (int affects_assignment : get_affects_star(pkb, assignment1))
        {
            if (is_affects_star(pkb, affects_assignment, assignment2))
            {
                return true;
            }
        }
    }
    return false;
}
/**
    * affects*(1,a)
    */
std::vector<int> ComputeAffectsStar::get_affects_star(PKB& pkb, int assignment)
{
    vector<int> result;
    vector<int> assign_stmts = pkb.get_all_assigns();
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects(assign_stmt, assignment))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}
/**
    * affects*(a, 1)
    */
std::vector<int> ComputeAffectsStar::get_affected_star(PKB& pkb, int assignment)
{
    vector<int> result;
    vector<int> assign_stmts = pkb.get_all_assigns();
    for (int assign_stmt : assign_stmts)
    {
        if (is_affects(assign_stmt, assignment))
        {
            result.push_back(assign_stmt);
        }
    }
    return result;
}
/**
    * affects*(1,a)
    */
std::vector<int> ComputeAffectsStar::get_all_affects_star(int assignment)
{
   // See get_all_affects()
   std::vector<int> result;
   return result;
}
/**
    * affects*(a, 1)
    */
std::vector<int> ComputeAffectsStar::get_all_affected_star(int assignment)
{
  // See get_all_affected
   std::vector<int> result;
   return result;
}
/**
    * affected(a, a1)
    */
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
