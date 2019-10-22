#include "ComputeAffectsStar.h"

bool ComputeAffectsStar::is_affects_star(int assignment1, int assignment2)
{
    // check Affects(1,2)
    // if (is_affects(assignment1, assignment2))
    if (is_affects_star(assignment1, assignment2)) // temp to compile
    {
        return true;
    } else {
        // recursive depth-approach
        for (int affects_assignment : get_affects_star(assignment1))
        {
            if (is_affects_star(affects_assignment, assignment2))
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
std::vector<int> ComputeAffectsStar::get_affects_star(int assignment)
{
    
}
/**
    * affects*(a, 1)
    */
std::vector<int> ComputeAffectsStar::get_affected_star(int assignment)
{

}
/**
    * affects*(1,a)
    */
std::vector<int> ComputeAffectsStar::get_all_affects_star(int assignment)
{

}
/**
    * affects*(a, 1)
    */
std::vector<int> ComputeAffectsStar::get_all_affected_star(int assignment)
{

}
/**
    * affected(a, a1)
    */
std::unordered_map<int, std::vector<int>> ComputeAffectsStar::get_all_affects_star_relationship()
{

}
