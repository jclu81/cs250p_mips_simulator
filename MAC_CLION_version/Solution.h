#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

using namespace std;

class Solution {

private:

    bool DEBUG;
    int clck;
    int cycle_number;
    vector<string> vect_lines;
    vector<int> *t_vars;
    unordered_map<string, int> label_map;
    enum op {
        ADD,
        ADDI,
        SUB,
        MUL,
        DIV,
        B,
        BEQ,
        BNQ,
        END,
    };
    const unordered_map<string, int> string2enum_map = {
            {"add",  ADD},
            {"addi", ADDI},
            {"sub",  SUB},
            {"mul",  MUL},
            {"div",  DIV},
            {"b",    B},
            {"beq",  BEQ},
            {"bnq",  BNQ},
            {"end",  END}
    };

public :

    Solution(ifstream &file_in, int clck_in = 10, bool DEBUG_in = false);

    void dbg(const string &msg);

    vector<int> *alu();

    int mips_clock();

    void execute_line(int &exe_line_num, bool &is_end);

    void if_line(int exe_line_nums[3], int if_return_value[4]);

    void exe_line(int exe_line_nums[3], bool &is_end, int &exe_return_values, int if_return_value[4]);

    void wb_line(int exe_line_nums[3], int case_id);

    void print_t_vars();

    void print_cycle_number();

    void print_string(const string &msg);

    ~Solution();

};
