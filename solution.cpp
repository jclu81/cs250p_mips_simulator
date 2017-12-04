#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>

using namespace std;

class solution {

private:

    bool DEBUG;
    int clck;
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

    solution(ifstream &file_in, int clck_in = 10, bool DEBUG_in = false);

    void dbg(const string &msg);

    vector<int> *alu();

    int mips_clock();

    void execute_line(int &exe_line_num, bool &is_end);

    void print_t_vars();

};


void solution::execute_line(int &exe_line_num, bool &is_end) {
    //get a line from vect_lines depends on exe_line_num
    string instr = this->vect_lines[exe_line_num];
    //print instruction
    cout << instr << endl;
    //3 conditions
    stringstream instr_stream(instr);
    string temp;
    getline(instr_stream, temp, ' ');
    //1: the first string is end
    if (temp.compare("end")) {
        is_end = true;
        return;
    }
    //2: the first string is label
    if (temp.substr(0, temp.length() - 1).compare("label")) {
        label_map.insert(pair<string, int>(temp, exe_line_num));
        getline(instr_stream, temp, ' ');
    }
    //3: the first string is instruction name: add/addi/b
    int case_id = string2enum_map.at(temp);

    string data_string[3];
    int i = 0;
    while (i < 3 && getline(instr_stream, temp, ',')) {
        data_string[i] = temp;
        i++;
    }
    int obj;
    int s1;
    int s2;
    if (case_id < B) {
        obj = data_string[0].c_str()[1] - '0';
        s1 = data_string[1].c_str()[1] - '0';
        if (case_id == ADDI) {
            s2 = stoi(data_string[2]);
        } else {
            s2 = data_string[2].c_str()[1] - '0';
        }
    } else if (case_id == B) {
        obj = label_map[data_string[0]];
        exe_line_num = obj;
        return;
    } else {
        s1 = data_string[0].c_str()[1] - '0';
        s2 = data_string[1].c_str()[1] - '0';
        obj = label_map[data_string[2]];
    }
    switch (case_id) {
        case ADD:
            t_vars->at(obj) = t_vars->at(s1) + t_vars->at(s2);
            break;
        case ADDI:
            t_vars->at(obj) = t_vars->at(s1) + s2;
            break;
        case SUB:
            t_vars->at(obj) = t_vars->at(s1) - t_vars->at(s2);
            break;
        case MUL:
            t_vars->at(obj) = t_vars->at(s1) * t_vars->at(s2);
            break;
        case DIV:
            t_vars->at(obj) = t_vars->at(s1) / t_vars->at(s2);
            break;
        case BEQ:
            if (t_vars->at(s1) == t_vars->at(s2)) {
                exe_line_num = obj;
            }
            break;
        case BNQ:
            if (t_vars->at(s1) != t_vars->at(s2)) {
                exe_line_num = obj;
            }
            break;
        default:
            cout << "error occurs at " << exe_line_num << endl;
    }
    return;
}

vector<int> *solution::alu() {
    bool is_end = false;
    int exe_line_num = 0;
    while (!is_end) {
        if (exe_line_num < this->vect_lines.size() - 1) {
            execute_line(exe_line_num, is_end);
            this->print_t_vars();
        } else {
            // end
            break;
//            is_end = true;
        }

    }
    return this->t_vars;
}

solution::solution(ifstream &file_in, int clck_in, bool DEBUG_in) {
    this->clck = clck_in;
    this->DEBUG = DEBUG_in;
    string temp;
    getline(file_in, temp);
    // read from string to vector<int> to init t_vars
    stringstream string_line(temp);
    while (getline(string_line, temp, ',')) {
        t_vars->push_back(stoi(temp));
    }
    //init vect_lines
    while (getline(file_in, temp)) {
        vect_lines.push_back(temp);
    }

    //init string2enum_map
//    string2enum_map.insert(pair<string,op>("add",ADD));
//    string2enum_map.insert(pair<string,op>("addi",ADDI));
//    string2enum_map.insert(pair<string,op>("sub",SUB));
//    string2enum_map.insert(pair<string,op>("mul",MUL));
//    string2enum_map.insert(pair<string,op>("div",DIV));
//    string2enum_map.insert(pair<string,op>("b",B));
//    string2enum_map.insert(pair<string,op>("beq",BEQ));
//    string2enum_map.insert(pair<string,op>("bnq",BNQ));
//    string2enum_map.insert(pair<string,op>("end",END));
}

int solution::mips_clock() {
    chrono::milliseconds timespan(clck);

    this_thread::sleep_for(timespan);
    static int cycle = 0;
    if (cycle == 0)
        cycle = 1;
    else
        cycle = 0;
    return cycle;
}

void solution::print_t_vars() {
    int i = 0;
    for (; i < this->t_vars->size() - 1; i++) {
        cout << this->t_vars->at(i) << ",";
    }
    cout << this->t_vars->at(i) << endl;
}