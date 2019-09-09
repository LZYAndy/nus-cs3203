#include "ParentBank.h"
bool ParentBank::is_parent(int stmt1, int stmt2)
{
    std::vector<int> stmts = bank.at(stmt1);
    if (stmts.empty())
    {
        return false;
    }
    else
    {
        return std::any_of(stmts.begin(), stmts.end(), [stmt2](int i)
        { return i == stmt2; });
    }
}
