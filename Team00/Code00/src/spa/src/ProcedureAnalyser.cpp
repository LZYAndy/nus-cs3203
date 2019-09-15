#include "ProcedureAnalyser.h"

std::regex proc_name_pattern("\\s*procedure\\s+([a-zA-Z][a-zA-Z0-9]*\\s*){");

ProcedureAnalyser::ProcedureAnalyser(std::string raw)
{
    // This constructor will create an instance of ProcedureAnalyser
    // by taking a string as an input.
    raw_data = raw;
}

// This method will find all the procedures.
std::vector<Procedure> ProcedureAnalyser::analyse()
{
    auto words_begin = std::sregex_iterator(
            raw_data.begin(),
            raw_data.end(),
            proc_name_pattern);
    auto words_end = std::sregex_iterator();

    int number_of_proc = distance(words_begin, words_end);
    std::vector<int> positions_of_proc;
    std::vector<string> list_of_statement;
    std::vector<Procedure> list_of_proc;

    for (sregex_iterator k = words_begin;k != words_end;++k)
    {
        smatch match = *k;
        std::string match_str = match.str();
        positions_of_proc.push_back(match.position(0));
    }

    // For now, we found all the position index of all the procedures.

    for (int i = 0;i < number_of_proc;i++)
    {
        if (i == number_of_proc - 1)
        {
            list_of_proc.push_back(parse_procedure(raw_data.substr(positions_of_proc.at(i))));
        }
        else
        {
            int this_position = positions_of_proc.at(i);
            int next_position = positions_of_proc.at(i + 1);
            list_of_proc.push_back(parse_procedure(raw_data.substr(this_position, next_position - this_position)));
        }
    }

    return list_of_proc;
}

Procedure ProcedureAnalyser::parse_procedure(std::string proc_string)
{
    proc_string = trim_left(proc_string);
    // now proc_string starts with "procedure"
    proc_string = proc_string.substr(9);
    proc_string = trim_left(proc_string);
    // now proc_string starts with name
    std::string name = "";
    while (true)
    {
        std::string this_pos = proc_string.substr(0,1);
        if (this_pos.compare(" ") == 0) {
            break;
        }
        else
        {
            proc_string = proc_string.substr(1);
            name.append(this_pos);
            continue;
        }
    }
    proc_string = trim_left(proc_string);
    // now proc_string starts with {
    proc_string = proc_string.substr(1);
    std::string reverse_str = proc_string;
    std::reverse(reverse_str.begin(), reverse_str.end());
    reverse_str = trim_left(reverse_str);
    reverse_str = reverse_str.substr(1);
    std::reverse(reverse_str.begin(), reverse_str.end());
    proc_string = reverse_str;
    Procedure result = Procedure(name, proc_string);
    return result;
}

std::string ProcedureAnalyser::trim_left(std::string proc_string)
{
    while (true)
    {
        std::string this_pos = proc_string.substr(0,1);
        if (this_pos.compare(" ") == 0)
        {
            proc_string = proc_string.substr(1);
            continue;
        }
        else
        {
            return proc_string;
        }
    }
}
