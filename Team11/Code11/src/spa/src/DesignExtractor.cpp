#include "DesignExtractor.h"
#include <unordered_set>
#include <stack>

bool DesignExtractor::extract_follows_star(FollowsBank &bank_in, FollowsStarBank &bank_out)
{
    if (!bank_in.does_follows_exists())
    {
        return false;
    }

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
    return true;
}

bool DesignExtractor::extract_parent_star(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank)
{
    if (!bank_in.does_parent_exist())
    {
        return false;
    }
    std::vector<int> keys = bank_in.get_all_parent();
    for (int key : keys)
    {
        extract_further_parents_child(bank_in, bank_out, uses_bank, modifies_bank, std::vector<int>(), key);
    }
    return true;
}

void DesignExtractor::extract_further_parents_child(ParentBank &bank_in, ParentStarBank &bank_out, UsesBank &uses_bank, ModifiesBank &modifies_bank, std::vector<int> parents, int child)
{
    std::vector<int> children = bank_in.get_children(child);
    if (!children.empty())
    {
        parents.push_back(child);
        for (int kid : children)
        {
            extract_further_parents_child(bank_in, bank_out, uses_bank, modifies_bank, parents, kid);
        }
    }
    for (int parent : parents)
    {
        if (parent == child)
        {
            continue;
        }
        bank_out.insert_parent_star(parent, child);
        std::vector<std::string> uses_var = uses_bank.get_used_by_statement(child);
        if (!uses_var.empty())
        {
            for (std::string var : uses_var)
            {
                uses_bank.insert_uses(parent, var);
            }
        }
        std::vector<std::string> modifies_var = modifies_bank.get_modified_by_statement(child);
        if (!modifies_var.empty())
        {
            for (std::string var : modifies_var)
            {
                modifies_bank.insert_modifies(parent, var);
            }
        }
    }
    return;
}

bool DesignExtractor::extract_calls_star(CallsBank &bank_in, CallsStarBank &bank_out)
{
    // copy callsBank to CallsStarBank
    for (std::pair<std::string, std::vector<std::string>> in: bank_in.get_all_procedures_calls_relationship())
    {
        for (std::string proc_called: in.second)
        {
            bank_out.insert_calls_star(in.first, proc_called);
        }
    }
    std::vector<std::string> keys  = bank_out.get_all_procedures_calls_star();
    int i = 0;
    while (i < keys.size())
    {
        for (int j = i; j <= keys.size(); j++)
        {
            for (std::string proc_calls : bank_out.get_procedures_calls_star(keys[j])) // get all proc that calls key (_, key)
            {  
                for (std::string proc_called_by_key : bank_out.get_procedures_called_by_star(keys[j]))
                {
                    bool insert_result = bank_out.insert_calls_star(proc_calls, proc_called_by_key);
                    if (!insert_result)
                    {
                        return false;
                    }
                }
            }
        }
        i++;
    }
    

    return true;
    // // build tree 
    // // topo sort
    // auto calls_keys = bank_in.get_all_procedures_calls();
    // auto calls_values = bank_in.get_all_procedures_called();
    // std::unordered_set<std::string> unique_procs;
    // std::unordered_map<std::string, int> proc_to_index_lookup;
    // for (std::string proc : calls_keys)
    // {
    //     unique_procs.insert(proc);
    // }
    // for (std::string proc : calls_values)
    // {
    //     unique_procs.insert(proc);
    // }
    // int no_of_procs = unique_procs.size();
    // int index = 0;
    // for (std::string proc : unique_procs)
    // {
    //     ++index;
    //     proc_to_index_lookup.insert({proc, index});
    // }
    // std::vector<int> adj[no_of_procs];
    // std::unordered_map<std::string, std::vector<std::string>> calls_relationship = bank_in.get_all_procedures_calls_relationship();
    // for (std::pair<std::string, std::vector<std::string>> pair : calls_relationship)
    // {
    //     for (std::string called_proc : pair.second)
    //     {
    //         adj[proc_to_index_lookup.at(pair.first)].push_back(proc_to_index_lookup.at(called_proc));
    //     }
    // }
    // // terminate if there is no node with no outgoing edge
    // bool edges_exist = false;
    // for (std::vector<int> v : adj)
    // {
    //     if (v.empty())
    //     {
    //         edges_exist = true;
    //     }
    // }
    // if (!edges_exist)
    // {
    //     return false;
    // }

    // std::stack<int> stack;
    // std::vector<bool> visited(no_of_procs, false);
    // stack.push(1);
    // int s;
    // while (!stack.empty())
    // {
    //     s = stack.top(); 
    //     stack.pop();

    //     if (!visited[s]) 
    //     { 
    //         visited[s] = true; 
    //     } 
    //     for (auto i = adj[s].begin(); i != adj[s].end(); ++i) 
    //         if (!visited[*i]) 
    //             stack.push(*i); 
    //     } 
    // }
}
