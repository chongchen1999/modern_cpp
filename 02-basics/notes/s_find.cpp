#include <iostream>

int main() {
    std::string str = "Hello, world!";

    // Find the first occurrence of 'o'
    if (str.find("t") != std::string::npos) {
        std::cout << "Found 't' in the string." << std::endl;
    } else {
        std::cout << "'t' not found in the string." << std::endl;
    }
    return 0;
}