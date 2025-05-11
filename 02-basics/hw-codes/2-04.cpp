#include <iostream>

void Test(int) {
    std::cout << "Non-template void Test(int)\n";
}

template <typename T>
T Test(int) {
    std::cout << "Template T Test(int) with T = " << typeid(T).name() << "\n";
    return T{};
}

int main() {
    Test(42);       // Calls non-template void Test(int)
    auto x = Test<int>(42);  // Calls template with T = int
    std::cout << "x = " << x << "\n"; // x is of type int

    Test<void>(42); // Calls template with T = void (but return type is void)
}