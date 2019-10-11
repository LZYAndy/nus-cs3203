#include "WhileBank.h"

bool WhileBank::insert_while(int statement, std::vector<std::string> control_var) {
    if (statement <= 0) {
        return false;
    }
    else
    {
        for (std::string control_var: control_var)
        {
            while_bank.put(statement, control_var);
        }
        return true;
    }
}

bool WhileBank::is_while(int statement) {
    std::vector<int> keys = while_bank.get_all_keys();
    if (keys.size() == 0)
    {
        return false;
    }
    else
    {
        std::vector<int>::iterator ret;
        ret = std::find(keys.begin(), keys.end(), statement);
        if(ret == keys.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

std::vector<int> WhileBank::get_while_stmtLst(int statement) {
    return while_stmtLst.get(statement);
}

bool WhileBank::insert_stmt_in_while_stmtLst(int whileStmt, int statement) {
    if (whileStmt <= 0 || statement <= whileStmt || !is_while(whileStmt))
    {
        return false;
    }
    else
    {
        while_stmtLst.put(whileStmt, statement);
        return true;
    }
}

std::vector<int> WhileBank::get_while_with_control_var(std::string control_var) {
    return while_bank.get_reverse(control_var);
}

std::unordered_map<int, std::vector<std::string>> WhileBank::get_all_whilestmt_and_control_var() {
    return while_bank.copy();
}
