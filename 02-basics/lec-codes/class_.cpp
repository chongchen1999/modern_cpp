#include <iostream>
#include <memory>

class A {
public:
    int value;
    A(int v) : value(v) {
        std::cout << "A constructor called with value: " << value << std::endl;
    }

    void show() const { std::cout << "Value: " << value << std::endl; }
};

int main() {
    A* a1 = new A(10); // Calls constructor
    a1->show();        // Calls show method

    std::cout << "Address of a1: " << a1 << std::endl; // Outputs the address of the object
    std::cout << "Address of a1->value: " << std::addressof(a1->value)
              << std::endl; // Outputs the address of the value member

    // Correct way to print the address of a member function
    auto showPtr = &A::show;
    std::cout << "Address of A::show: " << reinterpret_cast<void*>(showPtr) << std::endl;

    delete a1; // Calls destructor
    return 0;
}