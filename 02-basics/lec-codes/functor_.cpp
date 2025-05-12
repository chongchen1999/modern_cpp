#include <iostream>

struct Add {
    int operator()(int a, int b) const {
        return a + b;
    }
};

int main() {
    Add add;
    std::cout << add(3, 5); // 输出 8（调用 operator()）
}