#include <iostream>
#include <string>
#include <string_view>

// 1. 使用string_view作为函数参数（避免拷贝）
void print_substring(std::string_view sv, size_t pos, size_t len) {
    std::string_view sub = sv.substr(pos, len);
    std::cout << "Substring: \"" << sub << "\" (length=" << sub.size() << ")\n";
}

// 2. 演示string_view的常见操作
void demonstrate_string_view() {
    // 构造方式
    std::string str = "Hello, C++17 string_view!";
    std::string_view sv1{str};               // 来自std::string
    std::string_view sv2{"C-style string"};  // 来自字面量
    std::string_view sv3{str.data() + 7, 5}; // 子串："C++17"

    std::cout << "sv1: " << sv1 << "\n";
    std::cout << "sv2: " << sv2 << "\n";
    std::cout << "sv3: " << sv3 << "\n";

    // 访问操作
    std::cout << "First character of sv1: '" << sv1[0] << "'\n";
    std::cout << "sv3 size: " << sv3.size() << "\n";

    // 查找操作
    size_t comma_pos = sv1.find(',');
    std::cout << "Comma position in sv1: " << comma_pos << "\n";

    // 比较操作
    if (sv3 == "C++17") {
        std::cout << "sv3 is \"C++17\"\n";
    }

    // 函数传参
    print_substring(sv1, 7, 5); // 输出子串："C++17"
}

// 3. 演示生命周期风险（错误示例）
void dangerous_lifetime() {
    std::string_view sv;
    {
        std::string temp = "Temporary string";
        sv = temp; // sv指向temp的内存
        std::cout << "Inside scope: " << sv << "\n";
    } // temp被销毁，sv成为悬垂视图
    // 危险！sv现在指向无效内存
    // std::cout << "Outside scope: " << sv << "\n"; // 未定义行为！
}

int main() {
    std::cout << "----- Demonstration -----\n";
    demonstrate_string_view();

    std::cout << "\n----- Danger Example -----\n";
    dangerous_lifetime(); // 注释掉最后一行为安全运行

    return 0;
}