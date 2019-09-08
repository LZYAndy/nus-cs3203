#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "UsesBank.h"
#include "ModifiesBank.h"
#include "TypeBank.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

	bool insert_procedure(string name);
	bool insert_variable(string name);

	bool insert_uses(int statement, string variable);
	bool insert_uses(string procedure, string variable);

    bool insert_modifies(int statement, string variable);
    bool insert_modifies(string procedure, string variable);

private:
    UsesBank usesBank;
    ModifiesBank modifiesBank;
    TypeBank typeBank;
};