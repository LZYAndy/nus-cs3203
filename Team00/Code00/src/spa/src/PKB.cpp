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

bool PKB::insert_procedure(string name) {

}
bool PKB::insert_variable(string name) {

}

bool PKB::insert_uses(int statement, string variable) {

}
bool PKB::insert_uses(string procedure, string variable) {

}

bool PKB::insert_modifies(int statement, string variable) {

}
bool PKB::insert_modifies(string procedure, string variable) {

}
