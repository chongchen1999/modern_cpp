#include <cstdlib>  // 需要包含这个头文件才能使用 std::abs()
#include <iostream>

int main() {
    // 1. 基本表达式
    int a = 10;  // 10是一个字面量表达式
    int b = a;   // a是一个标识符表达式

    // 2. 算术表达式
    int sum = a + b;         // 加法
    int difference = a - b;  // 减法
    int product = a * b;     // 乘法
    int quotient = a / b;    // 除法
    int remainder = a % b;   // 取模

    std::cout << "算术表达式结果:" << std::endl;
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << difference << std::endl;
    std::cout << "a * b = " << product << std::endl;
    std::cout << "a / b = " << quotient << std::endl;
    std::cout << "a % b = " << remainder << std::endl << std::endl;

    // 3. 关系表达式
    bool isEqual = (a == b);
    bool isNotEqual = (a != b);
    bool isGreater = (a > b);
    bool isLess = (a < b);

    std::cout << "关系表达式结果:" << std::endl;
    std::cout << "a == b: " << isEqual << std::endl;
    std::cout << "a != b: " << isNotEqual << std::endl;
    std::cout << "a > b: " << isGreater << std::endl;
    std::cout << "a < b: " << isLess << std::endl << std::endl;

    // 4. 逻辑表达式
    bool logicalAnd = (a > 5) && (b < 20);
    bool logicalOr = (a > 15) || (b < 5);
    bool logicalNot = !(a == b);

    std::cout << "逻辑表达式结果:" << std::endl;
    std::cout << "(a>5 && b<20): " << logicalAnd << std::endl;
    std::cout << "(a>15 || b<5): " << logicalOr << std::endl;
    std::cout << "!(a==b): " << logicalNot << std::endl << std::endl;

    // 5. 赋值表达式
    a += 5;  // 等价于 a = a + 5
    b *= 2;  // 等价于 b = b * 2

    std::cout << "赋值表达式结果:" << std::endl;
    std::cout << "a += 5 → a = " << a << std::endl;
    std::cout << "b *= 2 → b = " << b << std::endl << std::endl;

    // 6. 条件表达式(三元运算符)
    int max = (a > b) ? a : b;
    std::cout << "条件表达式结果:" << std::endl;
    std::cout << "a和b中较大的值是: " << max << std::endl << std::endl;

    // 7. 逗号表达式
    int c = (a++, b++, a + b);  // 先计算a++和b++，然后计算a+b
    std::cout << "逗号表达式结果:" << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "a = " << a << ", b = " << b << std::endl << std::endl;

    // 8. 函数调用表达式
    std::cout << "函数调用表达式结果:" << std::endl;
    std::cout << "abs(-10): " << std::abs(-10) << std::endl;

    // 9. 类型转换表达式
    double pi = 3.14159;
    int intPi = static_cast<int>(pi);  // C++风格的类型转换
    std::cout << "类型转换表达式结果:" << std::endl;
    std::cout << "double pi = " << pi << " → int intPi = " << intPi
              << std::endl;

    return 0;
}