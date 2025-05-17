#include <cstring>
#include <iostream>
#include <new>

// ===== 1. Strict Aliasing Rules (严格别名规则) =====
// 规则：不同类型的指针不能访问同一内存（除非例外情况）
void strict_aliasing_examples() {
    int x = 42;
    float* f = reinterpret_cast<float*>(&x); // ❌ 违反严格别名规则（UB）
    // *f = 3.14f; // 未定义行为！

    // ✅ 合法的例外情况：
    // (1) char*/unsigned char*/std::byte* 可以别名任何类型
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&x);
    std::cout << "Bytes of x: ";
    for (size_t i = 0; i < sizeof(x); i++) {
        std::cout << static_cast<int>(bytes[i]) << " "; // ✅ 合法
    }
    std::cout << "\n";

    // (2) 相同类型（忽略 const/volatile）
    const int* p = &x; // ✅ int* 和 const int* 可以别名

    // (3) 有符号/无符号整型互相转换
    unsigned int* u = reinterpret_cast<unsigned int*>(&x); // ✅ 合法

    // (4) 使用 memcpy 避免别名问题
    float pi = 3.14f;
    int pi_as_int;
    std::memcpy(&pi_as_int, &pi, sizeof(float)); // ✅ 安全复制字节
    std::cout << "Pi as int: " << pi_as_int << "\n";
}

// ===== 2. `restrict` 关键字（C99/C++ 非标准扩展） =====
// 作用：告诉编译器指针是唯一的（无别名），允许激进优化
#if defined(__GNUC__) || defined(__clang__)
#define RESTRICT __restrict__
#elif defined(_MSC_VER)
#define RESTRICT __restrict
#else
#define RESTRICT // 无支持时留空
#endif

void add_arrays(int* RESTRICT a, int* RESTRICT b, int* RESTRICT out, size_t n) {
    // 编译器假设 a、b、out 不重叠，可以自动向量化
    for (size_t i = 0; i < n; i++) {
        out[i] = a[i] + b[i];
    }
}

// ===== 3. 综合测试 =====
int main() {
    std::cout << "=== Strict Aliasing Examples ===\n";
    strict_aliasing_examples();

    std::cout << "\n=== `restrict` Optimization ===\n";
    int a[4] = {1, 2, 3, 4};
    int b[4] = {5, 6, 7, 8};
    int out[4];
    add_arrays(a, b, out, 4);

    std::cout << "Result: ";
    for (int x : out)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}