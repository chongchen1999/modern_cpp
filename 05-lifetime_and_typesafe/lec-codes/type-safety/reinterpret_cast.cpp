#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>

// 1. Converting between object pointers
void pointer_conversion() {
    std::cout << "=== Pointer Conversion ===" << std::endl;

    int x = 42;
    int* int_ptr = &x;

    // Convert int* to void* and back
    void* void_ptr = reinterpret_cast<void*>(int_ptr);
    int* int_ptr2 = reinterpret_cast<int*>(void_ptr);

    std::cout << "Original value: " << *int_ptr
              << ", After round-trip: " << *int_ptr2 << std::endl;

    // Pointer-interconvertible example
    struct Base {
        int a;
    };
    struct Derived : Base {
        int b;
    };

    Derived d;
    Base* base_ptr = &d; // Standard pointer conversion
    Derived* derived_ptr = reinterpret_cast<Derived*>(base_ptr);
    std::cout << "Derived object through base pointer: " << derived_ptr->b
              << std::endl;
}

int func() {
    return 42;
}

// 2. Converting between function pointers
void function_pointer_conversion() {
    std::cout << "\n=== Function Pointer Conversion ===" << std::endl;

    // A simple function

    // Convert function pointer to void* and back
    void (*func_ptr)() = reinterpret_cast<void (*)()>(func);
    auto original_func = reinterpret_cast<decltype(&func)>(func_ptr);

    std::cout << "Function result after round-trip: " << original_func()
              << std::endl;

    // Note: This is platform-dependent and may not work on all systems
}

// 3. Converting between pointers and integers
void pointer_integer_conversion() {
    std::cout << "\n=== Pointer-Integer Conversion ===" << std::endl;

    int x = 100;
    int* ptr = &x;

    // Convert pointer to integer
    std::uintptr_t int_val = reinterpret_cast<std::uintptr_t>(ptr);
    std::cout << "Pointer as integer: " << int_val << std::endl;

    // Convert back to pointer
    int* ptr2 = reinterpret_cast<int*>(int_val);
    std::cout << "Integer back to pointer, value: " << *ptr2 << std::endl;

    // Note: Converting arbitrary integers to pointers is UB
}

// 4. Reference conversion
void reference_conversion() {
    std::cout << "\n=== Reference Conversion ===" << std::endl;

    int x = 42;
    int& ref = x;

    // Convert reference to different type reference
    // This is allowed under strict aliasing rules for compatible types
    unsigned int& alias_ref = reinterpret_cast<unsigned int&>(ref);
    std::cout << "Original int: " << x
              << ", Aliased unsigned int: " << alias_ref << std::endl;

    // Note: Converting to completely different types (like float) is UB
    // For that, use std::bit_cast or std::memcpy
}

// 5. Demonstrating what NOT to do
void dangerous_conversions() {
    std::cout << "\n=== Dangerous Conversions (AVOID) ===" << std::endl;

    // 1. Converting between incompatible pointer types
    float f = 3.14f;
    int* bad_ptr = reinterpret_cast<int*>(&f); // UB when dereferenced
    std::cout
        << "Dangerous float-to-int pointer conversion (UB if dereferenced)"
        << std::endl;

    // 2. Converting 0/NULL
    int* null_ptr = reinterpret_cast<int*>(0); // UB
    std::cout << "Dangerous NULL conversion (UB)" << std::endl;

    // 3. Converting to smaller integer type
    auto ptr = reinterpret_cast<int*>(&f);
    auto small_int = reinterpret_cast<long>(ptr); // UB if pointer is larger
    std::cout << "Dangerous pointer-to-small-int conversion (UB)" << std::endl;

    // Note: These are shown for demonstration only - don't do this in real
    // code!
}

// Safe alternative to type punning
void safe_type_punning() {
    std::cout << "\n=== Safe Type Punning ===" << std::endl;

    float f = 3.14f;

    // Using std::bit_cast (C++20)
    if constexpr (std::is_constant_evaluated()) {
        // Compile-time version
        constexpr float cf = 3.14f;
        constexpr auto as_int = std::bit_cast<int>(cf);
        std::cout << "std::bit_cast (compile-time): " << as_int << std::endl;
    } else {
        // Runtime version
        auto as_int = std::bit_cast<int>(f);
        std::cout << "std::bit_cast (runtime): " << as_int << std::endl;
    }

    // Using memcpy (pre-C++20)
    int int_value;
    std::memcpy(&int_value, &f, sizeof(f));
    std::cout << "memcpy version: " << int_value << std::endl;
}

int main() {
    pointer_conversion();
    function_pointer_conversion();
    pointer_integer_conversion();
    reference_conversion();
    safe_type_punning();
    dangerous_conversions();

    return 0;
}