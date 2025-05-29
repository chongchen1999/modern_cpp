#include <iostream>
#include <utility> // for std::exchange, std::swap
#include <vector>

// 使用std::exchange实现移动语义的类
class ResourceExchange {
    int* data;
    size_t size;

public:
    // 构造函数
    explicit ResourceExchange(size_t sz = 0)
        : data(sz ? new int[sz] : nullptr), size(sz) {
        std::cout << "ResourceExchange constructed, size = " << size << "\n";
    }

    // 析构函数
    ~ResourceExchange() {
        delete[] data;
        std::cout << "ResourceExchange destroyed, size = " << size << "\n";
    }

    // 拷贝构造函数
    ResourceExchange(const ResourceExchange& other)
        : data(other.size ? new int[other.size] : nullptr), size(other.size) {
        std::copy(other.data, other.data + size, data);
        std::cout << "ResourceExchange copied, size = " << size << "\n";
    }

    // 移动构造函数
    ResourceExchange(ResourceExchange&& other) noexcept
        : data(std::exchange(other.data, nullptr)),
          size(std::exchange(other.size, 0)) {
        std::cout << "ResourceExchange moved, size = " << size << "\n";
    }

    // 拷贝赋值运算符
    ResourceExchange& operator=(const ResourceExchange& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = size ? new int[size] : nullptr;
            std::copy(other.data, other.data + size, data);
            std::cout << "ResourceExchange copy assigned, size = " << size
                      << "\n";
        }
        return *this;
    }

    // 移动赋值运算符
    ResourceExchange& operator=(ResourceExchange&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            size = std::exchange(other.size, 0);
            std::cout << "ResourceExchange move assigned, size = " << size
                      << "\n";
        }
        return *this;
    }

    void fill(int value) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    void print() const {
        std::cout << "ResourceExchange content: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

// 使用copy-and-swap实现移动语义的类
class ResourceSwap {
    int* data;
    size_t size;

    void swap(ResourceSwap& other) noexcept {
        using std::swap;
        swap(data, other.data);
        swap(size, other.size);
    }

public:
    // 构造函数
    explicit ResourceSwap(size_t sz = 0)
        : data(sz ? new int[sz] : nullptr), size(sz) {
        std::cout << "ResourceSwap constructed, size = " << size << "\n";
    }

    // 析构函数
    ~ResourceSwap() {
        delete[] data;
        std::cout << "ResourceSwap destroyed, size = " << size << "\n";
    }

    // 拷贝构造函数
    ResourceSwap(const ResourceSwap& other) : data(nullptr), size(0) {
        if (other.size > 0) {
            data = new int[other.size];
            size = other.size;
            std::copy(other.data, other.data + size, data);
        }
        std::cout << "ResourceSwap copied, size = " << size << "\n";
    }

    // 移动构造函数
    ResourceSwap(ResourceSwap&& other) noexcept : data(nullptr), size(0) {
        swap(other);
        std::cout << "ResourceSwap moved, size = " << size << "\n";
    }

    // 统一赋值运算符（处理拷贝和移动）
    ResourceSwap& operator=(ResourceSwap other) noexcept {
        swap(other);
        std::cout << "ResourceSwap assigned, size = " << size << "\n";
        return *this;
    }

    void fill(int value) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    void print() const {
        std::cout << "ResourceSwap content: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

// 测试函数
void test_movement() {
    std::cout << "\n=== Testing ResourceExchange ===\n";
    {
        ResourceExchange a(5);
        a.fill(10);
        a.print();

        // 移动构造
        ResourceExchange b(std::move(a));
        b.print();

        // 移动赋值
        ResourceExchange c(3);
        c = std::move(b);
        c.print();
    }

    std::cout << "\n=== Testing ResourceSwap ===\n";
    {
        ResourceSwap x(4);
        x.fill(20);
        x.print();

        // 移动构造
        ResourceSwap y(std::move(x));
        y.print();

        // 移动赋值
        ResourceSwap z(2);
        z = std::move(y);
        z.print();

        // 拷贝赋值
        ResourceSwap w(z);
        w.print();
    }

    std::cout << "\n=== Testing with STL containers ===\n";
    {
        std::vector<ResourceExchange> vec;
        vec.reserve(3);

        std::cout << "--- Emplacing back ---\n";
        vec.emplace_back(2); // 直接构造在容器中

        std::cout << "--- Pushing back temporary ---\n";
        vec.push_back(ResourceExchange(3)); // 移动构造

        std::cout << "--- Pushing back lvalue ---\n";
        ResourceExchange tmp(4);
        vec.push_back(tmp); // 拷贝构造
    }
}

int main() {
    test_movement();
    return 0;
}