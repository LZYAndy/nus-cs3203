#include "TypeBank.h"

void TypeBank::insert_type(int stmt, EntityType type)
{
    if (bank.find(stmt) != bank.end())
    {
        std::vector<EntityType> bank_value = bank.at(stmt);
        bank_value.push_back(type);
    }
    else
    {
        std::vector<EntityType> value_list;
        value_list.push_back(type);
        bank.insert({stmt, value_list});
    }

    if (reverse_bank.find(type) != reverse_bank.end())
    {
        std::vector<int> reverse_bank_value = reverse_bank.at(type);
        reverse_bank_value.push_back(stmt);
    }
    else
    {
        std::vector<int> key_list;
        key_list.push_back(stmt);
        reverse_bank.insert({type, key_list});
    }
}

std::vector<EntityType> TypeBank::get_statement_type(int stmt)
{
    if (bank.find(stmt) != bank.end())
    {
        return bank[stmt];
    }
    return std::vector<EntityType>();
}

std::vector<int> TypeBank::get_all_of_type(EntityType type)
{
    if (reverse_bank.find(type) != reverse_bank.end())
    {
        return reverse_bank[type];
    }

    return std::vector<int>();
}

std::unordered_map<int, std::vector<EntityType>> TypeBank::copy()
{
    return bank;
}

