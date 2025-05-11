#include <iostream>

// 第一部分：验证指针和数组的声明与初始化
void TestPart1() {
    int a[][3] = { {1, 2, 3}, {4, 5, 6} };

    // 1. int (*b)[3] = a;
    int (*b)[3] = a; // 合法
    std::cout << "b[0][0] = " << b[0][0] << std::endl; // 应输出 1

    // 2. int **c = a; // 不合法（取消注释会编译错误）
    // int **c = a; // 错误：无法将 'int (*)[3]' 转换为 'int**'

    // 3. int **d = b; // 不合法（取消注释会编译错误）
    // int **d = b; // 错误：无法将 'int (*)[3]' 转换为 'int**'
}

// 第二部分：验证函数参数传递
void Func(int (&arr)[3]) {
    std::cout << "Func: arr[0] = " << arr[0] << std::endl;
}

void Func2(int arr[3]) { // 实际退化为 int*
    std::cout << "Func2: arr[0] = " << arr[0] << std::endl;
}

void TestPart2() {
    int a[]{1, 2, 3};
    int b[]{4, 5, 6, 7};

    // 1. Func(a);
    Func(a); // 合法，a 是 int[3]

    // 2. Func2(a);
    Func2(a); // 合法，a 退化为 int*

    // 3. Func(b); // 不合法（取消注释会编译错误）
    // Func(b); // 错误：无法将 'int [4]' 转换为 'int (&)[3]'

    // 4. Func2(b); // 合法
    Func2(b); // 合法，b 退化为 int*
}

int main() {
    std::cout << "=== 第一部分验证 ===" << std::endl;
    TestPart1();

    std::cout << "\n=== 第二部分验证 ===" << std::endl;
    TestPart2();

    return 0;
}