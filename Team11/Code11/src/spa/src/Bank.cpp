#include "Bank.h"


template<class T, class S>
void Bank<T, S>::put(T key, S value)
{

    if (bank.find(key) != bank.end())
    {
        std::vector<S> &bank_value = bank.at(key);
        // check if value exists already
        for (S val : bank_value)
        {
            if (value == val)
            {
                return;
            }
        }
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
        std::vector<T> &reverse_bank_value = reverse_bank.at(value);
        // check if value exists already
        for (T val : reverse_bank_value)
        {
            if (key == val)
            {
                return;
            }
        }
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

template<class T, class S>
bool Bank<T, S>::empty()
{
    return bank.empty() && reverse_bank.empty();
}

template<class T, class S>
std::unordered_map<T, std::vector<S>> Bank<T, S>::copy()
{
    // deep copy
    return bank;
}

template<class T, class S>
bool Bank<T,S>::check_relationship(T key, S value)
{
    if (bank.find(key) == bank.end())
    {
        return false;
    }
    else
    {
        std::vector<S> values = bank.at(key);
        return std::any_of(values.begin(), values.end(), [value](S i)
        {
            return i == value;
        });
    }
}

template<class T, class S>
std::unordered_map<S, std::vector<T>> Bank<T, S>::get_reverse_bank()
{
    return reverse_bank;
}

template class Bank<int, int>;
template class Bank<int, std::string>;
template class Bank<std::string, std::string>;

