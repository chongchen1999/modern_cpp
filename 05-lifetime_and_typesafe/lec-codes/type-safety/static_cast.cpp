#include <cstdint>
#include <iostream>
#include <type_traits>

// Function 1: Basic numeric conversions
void demonstrate_numeric_conversions() {
    std::cout << "=== Numeric Conversions ===\n";

    // Implicit conversions that can be made explicit with static_cast
    int i = 42;
    double d = static_cast<double>(i);
    std::cout << "int to double: " << d << "\n";

    // Inverse operations (narrowing conversions)
    double pi = 3.14159;
    int approx_pi = static_cast<int>(pi);
    std::cout << "double to int (narrowing): " << approx_pi << "\n";

    short s = static_cast<short>(i);
    std::cout << "int to short (narrowing): " << s << "\n";

    // Note: Can't convert pointer back to array/function
    // int arr[5];
    // int* ptr = arr;  // array-to-pointer decay
    // int(*arr_ptr)[5] = static_cast<int(*)[5]>(ptr); // Compile error
}

// Function 2: Enumeration conversions
void demonstrate_enum_conversions() {
    std::cout << "\n=== Enumeration Conversions ===\n";

    enum class Color : std::uint8_t { Red = 1, Green = 2, Blue = 3 };

    // Enum to underlying type
    Color c = Color::Green;
    std::uint8_t color_val = static_cast<std::uint8_t>(c);
    std::cout << "Enum to underlying type: " << static_cast<int>(color_val)
              << "\n";

    // Underlying type to enum
    Color c2 = static_cast<Color>(3);
    if (c2 == Color::Blue) {
        std::cout << "Underlying type to enum: successfully got Blue\n";
    }

    // Note: Enum has limits, not whole range of underlying type
    // Color c3 = static_cast<Color>(255); // May be undefined behavior
}

// Function 3: Inheritance-related conversions
class Base {
public:
    virtual ~Base() = default;
    virtual void foo() { std::cout << "Base::foo()\n"; }
};

class Derived : public Base {
public:
    void foo() override { std::cout << "Derived::foo()\n"; }
    void bar() { std::cout << "Derived::bar()\n"; }
};

class AnotherDerived : public Base {};

void demonstrate_inheritance_conversions() {
    std::cout << "\n=== Inheritance Conversions ===\n";

    Derived d;
    Base* b = &d; // Upcast (implicit)
    b->foo();

    // Downcast (explicit)
    Derived* d_ptr = static_cast<Derived*>(b);
    d_ptr->bar(); // Safe because we know it's actually a Derived

    // Dangerous downcast - undefined behavior if wrong
    AnotherDerived ad;
    Base* bad_b = &ad;
    // Derived* bad_d = static_cast<Derived*>(bad_b); // Compiles but UB

    // Private inheritance example
    class PrivDerived : private Base {};
    PrivDerived pd;
    // Base* pb = static_cast<Base*>(&pd); // Error: private inheritance
}

// Function 4: Standard-layout types
struct StandardLayout {
    int x;
    int y;

private:
    int z; // Before C++23, this would make it non-standard-layout
};

struct NonStandardLayout : public Base {
    int x;
    virtual void f() {}
};

void demonstrate_standard_layout() {
    std::cout << "\n=== Standard Layout Types ===\n";

    std::cout << "StandardLayout is standard layout: "
              << std::is_standard_layout_v<StandardLayout> << "\n";
    std::cout << "NonStandardLayout is standard layout: "
              << std::is_standard_layout_v<NonStandardLayout> << "\n";
}

// Function 5: Pointer conversions
void demonstrate_pointer_conversions() {
    std::cout << "\n=== Pointer Conversions ===\n";

    int x = 42;
    void* vptr = &x;                     // Implicit conversion to void*
    int* iptr = static_cast<int*>(vptr); // Explicit conversion back
    std::cout << "Pointer conversion preserved value: " << *iptr << "\n";

    // Standard layout example
    struct S {
        int a;
        double b;
    };
    S s{10, 3.14};
    void* sptr = &s;
    int* aptr =
        static_cast<int*>(sptr); // Pointer-interconvertible with first member
    std::cout << "First member via pointer conversion: " << *aptr << "\n";

    // Note: Pointer values might change with multiple inheritance
    class MIBase1 {
    public:
        int x;
    };
    class MIBase2 {
    public:
        int y;
    };
    class MIDerived : public MIBase1, public MIBase2 {};

    MIDerived md;
    MIBase2* b2 = &md;
    void* vp = b2;
    // MIBase1* b1 = static_cast<MIBase1*>(vp); // Not safe - wrong address
}

// Function 6: Conversion to void
[[nodiscard]] int important_function() {
    return 42;
}

void demonstrate_void_conversion() {
    std::cout << "\n=== Conversion to void ===\n";

    // Discarding a nodiscard value
    static_cast<void>(important_function());
    std::cout << "Nodiscard value discarded\n";

    // Suppressing unused variable warning
    int unused = 42;
    static_cast<void>(unused);
}

// Function 7: Object construction
class Constructible {
    int value;

public:
    Constructible(int v) : value(v) {}
    void print() { std::cout << "Constructible with value: " << value << "\n"; }
};

void demonstrate_object_construction() {
    std::cout << "\n=== Object Construction ===\n";

    Constructible c = static_cast<Constructible>(42);
    c.print();
}

// Function 8: Function pointer conversion
void func(int) {
    std::cout << "func1 called\n";
}
void func(double) {
    std::cout << "func2 called\n";
}

void demonstrate_function_pointers() {
    std::cout << "\n=== Function Pointer Conversion ===\n";
    
    auto p = static_cast<void(*)(int)>(&func); // Implicit conversion to function pointer

    // Without cast - ambiguous
    // void (*fp)(int) = func1; // Would be fine, but with overloads:
    void (*fp1)(int) = static_cast<void (*)(int)>(func);
    fp1(42);

    // Overloaded functions
    void (*fp2)(double) = static_cast<void (*)(double)>(func);
    fp2(3.14);
}

int main() {
    demonstrate_numeric_conversions();
    demonstrate_enum_conversions();
    demonstrate_inheritance_conversions();
    demonstrate_standard_layout();
    demonstrate_pointer_conversions();
    demonstrate_void_conversion();
    demonstrate_object_construction();
    demonstrate_function_pointers();

    return 0;
}