#include <iostream>

class A {
private:
    int value;

public:
    A(int v) : value(v) {
        std::cout << "A constructor called with value: " << value << std::endl;
    }

    void show() const { std::cout << "Value: " << value << std::endl; }
};

int main() {
    A* a1 = new A(10); // Calls constructor
    a1->show();        // Calls show method
    delete a1;         // Calls destructor
    return 0;
}