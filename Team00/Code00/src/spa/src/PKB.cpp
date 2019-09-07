#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PKB.h"
#include "TNode.h"

int PKB::setProcToAST(PROC p, TNode* r) {
	return 0;
}

TNode* PKB::getRootAST (PROC p){
	return nullptr;
}

bool PKB::insert_follows(int stmt1, int stmt2)
{
    if (stmt1 == stmt2)
    {
        return false;
    }
    if (stmt1 > stmt2)
    {
        return false;
    }
    follows_bank.put(stmt1, stmt2);
    return true;
}

bool PKB::extract_design()
{
    DesignExtractor::extract_follows_star(&follows_bank, &follows_star_bank);
    DesignExtractor::extract_parent_star(&parent_bank, &parent_star_bank);
    return true;
}

bool PKB::insert_parent(int stmt1, int stmt2)
{
    if (stmt1 == stmt2)
    {
        return false;
    }
    if (stmt1 > stmt2)
    {
        return false;
    }
    parent_bank.put(stmt1, stmt2);
    return true;
}

std::vector<int> PKB::get_all_follows_star(int stmt)
{
    return follows_star_bank.get(stmt);;
}

std::vector<int> PKB::get_all_followed_by(int stmt)
{
    return follows_star_bank.get_reverse(stmt);
}

std::vector<int> PKB::get_parent_star(int stmt)
{
    return parent_star_bank.get(stmt);
}

std::vector<int> PKB::get_children_star(int stmt)
{
    return parent_star_bank.get_reverse(stmt);
}

int PKB::get_follows(int stmt)
{
    std::vector<int> result = follows_bank.get(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

int PKB::get_followed_by(int stmt)
{
    std::vector<int> result = follows_bank.get_reverse(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

int PKB::get_parent(int stmt)
{
    std::vector<int> result = parent_bank.get(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

std::vector<int> PKB::get_children(int stmt)
{
    return parent_bank.get_reverse(stmt);
}

bool PKB::insert_assign(int stmt, string line)
{
    assign_bank.put(stmt, line);
    return true;
}

vector<int> PKB::get_pattern_matches(string var, string pattern)
{
    return assign_bank.matches(var, pattern);
}

vector<int> PKB::get_pattern_contains(string var, string pattern)
{
    return assign_bank.contains(var, pattern);
}

vector<int> PKB::get_all_pattern_matches(string pattern)
{
    return assign_bank.all_matches(pattern);
}

vector<int> PKB::get_all_pattern_contains(string pattern)
{
    return assign_bank.all_contains(pattern);
}