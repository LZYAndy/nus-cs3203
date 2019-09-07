#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "DesignExtractor.h"
#include "ParentBank.h"
#include "ParentStarBank.h"
#include "AssignBank.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	static VarTable* varTable;
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

	bool extract_design();
	bool insert_follows(int stmt1, int stmt2);
    bool insert_parent(int stmt1, int stmt2);
    bool insert_assign(int stmt, string line);

    vector<int> get_all_follows_star(int stmt);
    vector<int> get_all_followed_by(int stmt);
    int get_follows(int stmt);
    int get_followed_by(int stmt);
    int get_parent(int stmt);
    vector<int> get_children(int stmt);
    vector<int> get_parent_star(int stmt);
    vector<int> get_children_star(int stmt);
    vector<int> get_pattern_matches(string var, string pattern);
    vector<int> get_pattern_contains(string var, string pattern);
    vector<int> get_all_pattern_matches(string pattern);
    vector<int> get_all_pattern_contains(string pattern);


private:
    FollowsBank follows_bank;
    FollowsStarBank follows_star_bank;
    ParentBank parent_bank;
    ParentStarBank parent_star_bank;
    AssignBank assign_bank;
};