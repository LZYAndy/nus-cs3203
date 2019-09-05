#ifndef AUTOTESTER_BANK_H
#define AUTOTESTER_BANK_H

#include <unordered_map>
#include <vector>

template<class T, class S>
class Bank
{
public:
    Bank<T, S>();
    void put(T key, S value);
    std::vector<S> get(int key);
    std::vector<T> get_reverse(int key);

private:
    std::unordered_map<T, std::vector<S>> bank;
    std::unordered_map<S, std::vector<T>> reverse_bank;

};

#endif //AUTOTESTER_BANK_H
