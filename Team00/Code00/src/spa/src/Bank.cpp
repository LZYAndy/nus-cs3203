#include "Bank.h"

template<class T, class S>
Bank<T, S>::Bank()
{
}

template<class T, class S>
void Bank<T, S>::put(T key, S value)
{

    if (bank.find(key) != bank.end())
    {
        std::vector<S> bank_value = bank.at(key);
        bank_value.push_back(value);
    }
    else
    {
        std::vector<S> value_list;
        value_list.push_back(value);
        bank.insert({key, value_list});
    }

    if (reverse_bank.find(value) != reverse_bank.end())
    {
        std::vector<T> reverse_bank_value = reverse_bank.at(key);
        reverse_bank_value.push_back(key);
    }
    else
    {
        std::vector<T> key_list;
        key_list.push_back(key);
        bank.insert({value, key_list});
    }
}

template<class T, class S>
std::vector<S> Bank<T, S>::get(int key)
{
    if (bank.find(key) != bank.end())
    {
        return bank[key];
    }

    return std::vector<S>();
}

template<class T, class S>
std::vector<T> Bank<T, S>::get_reverse(int key)
{
    if (reverse_bank.find(key) != reverse_bank.end())
    {
        return reverse_bank[key];
    }

    return std::vector<T>();
}