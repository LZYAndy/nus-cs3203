#include "StringModification.h"

string StringModification::trim_left(string proc_string) {
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
