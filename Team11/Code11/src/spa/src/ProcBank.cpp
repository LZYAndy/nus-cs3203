#include "ProcBank.h"

bool ProcBank::insert_procedure(std::string name, int first_prog, std::vector<int> last_progs)
{
    if (!first_line_bank.get(name).empty())
    {
        return false;
    }
    if (!first_line_bank.get_reverse(first_prog).empty())
    {
        if (first_line_bank.get_reverse(first_prog)[0].compare(name) != 0)
        {
            return false;
        }
    }
    first_line_bank.put(name, first_prog);
    for (int prog_line: last_progs)
    {
        last_lines_bank.put(name, prog_line);
    }
    return true;
}

std::vector<std::string> ProcBank::get_all_procedures()
{
    return first_line_bank.get_all_keys();
}

int ProcBank::get_procedure_first_line(std::string procedure)
{
    auto result = first_line_bank.get(procedure);
    if (result.size() != 1)
    {
        return -1;
    }
    return result.back();
}

std::vector<int> ProcBank::get_procedure_last_lines(std::string procedure)
{
    return last_lines_bank.get(procedure);
}
