#include "DesignExtractor.h"

void DesignExtractor::extract_follows_star(FollowsBank* bank_in, FollowsStarBank* bank_out)
{
    extract_star(bank_in, bank_out);
}

void DesignExtractor::extract_parent_star(ParentBank* bank_in, ParentStarBank* bank_out)
{
    extract_star(bank_in, bank_out);
}

void DesignExtractor::extract_star(Bank<int, int>* bank_in, Bank<int, int>* bank_out)
{
    std::vector<int> keys = bank_in->get_all_keys();
    for (int key : keys)
    {
        while (true)
        {
            int current = key;
            std::vector<int> result = bank_in->get(current);
            if (result.empty())
            {
                break;
            }
            int value = result.back();
            bank_out->put(key, value);
        }
    }
}
