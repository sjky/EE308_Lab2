#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const string keyword[32] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                            "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
                            "short", "signed",
                            "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
                            "while"};

int main() {
    int countkey = 0;
    int countswi = 0;
    int countifelse = 0;
    int count_elseif = 0;
    string s;
    vector<string> data;
    vector<int> countcase;
    ifstream file;
    file.open(R"(D:\C++\software\lab2\testfile.cpp)");
    while (file >> s) {
        data.push_back(s);
        cout << s << endl;
    }
    file.close();

    for (int i = 0; i < data.size(); ++i) {
        vector<int> pos;
        for (int j = 0; j < 32; ++j) {
            int position = data[i].find(keyword[j]);
            if (position != data[i].npos) {
                if (find(pos.begin(), pos.end(), position) == pos.end()) {
                    pos.push_back(position);
                    countkey++;
                }
            }
        }
    }
    cout << countkey << endl;

    for (int i = 0; i < data.size(); ++i) {
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            countswi++;
        }
    }
    cout << countswi << endl;


    for (int i = 0; i < data.size(); ++i) {
        int casenum = 0;
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            for (int j = i + 1; j < data.size(); ++j) {
                int position2 = data[j].find("case");
                if (position2 != data[j].npos) {
                    casenum++;
                }
                position2 = data[j].find("default");
                if (position2 != data[j].npos) {
                    countcase.push_back(casenum);
                    i = j + 1;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < countcase.size(); ++i) {
        cout << countcase[i] << " ";
    }


    for (int i = 0; i < data.size(); ++i) {
        if (data[i].find("else") != data[i].npos && data[i + 1].find("if") == data[i + 1].npos ||
            data[i].find("else{") != data[i].npos || data[i].find("else;") != data[i].npos) {
            countifelse++;
        }
    }
    cout << endl << countifelse << endl;


    for (int i = 0; i < data.size(); ++i) {
        if ((data[i].find("if") != data[i].npos && data[i - 1].find("else") == data[i - 1].npos) ||
            (data[i].find("if") != data[i].npos &&
             (data[i - 1].find("else{") != data[i - 1].npos || data[i - 1].find("else;") != data[i - 1].npos))) {
            for (int j = i + 1; j < data.size(); ++j) {
                if (data[j].find("else") != data[j].npos && data[j + 1].find("if") != data[j + 1].npos &&
                    data[j].find("else{") == data[j].npos && data[j].find("else;") == data[j].npos) {
                    i = j;
                    count_elseif++;
                    break;
                }
            }
        }
    }
    cout << count_elseif;
    return 0;
}





