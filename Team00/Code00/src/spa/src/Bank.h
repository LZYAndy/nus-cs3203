#pragma once
#ifndef AUTOTESTER_BANK_H
#define AUTOTESTER_BANK_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <pql_dto/Entity.h>

template<class T, class S>
class Bank
{
public:
    void put(T key, S value);
    std::vector<S> get(T key);
    std::vector<T> get_reverse(S key);
    std::vector<T> get_all_keys();
    std::vector<S> get_all_values();
    bool empty();
    std::unordered_map<T, std::vector<S>> copy();
    bool check_relationship(T key, S value);
    
protected:
    std::unordered_map<T, std::vector<S>> bank;
    std::unordered_map<S, std::vector<T>> reverse_bank;

};

#endif //AUTOTESTER_BANK_H
