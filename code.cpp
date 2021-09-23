#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const string keyword[32] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                            "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
                            "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
                            "void", "volatile", "while"};

int main() {
    string s;
    int count_key = 0;
    int count_switch = 0;
    int count_ifelse = 0;
    vector<string> data;
    vector<int> count_case;
    ifstream file;
    file.open(R"(D:\C++\software\lab2\testfile.cpp)");//First pass in the address directly
    while (file >> s) {
        data.push_back(s);
    }
    file.close();

    for (int i = 0; i < data.size(); ++i) {
        vector<int> pos;
        for (int j = 0; j < 32; ++j) {
            int position = data[i].find(keyword[j]);
            if (position != data[i].npos) {
                if (find(pos.begin(), pos.end(), position) == pos.end()) {
                    pos.push_back(position);
                    count_key++;
                }
            }
        }
    }
    cout << count_key << endl;
    /***Level 2 implement draft***/
    //switch count
    for (int i = 0; i < data.size(); ++i) {
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            count_switch++;
        }
    }
    cout << count_switch << endl;

    //case count
    for (int i = 0; i < data.size(); ++i) {
        int case_num = 0;
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            for (int j = i + 1; j < data.size(); ++j) {
                int position2 = data[j].find("case");
                if (position2 != data[j].npos) {
                    case_num++;
                }
                //Use finding "default" as a switch termination condition instead of next "switch".
                position2 = data[j].find("default");
                if (position2 != data[j].npos) {
                    count_case.push_back(case_num);
                    i = j + 1;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < count_case.size(); ++i) {
        cout << count_case[i] << " ";
    }
    //Level 3 implementation
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].find("else") != data[i].npos && data[i+1].find("if") == data[i+1].npos||data[i].find("else{")!=data[i].npos){
            count_ifelse++;
        }
    }
    cout << endl << count_ifelse << endl;
    return 0;
}
