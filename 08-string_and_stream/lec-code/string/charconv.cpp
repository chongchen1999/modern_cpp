#include <array>    // 用于固定大小缓冲区
#include <charconv> // C++20 字符转换库
#include <iostream>
#include <string>

int main() {
    // ========== 示例1：数值转字符串（std::to_chars） ==========
    std::array<char, 10> buffer; // 预分配缓冲区
    int number = 12345;

    // 将数值写入缓冲区
    auto [ptr, ec] =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), number);

    if (ec == std::errc()) {                    // 检查是否成功
        std::string result(buffer.data(), ptr); // 构造字符串
        std::cout << "数值转字符串成功: " << result << std::endl; // 输出: 12345
    } else {
        std::cerr << "转换失败！" << std::endl;
    }

    // ========== 示例2：字符串转数值（std::from_chars） ==========
    std::string str_num = " -42.5 "; // 带空格和符号的字符串
    double parsed_num;

    // 从字符串解析数值（跳过前导空格）
    auto [end_ptr, parse_ec] = std::from_chars(
        str_num.data(), str_num.data() + str_num.size(), parsed_num);

    if (parse_ec == std::errc()) {
        std::cout << "字符串转数值成功: " << parsed_num
                  << std::endl; // 输出: -42.5
    } else {
        std::cerr << "解析失败！错误代码: " << static_cast<int>(parse_ec)
                  << std::endl;
    }

    return 0;
}