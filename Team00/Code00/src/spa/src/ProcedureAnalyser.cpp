#include "ProcedureAnalyser.h"

regex proc_name_pattern("\\s*procedure\\s+([a-zA-Z][a-zA-Z0-9]*\\s*){");

ProcedureAnalyser::ProcedureAnalyser(string raw) {
    // This constructor will create an instance of ProcedureAnalyser
    // by taking a string as an input.
    rawData = raw;
}

// This method will find all the procedures.
vector<string> ProcedureAnalyser::analyse() {
    auto words_begin = sregex_iterator(
            rawData.begin(),
            rawData.end(),
            proc_name_pattern);
    auto words_end = sregex_iterator();

    int number_of_proc = distance(words_begin, words_end);
    vector<int> positions_of_proc;
    vector<string> list_of_statement;
    vector<Procedure> list_of_proc;

    for (sregex_iterator k = words_begin;k != words_end;++k) {
        smatch match = *k;
        string match_str = match.str();
        positions_of_proc.push_back(match.position(0));
    }

    // For now, we found all the position index of all the procedures.

    for (int i = 0;i < number_of_proc;i++) {
        if (i == number_of_proc - 1) {
            list_of_proc.push_back(parse_procedure(rawData.substr(positions_of_proc.at(i))));
        } else {
            int this_position = positions_of_proc.at(i);
            int next_position = positions_of_proc.at(i + 1);
            list_of_proc.push_back(parse_procedure(rawData.substr(this_position, next_position - this_position)));
        }
    }
}

Procedure ProcedureAnalyser::parse_procedure(string proc_string) {
    proc_string = trim_left(proc_string);
    // now proc_string starts with "procedure"
    proc_string = proc_string.substr(9);
    proc_string = trim_left(proc_string);
    // now proc_string starts with name
    string name = "";
    while (true) {
        string this_pos = proc_string.substr(0,1);
        if (this_pos.compare(" ") == 0) {
            break;
        } else {
            proc_string = proc_string.substr(1);
            name.append(this_pos);
            continue;
        }
    }
    proc_string = trim_left(proc_string);
    // now proc_string starts with {
    proc_string = proc_string.substr(1);
    string reverse_str = proc_string;
    reverse(reverse_str.begin(), reverse_str.end());
    reverse_str = trim_left(reverse_str);
    reverse_str = reverse_str.substr(1);
    reverse(reverse_str.begin(), reverse_str.end());
    proc_string = reverse_str;
    Procedure result = Procedure(name, proc_string);
    return result;
}

string ProcedureAnalyser::trim_left(string proc_string) {
    while (true) {
        string this_pos = proc_string.substr(0,1);
        if (this_pos.compare(" ") == 0) {
            proc_string = proc_string.substr(1);
            continue;
        } else {
            return proc_string;
        }
    }
}
