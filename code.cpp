#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

int main() {
    string s;
    vector<string> data;
    vector<int> countcase;
    ifstream file;
    file.open(R"(D:\C++\software\lab2\testfile.cpp)");
    while (file >> s) {
        data.push_back(s);
    }
    file.close();

    return 0;
}
