#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "DesignExtractor.h"

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

private:
    FollowsBank follow_bank;
    FollowsStarBank follows_star_bank;
};