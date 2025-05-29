#include <print>

int main() {
    auto fib = [](this auto self, int n) {
        if (n <= 1) return n;
        return self(n - 1) + self(n - 2);
    };
    std::print("Fibonacci(10) = {}\n", fib(10));
    return 0;
}