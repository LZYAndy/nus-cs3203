#include "DesignExtractor.h"

void DesignExtractor::extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out)
{
    std::vector<int> keys = bank_in.get_all_followed();
    for (int key : keys)
    {
        int current = key;
        while (true)
        {
            int value = bank_in.get_follows(current);
            if (value == -1)
            {
                break;
            }
            bank_out.insert_follows_star(key, value);
            current = value;
        }
    }
}

void DesignExtractor::extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out)
{

    std::vector<int> keys = bank_in.get_all_parent();
    for (int key : keys)
    {
        extract_further_parents_child(bank_in, bank_out, std::vector<int>(), key);
    }

}

void DesignExtractor::extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, std::vector<int> parents, int child)
{
    std::vector<int> children = bank_in.get_children(child);
    if (!children.empty())
    {
        parents.push_back(child);
        for (int kid : children)
        {
            extract_further_parents_child(bank_in, bank_out, parents, kid);
        }
    }
    for (int parent : parents)
    {
        if (parent == child)
        {
            continue;
        }
        bank_out.insert_parent_star(parent, child);
    }
    return;
}
