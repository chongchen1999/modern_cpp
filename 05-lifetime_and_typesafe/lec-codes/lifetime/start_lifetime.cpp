#include <cstring>
#include <iostream>
#include <memory> // For std::start_lifetime_as and std::start_lifetime_as_array


// 示例结构体
struct Point {
    int x;
    int y;

    void print() const { std::cout << "Point(" << x << ", " << y << ")\n"; }
};

int main() {
    // ----------------------------
    // 1. 使用 std::start_lifetime_as
    // ----------------------------
    {
        // 分配对齐的内存缓冲区（足够存储一个 Point 对象）
        alignas(Point) unsigned char buffer[sizeof(Point)];

        // 模拟一个 Point 对象的二进制表示
        Point original{10, 20};
        std::memcpy(buffer, &original, sizeof(Point));

        // 显式开始对象的生命周期
        Point* p = std::start_lifetime_as<Point>(buffer);

        // 安全访问对象
        p->print(); // 输出: Point(10, 20)

        // 修改对象
        p->x = 30;
        p->print(); // 输出: Point(30, 20)
    }

    // ----------------------------
    // 2. 使用 std::start_lifetime_as_array
    // ----------------------------
    {
        constexpr size_t array_size = 3;

        // 分配对齐的内存缓冲区（足够存储 3 个 int）
        alignas(int) unsigned char buffer[sizeof(int) * array_size];

        // 模拟一个 int 数组的二进制表示
        int original_array[array_size] = {1, 2, 3};
        std::memcpy(buffer, original_array, sizeof(int) * array_size);

        // 显式开始数组的生命周期
        int* arr = std::start_lifetime_as_array<int>(buffer, array_size);

        // 安全访问数组
        std::cout << "Array: ";
        for (size_t i = 0; i < array_size; ++i) {
            std::cout << arr[i] << " "; // 输出: 1 2 3
        }
        std::cout << "\n";

        // 修改数组
        arr[1] = 99;
        std::cout << "Modified array: ";
        for (size_t i = 0; i < array_size; ++i) {
            std::cout << arr[i] << " "; // 输出: 1 99 3
        }
        std::cout << "\n";
    }

    return 0;
}