#include <iostream>
#include <type_traits>

// Primary template
template <typename T, int N = 0, typename Enable = void>
class MyContainer {
public:
    void print() {
        std::cout << "Primary template: T=" << typeid(T).name() 
                  << ", N=" << N << std::endl;
    }
};

// Full specialization for T=int, N=10
template <>
class MyContainer<int, 10> {
public:
    void print() {
        std::cout << "Full specialization for int, 10" << std::endl;
    }
};

// Partial specialization for pointer types
template <typename T, int N>
class MyContainer<T*, N> {
public:
    void print() {
        std::cout << "Partial specialization for pointer: T*=" 
                  << typeid(T).name() << ", N=" << N << std::endl;
    }
};

// Partial specialization for arrays (Note1: no default parameter allowed)
template <typename T, int N>
class MyContainer<T[N], 0> {  // Note: No default parameter here
public:
    void print() {
        std::cout << "Partial specialization for array: T[]=" 
                  << typeid(T).name() << "[" << N << "]" << std::endl;
    }
};

// Partial specialization using enable_if (SFINAE)
template <typename T, int N>
class MyContainer<T, N, std::enable_if_t<std::is_floating_point_v<T>>> {
public:
    void print() {
        std::cout << "Partial specialization for floating point: T=" 
                  << typeid(T).name() << ", N=" << N << std::endl;
    }
};

// Class with internal partial specialization
template <typename T>
class Outer {
public:
    // Primary template inside class
    template <typename U, int N>
    class Inner {
    public:
        void print() {
            std::cout << "Outer<T>::Inner<U,N> primary template" << std::endl;
        }
    };
    
    // Partial specialization inside class (Note4)
    template <typename U>
    class Inner<U, 0> {
    public:
        void print() {
            std::cout << "Outer<T>::Inner<U,0> partial specialization" << std::endl;
        }
    };
};

// Variable template (Note3)
template <typename T>
constexpr bool is_pointer_v = false;

template <typename T>
constexpr bool is_pointer_v<T*> = true;

int main() {
    // // Test primary template
    // MyContainer<char, 5> c1;
    // c1.print();
    
    // // Test full specialization
    // MyContainer<int, 10> c2;
    // c2.print();
    
    // // Test pointer partial specialization
    // MyContainer<double*, 3> c3;
    // c3.print();
    
    // Test array partial specialization
    MyContainer<int[5]> c4;
    c4.print();
    
    // Test SFINAE partial specialization
    MyContainer<float, 2> c5;
    c5.print();
    
    // Test nested partial specialization
    Outer<int>::Inner<double, 1> i1;
    i1.print();
    
    Outer<int>::Inner<double, 0> i2;
    i2.print();
    
    // Test variable template specialization
    std::cout << "is_pointer_v<int> = " << is_pointer_v<int> << std::endl;
    std::cout << "is_pointer_v<int*> = " << is_pointer_v<int*> << std::endl;
    
    return 0;
}