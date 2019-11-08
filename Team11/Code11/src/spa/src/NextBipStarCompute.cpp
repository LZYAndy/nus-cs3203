#include "NextBipStarCompute.h"

bool NextBipStarCompute::is_next_bip_star(int previous, int next)
{
    std::vector<int> to_visit;
    std::unordered_set<int> visited;
    std::vector<int> call_stack;
    std::vector<int> before_call_stack;

    to_visit.push_back(previous);
    while (!to_visit.empty())
    {
        int curr_prog_line = to_visit.back();
        to_visit.pop_back();
        auto visited_result = visited.emplace(curr_prog_line);
        if (!visited_result.second)
        {
            if (!call_stack.empty())
            {
                int after_call = call_stack.back();
                to_visit.push_back(after_call);
                call_stack.pop_back();
                if (after_call == next)
                {
                    return true;
                }

            }
            continue;
        }
        if (type_bank->get_statement_type(curr_prog_line) == EntityType::CALL)
        {
            before_call_stack.push_back(curr_prog_line);
            std::vector<int> possible_prog_lines = bip_bank->get_egress(curr_prog_line);
            std::vector<int> normal_next_stmts = next_bank->get_statements_next(curr_prog_line);
            if (!normal_next_stmts.empty())
            {
                int normal_next_stmt = normal_next_stmts[0];
                for (int possible_prog_line : possible_prog_lines)
                {
                    if (possible_prog_line == normal_next_stmt)
                    {
                        call_stack.push_back(normal_next_stmt);
                    }
                }
            }
            if (!possible_prog_lines.empty())
            {
                if (possible_prog_lines.front() == -1)
                {
                    call_stack.push_back(-1);
                }
            }

        }
        std::vector<int> next_stmts = bip_bank->get_next_bip(curr_prog_line);
        if (!call_stack.empty())
        {
            // check if next stmt is return to procedure
            if (std::find(next_stmts.begin(), next_stmts.end(), call_stack.back()) != next_stmts.end())
            {
                int return_statement = call_stack.back();
                call_stack.pop_back();
                if (return_statement == next)
                {
                    return true;
                }
                to_visit.push_back(return_statement);
                for (int next_stmt : next_stmts) // only add next statement if is not a return statement
                {
                    if (bip_bank->get_ingress(next_stmt).empty())
                    {
                        if (next_stmt == next)
                        {
                            return true;
                        }
                        to_visit.push_back(next_stmt);
                    }
                }
                continue;
            }
            if (call_stack.back() == -1)
            {
                std::vector<int> possible_exits;
                for (int next_possible_stmt : next_stmts)
                {
                    if (bip_bank->get_ingress(next_possible_stmt).empty())
                    {
                        if (next_possible_stmt == next)
                        {
                            return true;
                        }
                        possible_exits.push_back(next_possible_stmt);
                    }
                }
                if (!possible_exits.empty())
                {
                    for (int possible_exit : possible_exits)
                    {
                        next_stmts.push_back(possible_exit);
                    }
                }
                continue;
            }
        }

        for (int next_stmt : next_stmts)
        {
            if (next_stmt == next)
            {
                return true;
            }
            to_visit.push_back(next_stmt);
        }
    }
    return false;
}
//    // DFS
//    to_visit.push_back(previous);
//
//    while (!to_visit.empty())
//    {
//        int curr_prog_line = to_visit.back();
//        to_visit.pop_back();
//        auto visited_result = visited.emplace(curr_prog_line);
//        if (!visited_result.second) // visited before
//        {
//            continue;
//        }
//        // keep track egress if next line will branchin another procedure
//        if (type_bank->get_statement_type(curr_prog_line) == EntityType::CALL)
//        {
//            call_stack.push_back(bip_bank->get_egress(curr_prog_line));
//        }
//        std::vector<int> next_bip_stmts = bip_bank->get_next_bip(curr_prog_line);
//        // exit if next prog line is egress
//        if (!call_stack.empty())
//        {
//            if (std::find(next_bip_stmts.begin(), next_bip_stmts.end(), call_stack.back()) != next_bip_stmts.end())
//            {
//                int next_bip_stmt = call_stack.back();
//                call_stack.pop_back();
//                if (next_bip_stmt == next)
//                {
//                    return true;
//                }
//                for (int next_bip_node : next_bip_stmts) // add all next other than branchout
//                {
//                    if (bip_bank->get_ingress(next_bip_node).empty())
//                    {
//                        if (next_bip_node == next)
//                        {
//                            return true;
//                        }
//                        to_visit.push_back(next_bip_node);
//                    }
//                }
//                to_visit.push_back(next_bip_stmt);
//                continue;
//            }
//        }
//        for (int next_bip_stmt : next_bip_stmts)
//        {
//            if (next_bip_stmt == next)
//            {
//                return true;
//            }
//            to_visit.push_back(next_bip_stmt);
//        }
//    }
//    return false;
//}

std::vector<int> NextBipStarCompute::get_next_bip_star(int previous)
{
    std::unordered_set<int> combined_set;
    std::vector<int> result;
    for (int stmt : bip_bank->get_all_next_bip())
    {
        combined_set.insert(stmt);
    }
    for (int stmt : bip_bank->get_all_previous_bip())
    {
        combined_set.insert(stmt);
    }
    for (int stmt : combined_set)
    {
        if (is_next_bip_star(previous, stmt))
        {
            result.push_back(stmt);
        }
    }
    return result;
}
//    std::stack<int> to_visit;
//    std::unordered_set<int> visited;
//    std::stack<int> call_stack;
//    std::unordered_set<int> visitors;
//    // DFS
//    to_visit.push(previous);
//
//    while (!to_visit.empty())
//    {
//        int curr_prog_line = to_visit.top();
//        to_visit.pop();
//        auto visited_result = visited.emplace(curr_prog_line);
//        if (!visited_result.second) // visited before
//        {
//            continue;
//        }
//        // keep track egress if next line will branchin another procedure
//        if (type_bank->get_statement_type(curr_prog_line) == EntityType::CALL)
//        {
//            call_stack.push(bip_bank->get_egress(curr_prog_line));
//        }
//        std::vector<int> next_bip_stmts = bip_bank->get_next_bip(curr_prog_line);
//        // exit if next prog line is egress
//        if (!call_stack.empty())
//        {
//            if (std::find(next_bip_stmts.begin(), next_bip_stmts.end(), call_stack.top()) != next_bip_stmts.end())
//            {
//                int next_bip_stmt = call_stack.top();
//                call_stack.pop();
//                for (int next_bip_node : next_bip_stmts) // add all next other than branchout
//                {
//                    if (bip_bank->get_ingress(next_bip_node).empty())
//                    {
//                        to_visit.push(next_bip_node);
//                        visitors.emplace(next_bip_node);
//                    }
//                }
//                to_visit.push(next_bip_stmt);
//                visitors.emplace(next_bip_stmt);
//                continue;
//            }
//        }
//        for (int next_bip_stmt : next_bip_stmts)
//        {
//            to_visit.push(next_bip_stmt);
//            visitors.emplace(next_bip_stmt);
//        }
//    }
//    std::vector<int> visited_vector;
//    visited_vector.insert(visited_vector.end(), visitors.begin(), visitors.end());
//    return visited_vector;
//}

std::vector<int> NextBipStarCompute::get_previous_bip_star(int next)
{
    std::unordered_set<int> combined_set;
    std::vector<int> result;
    for (int stmt : bip_bank->get_all_next_bip())
    {
        combined_set.insert(stmt);
    }
    for (int stmt : bip_bank->get_all_previous_bip())
    {
        combined_set.insert(stmt);
    }
    for (int stmt : combined_set)
    {
        if (is_next_bip_star(stmt, next))
        {
            result.push_back(stmt);
        }
    }
    return result;
}
    // DFS
//    to_visit.push(next);
//
//    while (!to_visit.empty())
//    {
//        int curr_prog_line = to_visit.top();
//        to_visit.pop();
//        auto visited_result = visited.emplace(curr_prog_line);
//        if (!visited_result.second) // visited before
//        {
//            continue;
//        }
//        if (bip_bank->get_ingress(curr_prog_line).empty())
//        {
//            call_stack.push(bip_bank->get_ingress(curr_prog_line));
//        }
//        std::vector<int> previous_bip_stmts = bip_bank->get_previous_bip(curr_prog_line);
//        // exit if next prog line is egress
//        if (!call_stack.empty())
//        {
//            if (std::find(previous_bip_stmts.begin(), previous_bip_stmts.end(), call_stack.top())
//                    != previous_bip_stmts.end())
//            {
//                int previous_bip_stmt = call_stack.top();
//                call_stack.pop();
//                for (int previous_bip_node : previous_bip_stmts) // add all next other than branchout
//                {
//                    if (bip_bank->get_egress(previous_bip_node) == -1)
//                    {
//                        to_visit.push(previous_bip_node);
//                        visitors.emplace(previous_bip_node);
//                    }
//                }
//                to_visit.push(previous_bip_stmt);
//                visitors.emplace(previous_bip_stmt);
//                continue;
//            }
//        }
//        for (int previous_bip_stmt : previous_bip_stmts)
//        {
//            to_visit.push(previous_bip_stmt);
//            visitors.emplace(previous_bip_stmt);
//        }
//    }
//
//    std::vector<int> visited_vector;
//    visited_vector.insert(visited_vector.end(), visitors.begin(), visitors.end());
//    return visited_vector;
//}

std::unordered_map<int, std::vector<int>> NextBipStarCompute::get_all_next_bip_star_relationship()
{
    auto next_bip_star_relationship = bip_bank->get_all_next_bip_relationship();
    for (auto next_bip_star_entry : next_bip_star_relationship)
    {
        next_bip_star_relationship[next_bip_star_entry.first] = get_next_bip_star(next_bip_star_entry.first);
    }
    return next_bip_star_relationship;
}

NextBipStarCompute::NextBipStarCompute(NextBipBank* bip_bank, TypeBank* type_bank, NextBank* next_bank)
{
    this->bip_bank = bip_bank;
    this->type_bank = type_bank;
    this->next_bank = next_bank;
}

NextBipStarCompute::NextBipStarCompute()
{
}
