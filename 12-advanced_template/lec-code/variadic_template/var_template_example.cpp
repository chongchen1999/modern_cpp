#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// 基础情况：当所有参数都已处理时
void printfmt_impl(std::ostream& os, const std::string& format, size_t index) {
    // 检查是否有未处理的占位符
    size_t pos = format.find("{}", index);
    if (pos != std::string::npos) {
        throw std::runtime_error("Not enough arguments for format string");
    }
}

// 递归情况：处理每个参数
template <typename T, typename... Args>
void printfmt_impl(std::ostream& os, const std::string& format, size_t index,
                   T&& value, Args&&... args) {
    // 查找下一个占位符
    size_t pos = format.find("{}", index);
    if (pos == std::string::npos) {
        // 没有更多占位符，输出剩余字符串
        os << format.substr(index);
        // 检查是否有过多参数
        if (sizeof...(Args) > 0) {
            throw std::runtime_error("Too many arguments for format string");
        }
        return;
    }

    // 输出占位符前的文本
    os << format.substr(index, pos - index);
    // 输出当前参数
    os << value;
    // 递归处理剩余参数
    printfmt_impl(os, format, pos + 2, std::forward<Args>(args)...);
}

// 主函数
template <typename... Args>
void printfmt(const std::string& format, Args&&... args) {
    printfmt_impl(std::cout, format, 0, std::forward<Args>(args)...);
    std::cout << std::endl;
}

int main() {
    printfmt("Name: {}, Age: {}, Score: {}", "Alice", 25, 95.5);
    // 输出: Name: Alice, Age: 25, Score: 95.5

    // 测试错误情况
    // printfmt("Name: {}, Age: {}", "Alice", 25, 95.5); // 抛出异常: Too many
    // arguments printfmt("Name: {}, Age: {}, Score: {}", "Alice", 25); //
    // 抛出异常: Not enough arguments

    return 0;
}