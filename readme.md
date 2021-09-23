| The Link Your Class                        | [EE308 MIEC社区-EE308 MIEC论坛-CSDN社区云](https://bbs.csdn.net/forums/MUEE308FZ) |
| ------------------------------------------ | ------------------------------------------------------------ |
| The Link of Requirement of This Assignment | [LAB 2 Individual programing work (EE308 IEC MU 2021 Fall)-CSDN社区](https://bbs.csdn.net/topics/600798588) |
| The Aim of This Assignment                 | Implement a program function that can read in C or C++ code files for different levels of keyword extraction. |
| MU STU ID and FZU STU ID                   | 19103743_831901303                                           |



#### ✔GitHub-Link: [sjky/EE308_Lab2 (github.com)](https://github.com/sjky/EE308_Lab2)



### 1.PSP

| **Personal Software Process Stages**                 | **Estimated time(min）** | **Time(min）** |
| :--------------------------------------------------- | :----------------------- | :------------- |
| **1.Planning**                                       | -                        | -              |
| Estimate                                             | 20                       | 20             |
| **2.Development**                                    | -                        | -              |
| Analysis                                             | 60                       | 200            |
| Design Spec                                          | 30                       | 15             |
| Design Review                                        | 20                       | 20             |
| Coding Standard                                      | 30                       | 40             |
| Design                                               | 40                       | 60             |
| Coding                                               | 300                      | 350            |
| Code Review                                          | 60                       | 70             |
| Test                                                 | 100                      | 120            |
| **3.Report**                                         | -                        | -              |
| Test Report                                          | 20                       | 30             |
| Postmortem & Process Improvement Plan· Design Review | 50                       | 60             |
| Summary                                              | 730                      | 985            |



### 2.Description of problem-solving ideas

#### •The first thought

**When I first saw this question I had three thoughts in my mind**

1. I should use C++ (because I just learn it last semester) to read the test sample and extract the keywords one by one, separated by newlines and empty spaces.
2. How to find the keywords in the extracted elements?
3. I realized that the key important thing is to distinguish between "if-else" structure and "if-else if-else" structure, especially if they are nested within each other. ⁉

#### •Quick thinking solutions

![image-20210923221717472](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923221717472.png)

As you can see, this block diagram represents my three steps to solve the problem from "shallow to deep". However, the third block diagram shows that I haven't figured out how to recognize "if-else" structure and "if-else if-else" structure at the first time. **The good thing is I think I find a "nice way" to solve the last problem, you can see what I have done in next part!** 😁



### 3.Design and implementation process.

#### 3.1 processing data

Use "ifstream" in C++ to read the data from specific and output it into a variable length array "data". Then, we can get each word separated by newlines and empty spaces, which is easy for the rest of operation.

#### **3.2 flow chart of each level**

#### level 1:

<img src="C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923225928178.png" alt="image-20210923225928178" style="zoom: 67%;" >



#### level 2:

<img src="C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923231043714.png" alt="image-20210923231043714" style="zoom:67%;" />

#### level 3:

**I should explain here, "single else" means "else" like this ![image-20210923232341595](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923232341595.png) not "else if", only "else".**

<img src="C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923231505419.png" alt="image-20210923231505419" style="zoom:67%;" />



#### level 4:

**I should explain here, "single if" means "if" like this ![image-20210923232618615](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923232618615.png)not "else if", only "if".**

![image-20210923232243271](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923232243271.png)



### 4.Code description

**•code to process data**

In this part I broke the file into many elements like![image-20210923233726224](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923233726224.png)each line is an element and I store them in a vector.

```c++
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
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
    return 0;
}
```

**•code for level 1**

I do not post the "keyword" array here but I really did it! I use nested "for" loops here to check whether the element in the data array contain keyword  or not. 

```c++
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
```

**•code for level 2**

As I said in previous part, if I find "switch" in the element of data array, the code will keep looking the "case" until it finds "default". Then, a complete switch structure (include switch 1 and its cases) is counted. Next, it will find the next switch structure until the end.

```c++
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
```

**•code for level 3**

The condition in if is used to find the single "else"(not else-if) in the sample code.

```c++
//Mode3 will output the number of "if else" structures
void Mode3(vector<string> data) {
    int count_if_else = 0;
    for (int i = 0; i < data.size(); ++i) {
        //The condition in if is used to find the single "else"(not else-if) in the sample
        if (data[i].find("else") != data[i].npos && data[i + 1].find("if") == data[i + 1].npos ||
            data[i].find("else{") != data[i].npos || data[i].find("else;") != data[i].npos) {
            count_if_else++;
        }
    }
    cout << "The number of 'if_else' structure is: " << count_if_else << endl;
}
```

**•code for level 4**

The idea of this code is find a single if first, then we find the else-if structure, we treat it as a pair, and we're going to record the "if-else-if" structure once.

```c++
//Mode4 will output the number of "if, else if, else" structures.
void Mode4(vector<string> data) {
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
    cout << "The number of 'if, else if, else' structures is: " << count_if_elseif_if << endl;
}
```



### 5.unit test

#### The result

###### level 1

![image-20210923235557638](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923235557638.png)

###### level 2

![image-20210923235636245](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923235636245.png)

###### level 3

![image-20210923235716747](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923235716747.png)

###### level 4

![image-20210923235747200](C:\Users\12816\AppData\Roaming\Typora\typora-user-images\image-20210923235747200.png)



### 6.summary

I think this experiment gave me an idea of the complete process of writing an open source project, it was a new experience, which laid a solid foundation for future projects while practicing coding.



