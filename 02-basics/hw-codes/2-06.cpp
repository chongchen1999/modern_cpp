#include <stdexcept>
#include <vector>

template <typename T>
class Array3D {
private:
    size_t dim1, dim2, dim3; // 三个维度的尺寸
    std::vector<T> data;     // 使用一维vector存储数据

public:
    // 构造函数
    Array3D(size_t d1, size_t d2, size_t d3, const T& init_val = T())
        : dim1(d1), dim2(d2), dim3(d3), data(d1 * d2 * d3, init_val) {}

    // 拷贝构造函数（考虑了自赋值问题）
    Array3D(const Array3D& other)
        : dim1(other.dim1), dim2(other.dim2), dim3(other.dim3),
          data(other.data) {}

    // 拷贝赋值运算符（考虑了自赋值问题）
    Array3D& operator=(const Array3D& other) {
        if (this != &other) { // 检查自赋值
            dim1 = other.dim1;
            dim2 = other.dim2;
            dim3 = other.dim3;
            data = other.data;
        }
        return *this;
    }

    // 三维下标运算符访问
    T& operator()(size_t i, size_t j, size_t k) {
        check_index(i, j, k);
        return data[i * dim2 * dim3 + j * dim3 + k];
    }

    // 三维下标运算符访问（const版本）
    const T& operator()(size_t i, size_t j, size_t k) const {
        check_index(i, j, k);
        return data[i * dim2 * dim3 + j * dim3 + k];
    }

    // 获取各维度大小
    size_t size1() const { return dim1; }
    size_t size2() const { return dim2; }
    size_t size3() const { return dim3; }

private:
    // 检查索引是否有效
    void check_index(size_t i, size_t j, size_t k) const {
        if (i >= dim1 || j >= dim2 || k >= dim3) {
            throw std::out_of_range("Array3D index out of range");
        }
    }
};