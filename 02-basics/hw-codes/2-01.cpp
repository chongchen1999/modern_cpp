#include <algorithm>
#include <cassert>
#include <cmath>
#include <compare>
#include <iostream>

class Vector3 {
private:
    float x, y, z;

public:
    // Constructors using uniform initialization
    Vector3() : x{0.0f}, y{0.0f}, z{0.0f} {}
    explicit Vector3(float x_, float y_ = 0.0f, float z_ = 0.0f)
        : x{x_}, y{y_}, z{z_} {}

    // Accessors
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Length calculation
    [[nodiscard]] float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Addition operators (as member functions)
    [[nodiscard]] Vector3 operator+(const Vector3& rhs) const {
        return Vector3{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vector3& operator+=(const Vector3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    // Comparison operators (using spaceship operator for C++20)
    [[nodiscard]] auto operator<=>(const Vector3& rhs) const {
        return length() <=> rhs.length();
    }

    [[nodiscard]] bool operator==(const Vector3& rhs) const {
        return length() == rhs.length();
    }

    // For printing
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

// Global operator+ to allow 1 + a
[[nodiscard]] Vector3 operator+(float lhs, const Vector3& rhs) {
    return Vector3{lhs} + rhs;
}

// Warning attributes for operators that shouldn't have their result discarded
[[nodiscard]] Vector3 operator+(const Vector3& lhs, float rhs) {
    return lhs + Vector3{rhs};
}

// Test functions using uniform initialization
void test_initialization() {
    std::cout << "Testing initialization...\n";
    Vector3 v1{};
    Vector3 v2{1.0f};
    Vector3 v3{1.0f, 2.0f};
    Vector3 v4{1.0f, 2.0f, 3.0f};

    assert(v1.getX() == 0.0f && v1.getY() == 0.0f && v1.getZ() == 0.0f);
    assert(v2.getX() == 1.0f && v2.getY() == 0.0f && v2.getZ() == 0.0f);
    assert(v3.getX() == 1.0f && v3.getY() == 2.0f && v3.getZ() == 0.0f);
    assert(v4.getX() == 1.0f && v4.getY() == 2.0f && v4.getZ() == 3.0f);

    std::cout << "Initialization tests passed!\n\n";
}

void test_addition() {
    std::cout << "Testing addition...\n";
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2{4.0f, 5.0f, 6.0f};

    // Member operator+
    Vector3 sum1 = v1 + v2;
    assert(sum1.getX() == 5.0f && sum1.getY() == 7.0f && sum1.getZ() == 9.0f);

    // operator+=
    v1 += v2;
    assert(v1.getX() == 5.0f && v1.getY() == 7.0f && v1.getZ() == 9.0f);

    // Global operator+ with float
    Vector3 sum2 = v2 + 1.0f;
    assert(sum2.getX() == 5.0f && sum2.getY() == 5.0f && sum2.getZ() == 6.0f);

    // Global operator+ with float (left side)
    Vector3 sum3 = 1.0f + v2;
    assert(sum3.getX() == 5.0f && sum3.getY() == 5.0f && sum3.getZ() == 6.0f);

    // Test explicit constructor behavior
    // Vector3 sum4 = 1 + v2; // This won't compile (good!)
    Vector3 sum4 = Vector3{1.0f} + v2; // This works
    assert(sum4.getX() == 5.0f && sum4.getY() == 5.0f && sum4.getZ() == 6.0f);

    std::cout << "Addition tests passed!\n\n";
}

void test_comparison() {
    std::cout << "Testing comparison...\n";
    Vector3 short_vec{1.0f, 0.0f, 0.0f};  // length = 1
    Vector3 medium_vec{1.0f, 1.0f, 0.0f}; // length ≈ 1.414
    Vector3 long_vec{1.0f, 1.0f, 1.0f};   // length ≈ 1.732

    // Test all comparison operators
    assert(short_vec < medium_vec);
    assert(short_vec <= medium_vec);
    assert(medium_vec > short_vec);
    assert(medium_vec >= short_vec);
    assert(short_vec != medium_vec);
    assert(short_vec == (Vector3{1.0f, 0.0f, 0.0f}));

    assert(medium_vec < long_vec);
    assert(medium_vec <= long_vec);
    assert(long_vec > medium_vec);
    assert(long_vec >= medium_vec);
    assert(medium_vec != long_vec);

    std::cout << "Comparison tests passed!\n\n";
}

void test_length() {
    std::cout << "Testing length calculation...\n";
    Vector3 v1{3.0f, 4.0f, 0.0f};
    assert(v1.length() == 5.0f);

    Vector3 v2{1.0f, 1.0f, 1.0f};
    float expected = std::sqrt(3.0f);
    assert(std::abs(v2.length() - expected) < 0.0001f);

    Vector3 v3{0.0f, 0.0f, 0.0f};
    assert(v3.length() == 0.0f);

    std::cout << "Length tests passed!\n\n";
}

void test_nodiscard() {
    std::cout << "Testing [[nodiscard]] behavior...\n";
    Vector3 v1{1.0f, 2.0f, 3.0f};
    Vector3 v2{4.0f, 5.0f, 6.0f};

    // These will compile but may trigger warnings
    // v1 + v2;        // [[nodiscard]] should warn
    // v1.length();    // [[nodiscard]] should warn

    // These are fine because we use the results
    [[maybe_unused]] auto sum = v1 + v2;
    [[maybe_unused]] auto len = v1.length();

    std::cout << "[[nodiscard]] tests passed (check compiler warnings)\n\n";
}

int main() {
    test_initialization();
    test_addition();
    test_comparison();
    test_length();
    test_nodiscard();

    std::cout << "All tests passed successfully!\n";
    return 0;
}