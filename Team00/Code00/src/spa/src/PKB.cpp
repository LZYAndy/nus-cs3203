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
    follow_bank.put(stmt1, stmt2);
    return true;
}

bool PKB::extract_design()
{
    DesignExtractor::extract_follows_star(&follow_bank, &follows_star_bank);
    return true;
}