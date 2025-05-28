#include <format> // C++20 引入 std::format
#include <print> // C++23 引入 std::print（若编译器不支持，可用 fmt 库替代）
#include <string>
#include <vector>

int main() {
    // 1. 基本用法：std::format 格式化字符串
    std::string formatted_str =
        std::format("Hello, {}! The answer is {}.", "world", 42);
    std::println("Formatted string: {}", formatted_str); // 输出格式化结果

    // 2. 格式化数字和类型
    double pi = 3.1415926535;
    std::println("Pi: {:.2f}", pi); // 保留两位小数

    // 3. 位置参数（通过索引指定）
    std::println("{1} {0}!", "world", "Hello");

    // 4. 对齐和填充
    std::println("Left-aligned: {:<10}", 42);  // 左对齐，宽度 10
    std::println("Right-aligned: {:>10}", 42); // 右对齐
    std::println("Centered: {:^10}", 42);      // 居中
    std::println("With fill: {:*^10}", 42);    // 用 '*' 填充

    // 5. 格式化容器（需自定义格式化逻辑）
    std::vector<int> vec = {1, 2, 3};
    std::string vec_str = std::format("[{}, {}, {}]", vec[0], vec[1], vec[2]);
    std::println("Vector: {}", vec_str);

    // 6. 直接输出到控制台（std::print）
    std::print("This is printed directly. "); // 不换行
    std::println("And this adds a newline."); // 自动换行

    // 7. 错误处理：无效格式会抛出 std::format_error
    // try {
    //     std::string bad_str = std::format("Invalid: {:d}", "not_a_number");
    // } catch (const std::format_error& e) {
    //     std::println("Error: {}", e.what()); // 捕获格式错误
    // }
}