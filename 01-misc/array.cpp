#include <iostream>

void foo(int* x) {
    std::cout << "sizeof x: " << sizeof(x) << std::endl; 
}

int n;

int main() {
    std::cin >> n;
    int x[n];
    for (int i = 0; i < n; ++i) {
        x[i] = i + 1; // Initialize array with some values
    }
    std::cout << "sizeof x: " << sizeof(x) << std::endl;
    foo(x);
}