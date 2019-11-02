#include "NextBipStarCompute.h"

bool NextBipStarCompute::is_next_bip_star(int previous, int next)
{
    std::stack<int> to_visit;
    std::unordered_set<int> visited;
    std::stack<int> call_stack;

    // DFS
    to_visit.push(previous);

    while (!to_visit.empty())
    {
        int curr_prog_line = to_visit.top();
        to_visit.pop();
        auto visited_result = visited.emplace(curr_prog_line);
        if (!visited_result.second) // visited before
        {
            continue;
        }
        // keep track egress if next line will branchin another procedure
        if (type_bank->get_statement_type(curr_prog_line) == EntityType::CALL)
        {
            call_stack.push(bip_bank->get_egress(curr_prog_line));
        }
        std::vector<int> next_bip_stmts = bip_bank->get_next_bip(curr_prog_line);
        // exit if next prog line is egress
        if (!call_stack.empty())
        {
            if (std::find(next_bip_stmts.begin(), next_bip_stmts.end(), call_stack.top()) != next_bip_stmts.end())
            {
                int next_bip_stmt = call_stack.top();
                call_stack.pop();
                if (next_bip_stmt == next)
                {
                    return true;
                }
                for (int next_bip_node : next_bip_stmts) // add all next other than branchout
                {
                    if (bip_bank->get_ingress(next_bip_node) == -1)
                    {
                        if (next_bip_node == next)
                        {
                            return true;
                        }
                        to_visit.push(next_bip_node);
                    }
                }
                to_visit.push(next_bip_stmt);
                continue;
            }
        }
        for (int next_bip_stmt : next_bip_stmts)
        {
            if (next_bip_stmt == next)
            {
                return true;
            }
            to_visit.push(next_bip_stmt);
        }
    }
    return false;
}

std::vector<int> NextBipStarCompute::get_next_bip_star(int previous)
{
    std::stack<int> to_visit;
    std::unordered_set<int> visited;
    std::stack<int> call_stack;
    std::unordered_set<int> visitors;
    // DFS
    to_visit.push(previous);

    while (!to_visit.empty())
    {
        int curr_prog_line = to_visit.top();
        to_visit.pop();
        auto visited_result = visited.emplace(curr_prog_line);
        if (!visited_result.second) // visited before
        {
            continue;
        }
        // keep track egress if next line will branchin another procedure
        if (type_bank->get_statement_type(curr_prog_line) == EntityType::CALL)
        {
            call_stack.push(bip_bank->get_egress(curr_prog_line));
        }
        std::vector<int> next_bip_stmts = bip_bank->get_next_bip(curr_prog_line);
        // exit if next prog line is egress
        if (!call_stack.empty())
        {
            if (std::find(next_bip_stmts.begin(), next_bip_stmts.end(), call_stack.top()) != next_bip_stmts.end())
            {
                int next_bip_stmt = call_stack.top();
                call_stack.pop();
                for (int next_bip_node : next_bip_stmts) // add all next other than branchout
                {
                    if (bip_bank->get_ingress(next_bip_node) == -1)
                    {
                        to_visit.push(next_bip_node);
                        visitors.emplace(next_bip_node);
                    }
                }
                to_visit.push(next_bip_stmt);
                visitors.emplace(next_bip_stmt);
                continue;
            }
        }
        for (int next_bip_stmt : next_bip_stmts)
        {
            to_visit.push(next_bip_stmt);
            visitors.emplace(next_bip_stmt);
        }
    }
    std::vector<int> visited_vector;
    visited_vector.insert(visited_vector.end(), visitors.begin(), visitors.end());
    return visited_vector;
}

std::vector<int> NextBipStarCompute::get_previous_bip_star(int next)
{
    std::stack<int> to_visit;
    std::unordered_set<int> visited;
    std::stack<int> call_stack;
    std::unordered_set<int> visitors;

    // DFS
    to_visit.push(next);

    while (!to_visit.empty())
    {
        int curr_prog_line = to_visit.top();
        to_visit.pop();
        auto visited_result = visited.emplace(curr_prog_line);
        if (!visited_result.second) // visited before
        {
            continue;
        }
        if (bip_bank->get_ingress(curr_prog_line) != -1)
        {
            call_stack.push(bip_bank->get_ingress(curr_prog_line));
        }
        std::vector<int> previous_bip_stmts = bip_bank->get_previous_bip(curr_prog_line);
        // exit if next prog line is egress
        if (!call_stack.empty())
        {
            if (std::find(previous_bip_stmts.begin(), previous_bip_stmts.end(), call_stack.top()) != previous_bip_stmts.end())
            {
                int previous_bip_stmt = call_stack.top();
                call_stack.pop();
                for (int previous_bip_node : previous_bip_stmts) // add all next other than branchout
                {
                    if (bip_bank->get_egress(previous_bip_node) == -1)
                    {
                        to_visit.push(previous_bip_node);
                        visitors.emplace(previous_bip_node);
                    }
                }
                to_visit.push(previous_bip_stmt);
                visitors.emplace(previous_bip_stmt);
                continue;
            }
        }
        for (int previous_bip_stmt : previous_bip_stmts)
        {
            to_visit.push(previous_bip_stmt);
            visitors.emplace(previous_bip_stmt);
        }
    }

    std::vector<int> visited_vector;
    visited_vector.insert(visited_vector.end(), visitors.begin(), visitors.end());
    return visited_vector;
}

std::unordered_map<int, std::vector<int>> NextBipStarCompute::get_all_next_bip_star_relationship()
{
    auto next_bip_star_relationship = bip_bank->get_all_next_bip_relationship();
    for (auto next_bip_star_entry : next_bip_star_relationship)
    {
        next_bip_star_relationship[next_bip_star_entry.first] = get_next_bip_star(next_bip_star_entry.first);
    }
    return next_bip_star_relationship;
}

NextBipStarCompute::NextBipStarCompute(NextBipBank *bip_bank, TypeBank *type_bank)
{
    this->bip_bank = bip_bank;
    this->type_bank = type_bank;
}

NextBipStarCompute::NextBipStarCompute()
{
}
