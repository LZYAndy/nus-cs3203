#ifndef AUTOTESTER_NEXTBIPBANK_H
#define AUTOTESTER_NEXTBIPBANK_H

#include "Bank.h"

class NextBipBank
{
public:
    bool insert_next_bip(int prev_prog, int next_prog);
    bool insert_call_ingress_egress(int ingress_prog, int egress_prog);
    bool is_next_bip(int prev_prog, int next_prog);
    bool does_next_bip_exists();
    std::vector<int>  get_next_bip(int prog_line);
    std::vector<int>  get_previous_bip(int prog_line);
    std::vector<int>  get_all_next_bip();
    std::vector<int>  get_all_previous_bip();
    std::unordered_map<int, std::vector<int>> get_all_next_bip_relationship();
    int get_egress(int ingress_prog);
    int get_ingress(int egress_prog);
    
private:
    Bank<int, int> next_bip_bank;
    Bank<int, int> ingress_egress_bank;
};

#endif