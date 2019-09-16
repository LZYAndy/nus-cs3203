#ifndef AUTOTESTER_TYPEBANK_H
#define AUTOTESTER_TYPEBANK_H

#include <unordered_map>

#include "pql_dto/Entity.h"

struct EnumClassHash
{
    template<typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class TypeBank
{
public:
    /*
     * Insert Type for a statement into the typeBank
     * Returns false if the statement already exists
     */
    void insert_type(int stmt, EntityType type);
    EntityType get_statement_type(int stmt);
    std::vector<int> get_all_of_type(EntityType type);
    std::unordered_map<int, std::vector<EntityType>> copy();

private:
    std::unordered_map<int, std::vector<EntityType>> bank;
    std::unordered_map<EntityType, std::vector<int>, EnumClassHash> reverse_bank;
};


#endif //AUTOTESTER_TYPEBANK_H
