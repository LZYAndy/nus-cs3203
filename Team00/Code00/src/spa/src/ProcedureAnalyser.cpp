#include "ProcedureAnalyser.h"

ProcedureAnalyser::ProcedureAnalyser(std::string raw)
{
    // This constructor will create an instance of ProcedureAnalyser
    // by taking a string as an input.
    raw_data = raw;
}

// This method will find all the procedures.
std::vector<Procedure> ProcedureAnalyser::analyse()
{
    std::vector<int> positions_of_proc;
    positions_of_proc.push_back(0);
    std::string source = raw_data;
    int number_of_proc = 0;
    source = StringUtil::trim_left(source);
    std::vector<std::string> list_of_statement;
    std::vector<Procedure> list_of_proc;

    try
    {
        while (source != "")
        {
            source = StringUtil::trim_left(source);
            std::string check = source.substr(0, 9);
            if (check != "procedure")
            {
                throw "Invalid procedure!";
            }

            source = source.substr(9);
            source = StringUtil::trim_left(source);

            std::string proc_name = "";
            while (source.substr(0, 1) != " " && source.substr(0, 1) != "{")
            {
                proc_name = proc_name + source.substr(0, 1);
                source = source.substr(1);
            }
            source = StringUtil::trim_left(source);

            int ending = find_bracket(source, "{", "}");
            std::string proc_body = source.substr(1, ending - 2);
            source = source.substr(ending);
            source = StringUtil::trim_left(source);
            number_of_proc++;
            list_of_proc.push_back(Procedure(proc_name, proc_body));
        }

        // For now, we found all the position index of all the procedures.

//        for (int i = 0;i < number_of_proc;i++)
//        {
//            if (i == number_of_proc - 1)
//            {
//                list_of_proc.push_back(parse_procedure(raw_data.substr(positions_of_proc.at(i))));
//            }
//            else
//            {
//                int this_position = positions_of_proc.at(i);
//                int next_position = positions_of_proc.at(i + 1);
//                std::cout << this_position;
//                std::cout << next_position;
//                list_of_proc.push_back(parse_procedure(raw_data.substr(this_position, next_position - this_position)));
//            }
//        }

        return list_of_proc;
    }
    catch(const char* excep)
    {
        throw std::runtime_error(error_messages::invalid_SIMPLE);
    }
}

//Procedure ProcedureAnalyser::parse_procedure(std::string proc_string)
//{
//    proc_string = trim_left(proc_string);
//    // now proc_string starts with "procedure"
//    proc_string = proc_string.substr(9);
//    proc_string = trim_left(proc_string);
//    // now proc_string starts with name
//    std::string name = "";
//    while (true)
//    {
//        std::string this_pos = proc_string.substr(0,1);
//        if (this_pos.compare(" ") == 0) {
//            break;
//        }
//        else
//        {
//            proc_string = proc_string.substr(1);
//            name.append(this_pos);
//            continue;
//        }
//    }
//    proc_string = trim_left(proc_string);
//    // now proc_string starts with {
//    proc_string = proc_string.substr(1);
//    std::string reverse_str = proc_string;
//    std::reverse(reverse_str.begin(), reverse_str.end());
//    reverse_str = trim_left(reverse_str);
//    reverse_str = reverse_str.substr(1);
//    std::reverse(reverse_str.begin(), reverse_str.end());
//    proc_string = reverse_str;
//    Procedure result = Procedure(name, proc_string);
//    return result;
//}

//std::string ProcedureAnalyser::trim_left(std::string proc_string)
//{
//    while (true)
//    {
//        std::string this_pos = proc_string.substr(0,1);
//        if (this_pos.compare(" ") == 0)
//        {
//            proc_string = proc_string.substr(1);
//            continue;
//        }
//        else
//        {
//            return proc_string;
//        }
//    }
//}

int ProcedureAnalyser::find_bracket(std::string src, std::string opening, std::string closing)
{
    // First step: remove the opening bracket
    bool done = false;
    int count = 0;
    int index = 0;

    while (!done)
    {
        if (src == "")
        {
            throw std::runtime_error(error_messages::invalid_SIMPLE);
        }
        std::string this_pos = src.substr(0, 1);
        if (this_pos == opening)
        {
            count = count + 1;
        }
        else if (this_pos == closing)
        {
            count = count - 1;
            if (count == 0)
            {
                break;
            }
        }
        src = src.substr(1);
        index = index + 1;
    }
    return index + 1;
}
