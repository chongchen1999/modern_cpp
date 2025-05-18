#include <iostream>
#include <typeinfo>

// 用于演示函数指针转换
void func(int) {
    std::cout << "func(int) called\n";
}
void noexcept_func(int) noexcept {
    std::cout << "noexcept_func(int) called\n";
}

int main() {
    // ============================================
    // 1. Value Category Conversions (值类别转换)
    // ============================================
    std::cout << "=== 1. Value Category Conversions ===\n";

    // Lvalue-to-rvalue conversion
    int x = 42; // x 是左值（有内存地址）
    int y = x;  // x 隐式转换为右值（读取其值）
    std::cout << "Lvalue-to-rvalue: y = " << y << "\n";

    // Array-to-pointer conversion
    int arr[3] = {1, 2, 3};
    int* p = arr; // arr 隐式转换为 int*（指向首元素）
    std::cout << "Array-to-pointer: *p = " << *p << "\n";

    // Function-to-pointer conversion
    void (*func_ptr)(int) = func; // func 隐式转换为函数指针
    func_ptr(10);                 // 调用 func(int)

    // ============================================
    // 2. Numeric Promotions and Conversions (数值提升与转换)
    // ============================================
    std::cout << "\n=== 2. Numeric Promotions and Conversions ===\n";

    // Integer promotion (short → int)
    short s = 100;
    int i = s; // short → int 提升（无精度损失）
    std::cout << "Integer promotion: i = " << i << "\n";

    // Floating-point promotion (float → double)
    float f = 3.14f;
    double d = f; // float → double 提升
    std::cout << "Floating-point promotion: d = " << d << "\n";

    // Numeric conversion (可能丢失精度)
    double pi = 3.1415926535;
    int truncated = pi; // double → int 截断小数部分
    std::cout << "Numeric conversion (double→int): truncated = " << truncated
              << "\n";

    // ============================================
    // 3. Exception-Specified Function Pointer Conversion
    //    (带异常规范的函数指针转换)
    // ============================================
    std::cout
        << "\n=== 3. Exception-Specified Function Pointer Conversion ===\n";

    // 无 noexcept → 带 noexcept 的函数指针（C++17 前允许隐式转换）
    // void (*noexcept_ptr)(int) noexcept =
    //     func; // OK in C++14, deprecated in C++17
    // noexcept_ptr(20);

    // 带 noexcept → 无 noexcept 的函数指针（始终允许）
    void (*normal_ptr)(int) = noexcept_func; // OK
    normal_ptr(30);

    // ============================================
    // 4. Qualification Conversions (限定转换)
    // ============================================
    std::cout << "\n=== 4. Qualification Conversions ===\n";

    // 添加 const 限定（T* → const T*）
    int* ptr = &x;
    const int* const_ptr = ptr; // OK: 添加 const
    std::cout << "Qualification conversion (int* → const int*): *const_ptr = "
              << *const_ptr << "\n";

    // 错误示例：尝试移除 const（const T* → T*）
    // int* invalid_ptr = const_ptr;  // 编译错误：不能隐式移除 const

    // 多级指针的限定转换（T** → const T* const*）
    int** pp = &ptr;
    const int* const* valid_multi = pp; // OK
    std::cout << "Multi-level qualification: **valid_multi = " << **valid_multi
              << "\n";

    return 0;
}