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
    /**
     * Insert key-value pair into Bank and also create a reverse mapping of it.
     * @param key T.
     * @param value S.
     */
    void put(T key, S value);
    /**
     * Retrieve S value.
     * @param key T.
     * @return vector of S values.
     */
    std::vector<S> get(T key);
    /**
     * Retrieve T key.
     * @param value S.
     * @return vector of T keys.
     */
    std::vector<T> get_reverse(S key);
    /**
     * Retrieve all T keys.
     * @return vector of T keys.
     */
    std::vector<T> get_all_keys();
    /**
     * Retrieve all S values.
     * @return vector of S values.
     */
    std::vector<S> get_all_values();
    /**
     * Check if Bank is empty.
     * @return true if empty.
     */
    bool empty();
    /**
     * Create a deep-copy of bank.
     * @return unordered_map<T, std::vector<S>>.
     */
    std::unordered_map<T, std::vector<S>> copy();
    /**
     * Check if key-value pair exists.
     * @param key T.
     * @param value S.
     * @return true if exists.
     */
    bool check_relationship(T key, S value);
    
protected:
    std::unordered_map<T, std::vector<S>> bank;
    std::unordered_map<S, std::vector<T>> reverse_bank;

};

#endif //AUTOTESTER_BANK_H
