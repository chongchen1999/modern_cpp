#include <functional>
#include <future>
#include <iostream>
#include <numeric> // for std::async
#include <optional>
#include <ranges>
#include <string>
#include <vector>

// 1. Fixed custom Maybe Monad
template <typename T>
struct Maybe {
    std::optional<T> value;

    Maybe(T v) : value(v) {}
    Maybe(std::nullopt_t) : value(std::nullopt) {}

    // Fixed bind: properly handle the case when value is nullopt
    template <typename F>
    auto bind(F f) -> decltype(f(std::declval<T>())) {
        return value ? f(*value) : decltype(f(std::declval<T>()))(std::nullopt);
    }

    void print(const std::string& msg = "") const {
        std::cout << msg << (value ? std::to_string(*value) : "null")
                  << std::endl;
    }
};

// 2. Using std::optional as Monad
auto divide(int a, int b) -> std::optional<int> {
    return b != 0 ? std::optional(a / b) : std::nullopt;
}

// 3. Simulating std::future's then (C++20 alternative)
template <typename T>
auto async_add(int a, int b) -> std::future<T> {
    return std::async([=]() { return static_cast<T>(a + b); });
}

template <typename T, typename F>
auto then(std::future<T>&& fut, F f)
    -> std::future<decltype(f(std::declval<T>()))> {
    return std::async(
        [fut = std::move(fut), f]() mutable { return f(fut.get()); });
}

// 4. Ranges library example
auto range_monad_example() {
    auto r = std::views::iota(1, 6) // Changed to 6 to include 5 in the range
             | std::views::transform([](int x) { return x * 2; }) |
             std::views::filter([](int x) { return x % 3 == 0; });
    return r;
}

int main() {
    // ===== 1. Custom Maybe Monad =====
    Maybe<int> m1(42);
    m1.print("Custom Maybe (initial): ");

    auto result = m1.bind([](int x) { return Maybe(x * 2); }).bind([](int x) {
        return Maybe(x + 1);
    });
    result.print("Custom Maybe (after bind): ");

    // ===== 2. std::optional as Monad =====
    auto opt = divide(10, 2)
                   .and_then([](int x) {
                       return divide(x, 2);
                   }) // Changed denominator to 2 for non-null result
                   .transform([](int x) { return x * 3; });
    std::cout << "std::optional result: "
              << (opt ? std::to_string(*opt) : "null") << std::endl;

    // ===== 3. Simulating std::future's then =====
    auto future = then(async_add<int>(2, 3),        // Added template parameter
                       [](int x) { return x + 10; } // Simplified lambda
    );
    std::cout << "std::future result: " << future.get() << std::endl;

    // ===== 4. Ranges operations =====
    std::cout << "Ranges result: ";
    for (int x : range_monad_example()) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}