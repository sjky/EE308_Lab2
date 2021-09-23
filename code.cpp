/*
 * EE308 lab2
 * Name:Hongyu Chen
 * MU ID:19103743  FZU ID:831901303
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//Create the keyword array for convenience later
const string keyword[32] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                            "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
                            "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
                            "void", "volatile", "while"};


/*** Here we declare and define the modes we will ues in this program ***/
//Mode 1 is used to output "keyword" statistics.
void Mode1(vector<string> data) {
    int count_key = 0;
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
    cout << "The number of key word is: " << count_key << endl;
}

//Mode2 will output the number of "switch case" structures, and output the number of "case" corresponding to each group.
void Mode2(vector<string> data) {
    int count_switch = 0;
    vector<int> count_case;
    for (int i = 0; i < data.size(); ++i) {
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            count_switch++;
        }
    }
    cout << "The number of switch is:" << count_switch << endl;
    //The number of case in each switch is counted here
    for (int i = 0; i < data.size(); ++i) {
        int case_num = 0;
        int position = data[i].find("switch");
        if (position != data[i].npos) {
            for (int j = i + 1; j < data.size(); ++j) {
                int position2 = data[j].find("case");
                if (position2 != data[j].npos) {
                    case_num++;
                }
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
        cout << "The case of the " << i + 1 << " switch is: " << count_case[i] << endl;
    }
}

//Mode3 will output the number of "if else" structures
int Mode3(vector<string> data) {
    int count_if_else = 0;
    for (int i = 0; i < data.size(); ++i) {
        //The condition in if is used to find the single "else"(not else-if) in the sample
        if (data[i].find("else") != data[i].npos && data[i + 1].find("if") == data[i + 1].npos ||
            data[i].find("else{") != data[i].npos || data[i].find("else;") != data[i].npos) {
            count_if_else++;
        }
    }
    return count_if_else;
}

//Mode4 will output the number of "if, else if, else" structures.
int Mode4(vector<string> data) {
    int count_if_elseif_if = 0;
    for (int i = 0; i < data.size(); ++i) {
        //This condition is used to find the single "if" in the sample
        if ((data[i].find("if") != data[i].npos && data[i - 1].find("else") == data[i - 1].npos) ||
            (data[i].find("if") != data[i].npos &&
             (data[i - 1].find("else{") != data[i - 1].npos || data[i - 1].find("else;") != data[i - 1].npos))) {
            for (int j = i + 1; j < data.size(); ++j) {
                //This condition is used to find the "else-if" in the sample
                if (data[j].find("else") != data[j].npos && data[j + 1].find("if") != data[j + 1].npos &&
                    data[j].find("else{") == data[j].npos && data[j].find("else;") == data[j].npos) {
                    i = j;
                    count_if_elseif_if++;
                    break;
                }
            }
        }
    }
    return count_if_elseif_if;
}
/*** After define functions we run the main code here ***/
int main() {
    //Here we open the test file and put each word into a vector.
    string address;//This string is used for pass the address of your test file.
    string s;
    int level;
    vector<string> data;
    ifstream file;
    cout << "Please input the address: ";//Attention!!! File name should be consistent. ex:(testfile✔ test file×)
    cin >> address;
    file.open(address);
    while (file >> s) {
        data.push_back(s);
    }
    file.close();

    //Input the level you want to achieve
    cout << "Now, choose the level: ";
    cin >> level;
    //The four case will satisfy your requirement
    switch (level) {
        case 1:
            Mode1(data);
            break;
        case 2:
            Mode2(data);
            break;
        case 3:
            cout << "The number of 'if_else' structure is: " << Mode3(data)-Mode4(data) << endl;
            break;
        case 4:
            cout << "The number of 'if, else if, else' structures is: " << Mode4(data) << endl;
            break;
        default:
            break;
    }
    return 0;
}

