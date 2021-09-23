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

    return 0;
}
