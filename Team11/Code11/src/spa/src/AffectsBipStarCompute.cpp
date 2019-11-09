
#include "AffectsBipStarCompute.h"
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};
struct pair_vector_hash {
    inline std::size_t operator()(const std::pair<int,std::vector<int>> & v) const {
        return v.first*31+v.second.size();
    }
};

bool AffectsBipStarCompute::is_affects_bip_star(int assignment1, int assignment2)
{
//    std::unordered_set<std::string> states;
//    return is_affects_bip_star_helper(assignment1, assignment2, states);
    // check if isaffects()
    if (affects_bip_compute->is_affects_bip(assignment1, assignment2))
    {
        return true;
    }
    else
    {
        if (modifies_bank->get_modified_by_statement(assignment1).empty())
        {
            return false;
        }
        if (uses_bank->get_used_by_statement(assignment2).empty())
        {
            return false;
        }

//        std::string tracked_var = modifies_bank->get_modified_by_statement(assignment1)[0];
//        std::vector<std::string> target_vars = uses_bank->get_used_by_statement(assignment2);
        int inter_modified_stmt = assignment1;
        int end_stmt = assignment2;
//        if (std::find(target_vars.begin(), target_vars.end(), tracked_var) == target_vars.end())
//        {
//            return false;
//        }
        std::vector<std::pair<int, int>> queue; // <stmt, modified_stmt @ that point of time>
        std::unordered_set<std::pair<int, int>, pair_hash> visited_state;
        std::vector<std::pair<int, std::vector<int>>> visited_call_stack;
        std::vector<int> call_stack;
//        std::vector<int> to_visit = bip_bank->get_next_bip(assignment1);
        for (int initial_stmt : bip_bank->get_next_bip(assignment1))
        {
            queue.push_back(std::make_pair(initial_stmt, inter_modified_stmt));
            visited_call_stack.push_back(std::make_pair(initial_stmt, call_stack));
        }
//        queue.push_back(std::make_pair(inter_modified_stmt, inter_modified_stmt));
//        visited_call_stack.push_back(std::make_pair(inter_modified_stmt, call_stack));
        while (!queue.empty())
        {
//            int curr_stmt = to_visit.back();
//            to_visit.pop_back();
            std::pair<int, int> curr_state = queue.back();
            int curr_stmt = curr_state.first;
            inter_modified_stmt = curr_state.second;
            queue.pop_back();
            call_stack = visited_call_stack.back().second;
            visited_call_stack.pop_back();
            if (affects_bip_compute->is_affects_bip(curr_stmt, end_stmt))
            {
                if (affects_bip_compute->is_affects_bip(inter_modified_stmt, curr_stmt))
                {
                    return true;
                }
            }
            if (!visited_state.emplace(curr_state).second) // visited before with inter_modifies_stmt
            {
                if (!call_stack.empty())
                {
                    int after_call = call_stack.back();
                    call_stack.pop_back();
                    visited_call_stack.push_back(std::make_pair(after_call, call_stack));
                    queue.push_back(std::make_pair(after_call, inter_modified_stmt));
//                    to_visit.push_back(after_call);
                    if (affects_bip_compute->is_affects_bip(after_call, end_stmt))
                    {
                        return true;
                    }
                }
                continue;
            }
            if (type_bank->get_statement_type(curr_stmt) == EntityType::CALL)
            {
                std::vector<int> possible_prog_lines = bip_bank->get_egress(curr_stmt);
                std::vector<int> normal_next_stmts = next_bank->get_statements_next(curr_stmt);
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
            if (affects_bip_compute->is_affects_bip(inter_modified_stmt, curr_stmt))
            {
                inter_modified_stmt = curr_stmt;
            }
            std::vector<int> next_stmts = bip_bank->get_next_bip(curr_stmt);
            if (!call_stack.empty())
            {
                // check if next stmt is return to procedure
                if (std::find(next_stmts.begin(), next_stmts.end(), call_stack.back()) != next_stmts.end())
                {
                    int return_stmt = call_stack.back();
                    call_stack.pop_back();
                    visited_call_stack.push_back(std::make_pair(return_stmt, call_stack));
                    queue.push_back(std::make_pair(return_stmt, inter_modified_stmt));
//                    to_visit.push_back(return_stmt);
                    for (int next_stmt : next_stmts) // only add next statement if is not a return statement
                    {
                        if (bip_bank->get_ingress(next_stmt).empty())
                        {
                            visited_call_stack.push_back(std::make_pair(next_stmt, call_stack));
                            queue.push_back(std::make_pair(next_stmt, inter_modified_stmt));
//                            to_visit.push_back(next_stmt);
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
                            possible_exits.push_back(next_possible_stmt);
                        }
                    }
                    if (!possible_exits.empty())
                    {
                        for (int possible_exit : possible_exits)
                        {
                            visited_call_stack.push_back(std::make_pair(possible_exit, call_stack));
                            queue.push_back(std::make_pair(possible_exit, inter_modified_stmt));
//                            to_visit.push_back(possible_exit);
                        }
                    }
                    continue;
                }
            }
            if (!next_stmts.empty())
            {
                for (int next_stmt: next_stmts)
                {
                    std::pair<int, int> state = std::make_pair(next_stmt, inter_modified_stmt);
                    queue.push_back(state);
                    visited_call_stack.push_back(std::make_pair(next_stmt, call_stack));
//                    to_visit.push_back(next_stmt);
                }
            }
        }
    }
    return false;

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
        for (int affects_assignment : affects_bip_compute->get_assigns_affected_bip_by(assignment1, false))
        {
            if (is_affects_bip_star_helper(affects_assignment, assignment2, states))
            {
                return true;
            }
        }
    }
    return false;
}

bool AffectsBipCompute::does_affects_bip_exist()
{
    if (!affects_cache.empty())
    {
        return true;
    }
    else
    {
        get_all_affects_bip_relationship();
        return !affects_cache.empty();
    }
}

AffectsBipStarCompute::AffectsBipStarCompute(AffectsBipCompute* affects_bip_compute, TypeBank* type_bank, NextBipBank* bip_bank, NextBank* next_bank, UsesBank* uses_bank, ModifiesBank* modifies_bank)
{
    this->affects_bip_compute = affects_bip_compute;
    this->type_bank = type_bank;
    this->bip_bank = bip_bank;
    this->next_bank = next_bank;
    this->uses_bank = uses_bank;
    this->modifies_bank = modifies_bank;
}

AffectsBipStarCompute::AffectsBipStarCompute()
{
}