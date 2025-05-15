#include <functional>
#include <iostream>
#include <string>

// 普通函数
double multiply(double a, double b) {
    return a * b;
}

// 函数对象
struct Divide {
    double operator()(double a, double b) const { return a / b; }
};

// 类成员函数
class Math {
public:
    static int square(int x) { return x * x; }
    int cube(int x) const { return x * x * x; }
};

int main() {
    // 1. 存储普通函数
    std::function<double(double, double)> func1 = multiply;
    std::cout << "Multiply: " << func1(4, 5) << std::endl; // 输出: 20

    // 2. 存储函数对象
    Divide divide;
    std::function<double(double, double)> func2 = divide;
    std::cout << "Divide: " << func2(20, 5) << std::endl; // 输出: 4

    // 3. 存储lambda表达式
    std::function<double(double, double)> func3 = [](double a, double b) {
        return a + b;
    };
    std::cout << "Add: " << func3(4, 5) << std::endl; // 输出: 9

    // 4. 存储静态成员函数
    std::function<int(int)> func4 = Math::square;
    std::cout << "Square: " << func4(5) << std::endl; // 输出: 25

    // 5. 存储非静态成员函数
    Math math;
    // 使用 std::bind 绑定对象实例
    std::function<int(int)> func5 =
        std::bind(&Math::cube, &math, std::placeholders::_1);
    std::cout << "Cube: " << func5(3) << std::endl; // 输出: 27

    std::function<int(int)> func5_lambda = [&math](int x) {
        return math.cube(x);
    };
    std::cout << "Cube: " << func5_lambda(3) << std::endl;

    // 检查 std::function 是否为空
    std::function<void()> emptyFunc;
    if (!emptyFunc) {
        std::cout << "emptyFunc is empty" << std::endl;
    }

    return 0;
}