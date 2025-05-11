#include <limits>
#include <iostream>

int main() {
    int a = std::numeric_limits<int>::max();
    int b = a + 1;

    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;    
    return 0;
}