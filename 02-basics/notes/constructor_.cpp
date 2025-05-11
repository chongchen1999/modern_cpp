#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Resource {
private:
    std::string name;
    int* data;
    size_t size;

public:
    // Default constructor
    Resource() : name("unnamed"), data(nullptr), size(0) {
        std::cout << "Default constructor: Created empty resource" << std::endl;
    }

    // Parameterized constructor
    Resource(const std::string& n, size_t s) : name(n), size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
        std::cout << "Parameterized constructor: Created " << name
                  << " with size " << size << std::endl;
    }

    // Copy constructor
    Resource(const Resource& other)
        : name(other.name + "_copy"), size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy constructor: Copied " << other.name << " to " << name
                  << std::endl;
    }

    // Move constructor (C++11)
    Resource(Resource&& other) noexcept
        : name(std::move(other.name)), data(other.data), size(other.size) {
        // Take ownership from the source object
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor: Moved " << name << std::endl;
    }

    // Constructor delegation (C++11)
    Resource(const std::string& n) : Resource(n, 10) {
        std::cout
            << "Delegating constructor: Delegated to parameterized constructor"
            << std::endl;
    }

    // Initializer list constructor (C++11)
    Resource(std::initializer_list<int> values)
        : name("initializer_list"), size(values.size()) {
        data = new int[size];
        size_t i = 0;
        for (const auto& val : values) {
            data[i++] = val;
        }
        std::cout << "Initializer list constructor: Created resource with "
                  << size << " values" << std::endl;
    }

    // Conversion constructor (implicit)
    Resource(int initialSize) : name("converted"), size(initialSize) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
        std::cout << "Conversion constructor: Created from integer "
                  << initialSize << std::endl;
    }

    // Explicit constructor (prevents implicit conversion)
    explicit Resource(char c) : name(1, c), size(1) {
        data = new int[1];
        data[0] = static_cast<int>(c);
        std::cout << "Explicit constructor: Created from char " << c
                  << std::endl;
    }

    // Destructor
    ~Resource() {
        if (data) {
            delete[] data;
            std::cout << "Destructor: Destroyed " << name << std::endl;
        } else {
            std::cout << "Destructor: Destroyed empty " << name << std::endl;
        }
    }

    // Preview data
    void preview() const {
        std::cout << "Resource " << name << " contains: ";
        if (data && size > 0) {
            std::cout << "[ ";
            for (size_t i = 0; i < std::min(size_t(5), size); ++i) {
                std::cout << data[i] << " ";
            }
            if (size > 5)
                std::cout << "...";
            std::cout << "]";
        } else {
            std::cout << "nothing (empty)";
        }
        std::cout << std::endl;
    }

    // Move a Resource
    Resource createAndMove(const std::string& n, size_t s) {
        Resource temp(n, s);
        return temp; // Return Value Optimization (RVO) may apply here
    }

    // Static function to demonstrate temporary object
    static void demonstrate() {
        std::cout << "\nDemonstrating temporary object and move semantics:"
                  << std::endl;
        Resource r =
            Resource("temp", 3); // Temporary that's immediately moved/optimized
        r.preview();
    }
};

// Class demonstrating inheriting constructors (C++11)
class DerivedResource : public Resource {
private:
    std::string description;

public:
    // Inherit base class constructors (C++11)
    using Resource::Resource;

    // Add a constructor that calls base class constructor
    DerivedResource(const std::string& n, size_t s, const std::string& desc)
        : Resource(n, s), description(desc) {
        std::cout << "Derived constructor: Added description \"" << description
                  << "\"" << std::endl;
    }

    void showDescription() const {
        std::cout << "Description: " << description << std::endl;
    }
};

// Class template with constructor
template <typename T>
class Container {
private:
    T value;

public:
    // Constructor template
    Container(const T& val) : value(val) {
        std::cout << "Template constructor: Created container" << std::endl;
    }

    void display() const {
        std::cout << "Container value: " << value << std::endl;
    }
};

// Class with constructor initialization order
class InitOrder {
private:
    int a;
    int b;
    int c;

public:
    // Note: Initialization order is determined by declaration order, not
    // initializer order
    InitOrder(int x, int y, int z) : c(z), a(x), b(y) {
        std::cout << "Initialization order: Values are a=" << a << ", b=" << b
                  << ", c=" << c << std::endl;
        std::cout << "  (Notice that despite c being initialized first in "
                     "list, members are initialized in declaration order)"
                  << std::endl;
    }
};

// Class with constexpr constructor (C++11)
class ConstValue {
private:
    int value;

public:
    constexpr ConstValue(int v) : value(v) {}

    constexpr int getValue() const { return value; }
};

// Perfect forwarding constructor example - moved outside of main()
class ForwardingExample {
public:
    template <typename... Args>
    ForwardingExample(Args&&... args) {
        std::cout << "Perfect forwarding constructor called with "
                  << sizeof...(args) << " arguments" << std::endl;
    }
};

int main() {
    std::cout << "=== COMPREHENSIVE CONSTRUCTOR DEMONSTRATION ===" << std::endl;

    std::cout << "\n1. Default constructor:" << std::endl;
    Resource r1;
    r1.preview();

    std::cout << "\n2. Parameterized constructor:" << std::endl;
    Resource r2("data", 5);
    r2.preview();

    std::cout << "\n3. Copy constructor:" << std::endl;
    Resource r3 = r2; // Copy constructor
    r3.preview();

    std::cout << "\n4. Move constructor:" << std::endl;
    Resource r4 = std::move(r1); // Move constructor
    r1.preview();                // r1 should be empty now
    r4.preview();

    std::cout << "\n5. Delegating constructor:" << std::endl;
    Resource r5("delegated");
    r5.preview();

    std::cout << "\n6. Initializer list constructor:" << std::endl;
    Resource r6 = {1, 2, 3, 4, 5}; // Uses initializer list constructor
    r6.preview();

    std::cout << "\n7. Implicit conversion constructor:" << std::endl;
    Resource r7 = 20; // Implicit conversion from int to Resource
    r7.preview();

    std::cout << "\n8. Explicit constructor (no implicit conversion):"
              << std::endl;
    // Resource r8 = 'A';  // This would error because the constructor is
    // explicit
    Resource r8(static_cast<char>('A')); // Must be explicit
    r8.preview();

    std::cout << "\n9. Return Value Optimization (RVO) and move semantics:"
              << std::endl;
    Resource r9 = r2.createAndMove("moved_resource", 3);
    r9.preview();

    Resource::demonstrate();

    std::cout << "\n10. Inheriting constructors (C++11):" << std::endl;
    DerivedResource dr1("derived", 3); // Uses inherited constructor
    dr1.preview();

    std::cout << "\n11. Derived class constructor:" << std::endl;
    DerivedResource dr2("derived_with_desc", 3, "Special resource");
    dr2.preview();
    dr2.showDescription();

    std::cout << "\n12. Template constructor:" << std::endl;
    Container<int> c1(42);
    c1.display();
    Container<std::string> c2("Hello");
    c2.display();

    std::cout << "\n13. Initialization order:" << std::endl;
    InitOrder io(1, 2, 3);

    std::cout << "\n14. Constexpr constructor (compile-time construction):"
              << std::endl;
    constexpr ConstValue cv(100);
    constexpr int compile_time_value = cv.getValue();
    std::cout << "Compile-time constructed value: " << compile_time_value
              << std::endl;

    std::cout << "\n15. Perfect forwarding constructor:" << std::endl;
    ForwardingExample fe1;
    ForwardingExample fe2(10, "text", 3.14);

    std::cout
        << "\n16. Placement new (constructor at specific memory location):"
        << std::endl;
    void* memory = operator new(sizeof(Resource));
    Resource* placed = new (memory) Resource("placement", 2);
    placed->preview();
    placed->~Resource(); // Must call destructor manually
    operator delete(memory);

    std::cout << "\n=== ALL OBJECTS WILL NOW BE DESTROYED ===" << std::endl;
    return 0;
}