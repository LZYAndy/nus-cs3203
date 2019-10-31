#include "NextBank.h"

bool NextBank::insert_next(int stmt1, int stmt2) {
    if (stmt1 <= 0 || stmt2 <= 0 || stmt1 == stmt2)
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
    return next_bank.check_relationship(stmt1, stmt2);
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

std::unordered_map<int, std::vector<int>> NextBank::get_all_next_relationship() {
    return next_bank.copy();
}

std::unordered_map<int, std::vector<int>> NextBank::get_all_previous_relationship() {
    return next_bank.get_reverse_bank();
}
