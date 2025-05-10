#include <algorithm>  // std::for_each
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// 打印键值对
void printPair(const pair<string, int>& element) {
    cout << "Student: " << element.first << ", Grade: " << element.second
         << endl;
}

int main() {
    // 创建一个包含一些学生成绩的map
    map<string, int> grades = {
        {"Alice", 92}, {"Bob", 85}, {"Charlie", 76}, {"David", 91}};

    // 使用std::for_each和lambda表达式打印所有成绩
    cout << "Grades printed using for_each and lambda:" << endl;
    for_each(grades.begin(), grades.end(),
             [](const pair<string, int>& element) {
                 cout << "Student: " << element.first
                      << ", Grade: " << element.second << endl;
             });

    cout << "\nGrades printed using a function:" << endl;
    // 使用普通函数打印所有成绩
    for_each(grades.begin(), grades.end(), printPair);

    // 使用vector存储学生的姓名
    vector<string> names;
    for (const auto& pair : grades) {
        names.push_back(pair.first);
    }

    // 打印vector中的名字
    cout << "\nNames stored in vector:" << endl;
    for (const string& name : names) {
        cout << name << endl;
    }

    // 使用list存储一些额外的信息
    list<int> extraInfo = {10, 20, 30};
    cout << "\nExtra info stored in list:" << endl;
    for (int value : extraInfo) {
        cout << value << endl;
    }

    return 0;
}