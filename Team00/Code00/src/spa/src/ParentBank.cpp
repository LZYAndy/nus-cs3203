#include "ParentBank.h"
bool ParentBank::is_parent(int stmt1, int stmt2)
{
    if (bank.find(stmt1) == bank.end())
    {
        return false;
    }
    else
    {
        std::vector<int> stmts = bank.at(stmt1);
        return std::any_of(stmts.begin(), stmts.end(), [stmt2](int i)
        { return i == stmt2; });
    }
}
