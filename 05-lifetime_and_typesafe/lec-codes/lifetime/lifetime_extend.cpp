#include <iostream>

struct A {
    A() {
        std::cout << "A is created!" << std::endl;
    }

    ~A() {
        std::cout << "A is destroyed!" << std::endl;
    }
};

A get_A() {
    return A{};
}

int main() {
    {
        const A &a = get_A();
        std::cout << "out of scope" << std::endl;
    }
    
    return 0;
}