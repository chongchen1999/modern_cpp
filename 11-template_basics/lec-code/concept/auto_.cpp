#include <iostream>

auto max(auto x, auto y) {
    return (x > y) ? x : y;
}

int main() {
    std::cout << "Max of 3 and 4 is: " << max(3, 4) << std::endl;
    std::cout << "Max of 3.5 and 2.1 is: " << max(3.5, 2.1) << std::endl;
    return 0;
}