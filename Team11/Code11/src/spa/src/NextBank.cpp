#include "NextBank.h"

bool NextBank::insert_next(int stmt1, int stmt2) {
    if (stmt2 <= stmt1)
    {
        return false;
    }
    else
    {
        next_bank.put(stmt1, stmt2);
        return true;
    }
}

bool NextBank::is_next(int stmt1, int stmt2) {
    std::vector<int> elements = next_bank.get(stmt1);
    if(elements.size() == 0)
    {
        return false;
    }
    else
    {
        std::vector<int>::iterator ret;
        ret = std::find(elements.begin(), elements.end(), stmt2);
        if(ret == elements.end())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool NextBank::does_next_exists() {
    return !next_bank.empty();
}

std::vector<int> NextBank::get_statements_previous(int statement) {
    return next_bank.get_reverse(statement);
}

std::vector<int> NextBank::get_statements_next(int statement) {
    return next_bank.get(statement);
}

std::vector<int> NextBank::get_all_previous() {
    return next_bank.get_all_keys();
}

std::vector<int> NextBank::get_all_next() {
    return next_bank.get_all_values();
}
