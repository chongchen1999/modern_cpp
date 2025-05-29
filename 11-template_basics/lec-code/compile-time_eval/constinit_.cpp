#include <iostream>
#include <random>

// 1. constinit 全局变量（必须用常量表达式初始化）
constexpr int getValue() {
    return 42;
}
constinit int globalVar = getValue(); // 正确：编译期初始化
// constinit int badVar = std::rand(); // 错误：非常量表达式

// 2. constexpr 全局变量（隐含 const，不可修改）
constexpr int constexprVar = 100;

// 3. 普通全局变量（可能动态初始化）
int dynamicVar = std::rand(); // 运行时初始化

void demo() {
    // 4. constinit 静态局部变量
    static constinit int staticLocal = 10; // 编译期初始化
    staticLocal += 1; // 允许修改（constinit 不限制可变性）
    std::cout << "staticLocal: " << staticLocal << std::endl;

    // 5. 错误用法：constinit 不能用于非静态局部变量
    // constinit int localVar = 20; // 编译错误
}

int main() {
    std::cout << "=== 初始化值 ===" << std::endl;
    std::cout << "globalVar (constinit): " << globalVar << std::endl;
    std::cout << "constexprVar (constexpr): " << constexprVar << std::endl;
    std::cout << "dynamicVar (普通变量): " << dynamicVar << std::endl;

    // 修改 constinit 变量（允许）
    globalVar = 200;
    std::cout << "\n=== 修改后 ===" << std::endl;
    std::cout << "globalVar (修改后): " << globalVar << std::endl;

    // 尝试修改 constexpr 变量（错误）
    // constexprVar = 300; // 编译错误：constexpr 隐含 const

    // 多次调用 demo()，观察静态局部变量的行为
    std::cout << "\n=== 调用 demo() ===" << std::endl;
    demo(); // 输出 staticLocal: 11
    demo(); // 输出 staticLocal: 12（保持状态）
}