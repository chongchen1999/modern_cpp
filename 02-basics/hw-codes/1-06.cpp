#include <iostream>

// 1. 定义一个函数，其返回值为 `int`，参数为 `float` 和 `double`
int compute(float f, double d) {
    return static_cast<int>(f * d); // 示例计算：float × double → int
}

using i_Fn_f_d = int (*)(float, double); // 定义函数指针类型

// 2. 定义目标函数，它接受一个函数指针作为参数，并返回 `void`
void processFunction(i_Fn_f_d funcPtr) {
    float f = 3.14f;
    double d = 2.71828;

    // 调用传入的函数指针
    int result = funcPtr(f, d);

    // 输出结果
    std::cout << "Result: " << result << std::endl;
}

int main() {
    // 3. 将 `compute` 函数的地址传递给 `processFunction`
    processFunction(compute);

    return 0;
}