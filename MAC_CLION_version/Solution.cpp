//
// Created by Jingcheng Lu on 12/3/17.
//

#include "Solution.h"


using namespace std;

void Solution::execute_line(int &exe_line_num, bool &is_end) {
    //get a line from vect_lines depends on exe_line_num
    string instr = this->vect_lines[exe_line_num];
    exe_line_num++;
    //print instruction
    cout << instr << endl;
    //3 conditions
    stringstream instr_stream(instr);
    string temp;
//    char *instr_char;
//    strcpy(instr_char, instr.c_str());
    getline(instr_stream, temp, ' ');
//    temp = strtok(instr_char, " ");
    //1: the first string is end
    if (!temp.compare("end")) {
        is_end = true;
        return;
    }
    //2: the first string is label
    if (!temp.substr(0, temp.length() - 1).compare("label")) {
//        label_map.insert(pair<string, int>(temp, exe_line_num));
        getline(instr_stream, temp, ' ');
//        temp = strtok(NULL, " ");
    }

    //3: the first string is instruction name: add/addi/b
    int case_id = string2enum_map.at(temp);

    string data_string[3];
    int i = 0;

    getline(instr_stream, temp, ',');
    while (i < 3 && !temp.empty()) {

        data_string[i] = temp;
        i++;
        getline(instr_stream, temp, ',');
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

void Solution::if_line(int exe_line_nums[3], int if_return_value[4]) {
    //get a line from vect_lines depends on exe_line_num
    string instr = this->vect_lines[exe_line_nums[0]];
    exe_line_nums[1] = exe_line_nums[0];

    //3 conditions
    stringstream instr_stream(instr);
    string temp;
    getline(instr_stream, temp, ' ');

    //1: the first string is end
    if (!temp.compare("end")) {
        if_return_value[0] = END;
        return;
    }

    //2: the first string is label
    if (!temp.substr(0, temp.length() - 1).compare("label")) {
        getline(instr_stream, temp, ' ');
    }

    //3: the first string is instruction name: add/addi/b
    int case_id = string2enum_map.at(temp);
    if_return_value[0] = case_id;
    string data_string[3];
    int i = 0;

    getline(instr_stream, temp, ',');
    while (i < 3 && !temp.empty()) {
        data_string[i] = temp;
        i++;
        getline(instr_stream, temp, ',');
    }
    if (case_id < B) {
        if_return_value[1] = data_string[0].c_str()[1] - '0';
        if_return_value[2] = data_string[1].c_str()[1] - '0';
        if (case_id == ADDI) {
            if_return_value[3] = stoi(data_string[2]);
        } else {
            if_return_value[3] = data_string[2].c_str()[1] - '0';
        }
        // not branch
        exe_line_nums[0]++;
    } else if (case_id == B) {
        if_return_value[1] = label_map[data_string[0]];
        //stall
        exe_line_nums[0] = -1;
        return;
    } else {
        if_return_value[2] = data_string[0].c_str()[1] - '0';
        if_return_value[3] = data_string[1].c_str()[1] - '0';
        if_return_value[1] = label_map[data_string[2]];
        //stall
        exe_line_nums[0] = -1;
    }

}

void Solution::exe_line(int exe_line_nums[3], bool &is_end, int &exe_return_values, int if_return_value[4]) {
    exe_return_values = if_return_value[0];
    if (if_return_value[0] == END) {
        is_end = true;
        exe_line_nums[0] = -1;
        cout << this->vect_lines.at(exe_line_nums[1]) << endl;
        return;
    }
    exe_line_nums[2] = exe_line_nums[1];
    switch (if_return_value[0]) {
        case ADD:
            t_vars->at(if_return_value[1]) = t_vars->at(if_return_value[2]) + t_vars->at(if_return_value[3]);
            break;
        case ADDI:
            t_vars->at(if_return_value[1]) = t_vars->at(if_return_value[2]) + if_return_value[3];
            break;
        case SUB:
            t_vars->at(if_return_value[1]) = t_vars->at(if_return_value[2]) - t_vars->at(if_return_value[3]);
            break;
        case MUL:
            t_vars->at(if_return_value[1]) = t_vars->at(if_return_value[2]) * t_vars->at(if_return_value[3]);
            break;
        case DIV:
            t_vars->at(if_return_value[1]) = t_vars->at(if_return_value[2]) / t_vars->at(if_return_value[3]);
            break;
        case B:
            exe_line_nums[0] = -if_return_value[1];
            break;
        case BEQ:
            if (t_vars->at(if_return_value[2]) == t_vars->at(if_return_value[3])) {
                exe_line_nums[0] = -if_return_value[1];
            } else {
                exe_line_nums[0] = -(exe_line_nums[1] + 1);
            }
            break;
        case BNQ:
            if (t_vars->at(if_return_value[2]) != t_vars->at(if_return_value[3])) {
                exe_line_nums[0] = -if_return_value[1];
            } else {
                exe_line_nums[0] = -(exe_line_nums[1] + 1);
            }
            break;
        default:
            cout << "error occurs at " << exe_line_nums[1] << endl;
    }
    if (if_return_value[0] >= B) {
        cout << this->vect_lines.at(exe_line_nums[1]) << endl;
        this->print_t_vars();
        this->print_clck();
    }
}

void Solution::wb_line(int exe_line_nums[3], int exe_return_values) {

    if (exe_return_values < B) {
        cout << this->vect_lines.at(exe_line_nums[2]) << endl;
        this->print_t_vars();
        this->print_clck();
    } else {
        //suppose do nothing! but should reverse if line number in this case
        exe_line_nums[0] = -exe_line_nums[0];
        exe_line_nums[1] = -1;

    }
    exe_line_nums[2] = -1;
}


vector<int> *Solution::alu() {
    this->print_clck();
    // start execute

//    bool is_end = false;
//    int exe_line_num = 0;
//    while (true) {
//        execute_line(exe_line_num, is_end);
//        if (is_end) {
//            break;
//        }
//        this->print_t_vars();
//        this->clck++;
//        this->print_clck();
//    }

    // pipeling
    bool is_end = false;
    int exe_line_nums[3] = {0, -1, -1};
    int if_return_values[4] = {-1, -1, -1, -1};
    int exe_return_values = -1;
    while (true) {
        this->dbg("Before: clock is " + to_string(this->clck));
        if (exe_line_nums[2] > -1) {
            this->dbg(to_string(exe_line_nums[2]) + "'s write back stage!");
            wb_line(exe_line_nums, exe_return_values);

        }
        if (exe_line_nums[1] > -1) {
            this->dbg(to_string(exe_line_nums[1]) + "'s execute stage!");
            exe_line(exe_line_nums, is_end, exe_return_values, if_return_values);

        }
        if (exe_line_nums[0] > -1) {
            this->dbg(to_string(exe_line_nums[0]) + "'s IF stage!");
            if_line(exe_line_nums, if_return_values);

        }
        if (is_end) {
            // all stage are down
            break;
        }
        this->clck++;
        this->dbg("After: clock is " + to_string(this->clck));
    }

    return this->t_vars;
}

Solution::Solution(ifstream &file_in, int clck_in, bool DEBUG_in) {
    this->clck = clck_in;

    this->DEBUG = DEBUG_in;
    t_vars = new vector<int>;
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
    //init label_map
    string instr;
    for (int i = 0; i < this->vect_lines.size(); i++) {
        instr = this->vect_lines.at(i);
        stringstream instr_stream(instr);
        getline(instr_stream, temp, ' ');
        if (!temp.substr(0, temp.length() - 1).compare("label")) {
            label_map.insert(pair<string, int>(temp, i));
//            this->vect_lines.at(i) = instr.substr(7,instr.size()-6);
        }
    }
    this->print_t_vars();
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

int Solution::mips_clock() {
    chrono::milliseconds timespan(clck);

    this_thread::sleep_for(timespan);
    static int cycle = 0;
    if (cycle == 0)
        cycle = 1;
    else
        cycle = 0;
    return cycle;
}

void Solution::print_t_vars() {
    int i = 0;
    for (; i < this->t_vars->size() - 1; i++) {
        cout << this->t_vars->at(i) << ",";
    }
    cout << this->t_vars->at(i) << endl;
}

void Solution::print_clck() {
    cout << this->clck << endl;
}

Solution::~Solution() {
//    if (t_vars != NULL){
//        delete t_vars;
//        cout<<"delete t_vars"<<endl;
//    }

}

void Solution::dbg(const string &msg) {
    if (this->DEBUG)
        cout << msg << endl;
}