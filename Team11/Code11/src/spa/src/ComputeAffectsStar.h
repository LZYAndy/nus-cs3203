#ifndef COMPUTE_AFFECTS_STAR_H
#define COMPUTE_AFFECTS_STAR_H

#include <vector>
#include <unordered_map>

class ComputeAffectsStar
{
public:
    /**
     * affects*(1,2)
     */
    bool is_affects_star(int assignment1, int assignment2);
    /**
     * affects*(1,a)
     */
    std::vector<int> get_affects_star(int assignment);
    /**
     * affects*(a, 1)
     */
    std::vector<int> get_affected_star(int assignment);
        /**
     * affects*(1,a)
     */
    std::vector<int> get_all_affects_star(int assignment);
    /**
     * affects*(a, 1)
     */
    std::vector<int> get_all_affected_star(int assignment);
    /**
     * affected(a, a1)
     */
    std::unordered_map<int, std::vector<int>> get_all_affects_star_relationship();

};

#endif