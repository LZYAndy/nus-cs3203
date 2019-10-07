#include "WhileBank.h"

bool WhileBank::insert_while(int statement, std::string condition) {
    if (statement <= 0) {
        return false;
    }
    else
    {
        while_bank.put(statement, condition);
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

std::vector<int> WhileBank::get_while_statements() {
    return while_bank.get_all_keys();
}

std::vector<int> WhileBank::get_while_stmtLst(int statement) {
    return while_stmtLst.get(statement);
}
