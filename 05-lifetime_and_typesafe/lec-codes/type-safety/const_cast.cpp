#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

// 1. 基本概念：const_cast 用于移除 const 限定符
void basic_concept() {
    std::cout << "=== 基本概念演示 ===" << std::endl;

    int value = 42;
    const int* const_ptr = &value;

    // 使用 const_cast 移除 const 限定符
    int* non_const_ptr = const_cast<int*>(const_ptr);
    *non_const_ptr = 100;

    std::cout << "修改后的值: " << value << std::endl;
    std::cout << "原始指针的值: " << *const_ptr << std::endl;
}

// 2. 合法使用场景1：原本就不是只读的数据
void ftp_command_example() {
    std::cout << "\n=== FTP命令处理示例 ===" << std::endl;

    // 模拟用户输入的命令（存储在堆上，不是只读的）
    char* user_command = new char[100];
    std::strcpy(user_command, "open 192.168.1.1 8080");

    // 处理函数通常使用 string_view（const char*）
    std::string_view command_view(user_command);

    // 我们需要修改命令中的IP部分（添加'\0'终止符）
    if (command_view.substr(0, 4) == "open") {
        // 我们知道原始数据是可修改的，所以使用 const_cast
        char* mutable_command = const_cast<char*>(command_view.data());

        // 找到IP和端口之间的空格
        size_t space_pos = command_view.find(' ', 5);
        if (space_pos != std::string_view::npos) {
            mutable_command[space_pos] = '\0'; // 修改为终止符
            const char* ip = command_view.data() + 5;
            const char* port = command_view.data() + space_pos + 1;

            std::cout << "IP: " << ip << std::endl;
            std::cout << "Port: " << port << std::endl;
        }
    }

    delete[] user_command;
}

// 3. 合法使用场景2：库函数忘记加const但实际不会修改
void library_function_example() {
    std::cout << "\n=== 库函数示例 ===" << std::endl;

    // 假设这是一个第三方库函数，忘记加const但实际上不会修改参数
    void legacy_print(char* str); // 前向声明

    const char* message = "Hello from const string";

    // 我们知道这个函数实际上不会修改字符串
    legacy_print(const_cast<char*>(message));
}

// 模拟的第三方库函数
void legacy_print(char* str) {
    std::cout << "库函数输出: " << str << std::endl;
}

// 4. 危险用法：修改真正的只读数据
void undefined_behavior_example() {
    std::cout << "\n=== 未定义行为示例 ===" << std::endl;

    const int volatile read_only_value = 42;

    std::cout << "原始值: " << read_only_value << std::endl;

    // 危险！尝试修改真正的const变量
    int volatile& mutable_ref = const_cast<int volatile&>(read_only_value);
    mutable_ref = 100;

    // 这是未定义行为，结果不可预测
    std::cout << "尝试修改后的值: " << read_only_value << ' '
              << &read_only_value << std::endl;
    std::cout << "通过引用看到的值: " << mutable_ref << ' ' << &mutable_ref
              << std::endl;

    // 在某些编译器/平台上可能会崩溃或表现不一致
}

// 5. volatile 的情况
void volatile_example() {
    std::cout << "\n=== volatile 示例 ===" << std::endl;

    const volatile int sensor_value = 100;
    // const volatile int* volatile_ptr = &sensor_value;

    // // 移除 volatile 限定符
    // int* non_volatile_ptr = const_cast<int*>(volatile_ptr);

    // // 这违背了 volatile 的初衷，写入可能不会立即反映到内存
    // *non_volatile_ptr = 200;

    int& ref_sensor_value = const_cast<int&>(sensor_value);
    ref_sensor_value = 200;

    std::cout << "传感器值: " << sensor_value << std::endl;
}

int main() {
    basic_concept();
    ftp_command_example();
    library_function_example();

    // 注释掉危险示例，避免程序崩溃
    undefined_behavior_example();

    volatile_example();

    return 0;
}