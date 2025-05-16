#include <iostream>
#include <set>
#include <type_traits>

// Function returning a lambda (C++14 and later)
auto make_adder(int x) {
    return [x](int y) { return x + y; }; // Stateful lambda (captures x)
}

// Stateless lambda example
auto stateless_lambda = [](int a, int b) { return a + b; };

// Using decltype with lambda (C++20 feature)
using LambdaType = decltype([](int a, int b) { return a + b; });

int main() {
    // 1. Lambda returned from function (C++14)
    auto add5 = make_adder(5);
    std::cout << "add5(3) = " << add5(3) << std::endl; // 8

    // 2. Stateless vs stateful lambda
    auto stateless = [](int x) { return x * 2; };
    int y = 10;
    auto stateful = [y](int x) { return x + y; };

    std::cout << "stateless(5) = " << stateless(5) << std::endl; // 10
    std::cout << "stateful(5) = " << stateful(5) << std::endl;   // 15

    // 3. Lambda type and construction (C++20)
    // Before C++20, this wouldn't compile:
    decltype(stateless_lambda) another_lambda;
    std::cout << "another_lambda(2,3) = " << another_lambda(2, 3)
              << std::endl; // 5

    // 4. Using lambda type directly (C++20)
    LambdaType lambda_obj;
    std::cout << "lambda_obj(4,5) = " << lambda_obj(4, 5) << std::endl; // 9

    // 5. Set with lambda comparator (C++20)
    // Before C++20, you'd need to pass the lambda to constructor
    std::set<int, decltype([](int a, int b) { return a > b; })> descending_set;
    descending_set.insert(3);
    descending_set.insert(1);
    descending_set.insert(4);

    std::cout << "descending_set: ";
    for (int x : descending_set) {
        std::cout << x << " ";
    }
    std::cout << std::endl; // 4 3 1

    // 6. Unevaluated lambda expression (C++20)
    // static_assert(std::is_same_v<decltype(stateless_lambda), LambdaType>,
    //               "Types should be the same");

    // 7. Immediately invoked lambda expression
    int z = [y]() {
        std::cout << "Initializing z with y = " << y << std::endl;
        return y * 2;
    }();
    std::cout << "z = " << z << std::endl; // 20

    // 8. Copying and assigning lambdas
    auto lambda1 = [](int x) { return x + 1; };
    auto lambda2 = lambda1; // Copy construction works for stateless lambdas

    auto lambda3 = [y](int x) { return x + y; };
    auto lambda4 = lambda3; // This would fail before C++20 for stateful
    // lambdas But in C++20, even stateful lambdas can be copied if their
    // captures are copyable

    return 0;
}