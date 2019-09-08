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
        std::vector<T> reverse_bank_value = reverse_bank.at(value);
        reverse_bank_value.push_back(key);
    }
    else
    {
        std::vector<T> key_list;
        key_list.push_back(key);
        reverse_bank.insert({value, key_list});
    }
}

template<class T, class S>
std::vector<S> Bank<T, S>::get(T key)
{
    if (bank.find(key) != bank.end())
    {
        return bank[key];
    }

    return std::vector<S>();
}

template<class T, class S>
std::vector<T> Bank<T, S>::get_reverse(S key)
{
    if (reverse_bank.find(key) != reverse_bank.end())
    {
        return reverse_bank[key];
    }

    return std::vector<T>();
}

template<class T, class S>
std::vector<T> Bank<T,S>::get_all_keys()
{
    std::vector<T> keys;
    for (std::pair<T,std::vector<S>> element : bank)
    {
        keys.push_back(element.first);
    }

    return keys;
}

template<class T, class S>
std::vector<S> Bank<T,S>::get_all_values()
{
    std::vector<S> values;
    for (std::pair<S,std::vector<T>> element : reverse_bank)
    {
        values.push_back(element.first);
    }

    return values;
}

template class Bank<int, int>;
template class Bank<int, std::string>;
