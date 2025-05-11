#include <map>
#include <iostream>

int main() {
    std::map<int, int> m;
    m[0] = m.size();
    std::cout << m.size() << std::endl; // 1
    std::cout << m[0] << std::endl; // 0
}