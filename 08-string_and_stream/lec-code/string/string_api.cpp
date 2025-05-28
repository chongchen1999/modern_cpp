#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 1. 构造与基本操作
    string s1;                             // 默认构造
    string s2 = "Hello";                   // 从C字符串构造
    string s3(" World");                   // 直接构造
    string s4(5, 'x');                     // 填充构造 - "xxxxx"
    string s5(s2);                         // 拷贝构造
    string s6(s2.begin(), s2.begin() + 3); // 迭代器范围构造 - "Hel"

    cout << "s1: " << s1 << " (empty: " << s1.empty() << ")" << endl;
    cout << "s2: " << s2 << " (size: " << s2.size() << ")" << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
    cout << "s5: " << s5 << endl;
    cout << "s6: " << s6 << endl;

    // 2. 元素访问
    cout << "\nElement access:" << endl;
    cout << "s2[1]: " << s2[1] << endl;           // 'e'
    cout << "s2.at(1): " << s2.at(1) << endl;     // 'e'
    cout << "s2.front(): " << s2.front() << endl; // 'H'
    cout << "s2.back(): " << s2.back() << endl;   // 'o'

    try {
        cout << s2.at(10); // 抛出 std::out_of_range
    } catch (const out_of_range& e) {
        cout << "Caught out_of_range: " << e.what() << endl;
    }

    // 3. 修改操作
    cout << "\nModifiers:" << endl;
    s2.append(s3); // s2 = "Hello World"
    cout << "After append: " << s2 << endl;

    s2.insert(5, " C++"); // "Hello C++ World"
    cout << "After insert: " << s2 << endl;

    s2.replace(6, 3, "STL"); // "Hello STL World"
    cout << "After replace: " << s2 << endl;

    s2.erase(5, 5); // "Hello World"
    cout << "After erase: " << s2 << endl;

    s2.push_back('!'); // "Hello World!"
    cout << "After push_back: " << s2 << endl;

    s2.pop_back(); // "Hello World"
    cout << "After pop_back: " << s2 << endl;

    // 4. 字符串操作
    cout << "\nString operations:" << endl;
    cout << "Substring(6,5): " << s2.substr(6, 5) << endl;            // "World"
    cout << "Find 'World': " << s2.find("World") << endl;             // 6
    cout << "Find first of 'lo': " << s2.find_first_of("lo") << endl; // 2
    cout << "Starts with 'Hello': " << s2.starts_with("Hello") << endl; // true
    cout << "Ends with 'World': " << s2.ends_with("World") << endl;     // true
    cout << "Contains 'llo': " << (s2.find("llo") != string::npos)
         << endl; // true

    // 5. 容量管理
    cout << "\nCapacity management:" << endl;
    s2 = "Hello, the std::string, now I would like to test you!"; // 重置 s2
    cout << "Capacity: " << s2.capacity()
         << " address: " << static_cast<const void*>(s2.data()) << endl;
    s2.reserve(100);
    cout << "After reserve(100), capacity: " << s2.capacity()
         << " address: " << static_cast<const void*>(s2.data()) << endl;
    s2.shrink_to_fit();
    cout << "After shrink_to_fit, capacity: " << s2.capacity()
         << " address: " << static_cast<const void*>(s2.data()) << endl;

    // 6. 数值转换 (C++11)
    cout << "\nNumeric conversions:" << endl;
    string num_str = "123.45";
    int i = stoi(num_str);          // 123
    double d = stod(num_str);       // 123.45
    string back_str = to_string(d); // "123.450000" (before C++26)

    cout << "stoi: " << i << endl;
    cout << "stod: " << d << endl;
    cout << "to_string: " << back_str << endl;

// 7. C++23 新特性演示 (如果编译器支持)
#if __cplusplus >= 202302L
    cout << "\nC++23 features:" << endl;
    string s7;
    s7.resize_and_overwrite(10, [](char* p, size_t n) {
        for (size_t i = 0; i < n; ++i) {
            p[i] = 'A' + i;
        }
        return n;
    });
    cout << "resize_and_overwrite: " << s7 << endl; // "ABCDEFGHIJ"
#endif

    return 0;
}