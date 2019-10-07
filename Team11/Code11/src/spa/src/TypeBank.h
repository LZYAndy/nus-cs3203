#ifndef AUTOTESTER_TYPEBANK_H
#define AUTOTESTER_TYPEBANK_H

#include <unordered_map>

#include "pql_dto/Entity.h"

class TypeBank
{
public:
    /**
     * Insert Type relationship to TypeBank.
     * @param stmt1 stmt# of statement.
     * @param type type of statement.
     * @return true if the insert process is successful.
     */
    bool insert_type(int stmt, EntityType type);
    /**
     * Get statement type.
     * @param stmt# of statement to be queried.
     * @return statement type.
     */
    EntityType get_statement_type(int stmt);
    /**
     * Get stmt# of all EntityType statements in PKB.
     * @param type EntityType to retrieve
     * @return vector containing all the stmt# of EntityType statements.
     */
    std::vector<int> get_all_of_type(EntityType type);
    /**
     * Get all Types relationship that exists in TypeBanl.
     * @return unordered_map containing all Type relationship that exists in TypeBank
     */
    std::unordered_map<int, std::vector<EntityType>> copy();

private:
    std::unordered_map<int, std::vector<EntityType>> bank;
    std::unordered_map<EntityType, std::vector<int>, EnumClassHash> reverse_bank;
};


#endif //AUTOTESTER_TYPEBANK_H
