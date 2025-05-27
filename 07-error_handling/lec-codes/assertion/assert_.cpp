#include <cassert> // 标准断言头文件
#include <iostream>
#include <type_traits> // 用于static_assert类型检查
#include <cmath> // 用于数学函数，如sqrt

// 自定义断言宏
#ifndef NDEBUG
#define CUSTOM_ASSERT(condition, message)                                      \
    do {                                                                       \
        if (!(condition)) {                                                    \
            std::cerr << "【自定义断言失败】" << message << "\n"               \
                      << "文件: " << __FILE__ << "\n"                          \
                      << "行号: " << __LINE__ << "\n"                          \
                      << "表达式: " << #condition << std::endl;                \
            std::abort();                                                      \
        }                                                                      \
    } while (false)
#else
#define CUSTOM_ASSERT(condition, message)                                      \
    do {                                                                       \
    } while (false)
#endif

// 演示函数：计算平方根（要求输入必须非负）
double safe_sqrt(double x) {
    // 标准断言：检查输入有效性
    assert(x >= 0 && "输入不能为负数");

    // 自定义断言：添加更多上下文信息
    CUSTOM_ASSERT(x <= 1000, "输入值过大，可能导致精度问题");

    return sqrt(x);
}

// 类型安全的绝对值函数模板
template <typename T>
T safe_abs(T value) {
    // 静态断言：编译时类型检查
    static_assert(std::is_arithmetic<T>::value,
                  "T必须是算术类型(int, float等)");

    return value < 0 ? -value : value;
}

int main() {
    std::cout << "=== C++断言演示程序 ===" << std::endl;

    // 1. 演示标准assert
    std::cout << "\n[1] 标准assert演示:" << std::endl;
    std::cout << "计算9的平方根: " << safe_sqrt(9) << std::endl;

    // 取消下面注释会触发断言失败
    // std::cout << "计算-4的平方根: " << safe_sqrt(-4) << std::endl;

    // 2. 演示自定义assert
    std::cout << "\n[2] 自定义assert演示:" << std::endl;
    std::cout << "计算100的平方根: " << safe_sqrt(100) << std::endl;

    // 取消下面注释会触发自定义断言失败
    // std::cout << "计算2000的平方根: " << safe_sqrt(2000) << std::endl;

    // 3. 演示static_assert
    std::cout << "\n[3] static_assert演示:" << std::endl;
    std::cout << "int绝对值: " << safe_abs(-5) << std::endl;
    std::cout << "double绝对值: " << safe_abs(-3.14) << std::endl;

    // 取消下面注释会导致编译错误（静态断言失败）
    /*
    struct Point { int x; int y; };
    Point p{-1, 2};
    std::cout << "Point绝对值: " << safe_abs(p) << std::endl;
    */

    // 4. 演示NDEBUG的影响
    std::cout << "\n[4] NDEBUG影响演示:" << std::endl;
#ifdef NDEBUG
    std::cout << "NDEBUG已定义，标准assert被禁用" << std::endl;
#else
    std::cout << "NDEBUG未定义，标准assert启用" << std::endl;
#endif

    std::cout << "\n程序正常结束" << std::endl;
    return 0;
}