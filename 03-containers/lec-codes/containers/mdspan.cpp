#include <array>
#include <iostream>
#include <mdspan>
#include <numeric> // for iota
#include <vector>

// 辅助函数：打印mdspan内容
template <typename T, typename Extents, typename Layout, typename Accessor>
void print_mdspan(std::string_view name,
                  std::mdspan<T, Extents, Layout, Accessor> m) {
    std::cout << name << " (" << m.extent(0);
    for (size_t i = 1; i < m.rank(); ++i) {
        std::cout << "x" << m.extent(i);
    }
    std::cout << "):\n";

    for (size_t i = 0; i < m.extent(0); ++i) {
        for (size_t j = 0; j < m.extent(1); ++j) {
            std::cout << m(i, j) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    // 1. 基本用法 - 创建2D视图
    {
        std::vector<int> data(12);
        std::iota(data.begin(), data.end(), 1); // 填充1-12

        // 创建3x4的mdspan视图
        std::mdspan mat2d(data.data(), 3, 4);
        print_mdspan("Basic 3x4 matrix", mat2d);

        // 修改元素
        mat2d(1, 2) = 99;
        std::cout << "After modification: mat2d(1,2) = " << mat2d(1, 2)
                  << "\n\n";
    }

    // 2. 不同布局策略
    {
        std::vector<int> data(6);
        std::iota(data.begin(), data.end(), 1);

        // 行主序(默认，C风格)
        std::mdspan<int, std::extents<int, 2, 3>, std::layout_right> row_major(
            data.data());
        print_mdspan("Row-major (C-style) layout", row_major);

        // 列主序(Fortran风格)
        std::mdspan<int, std::extents<int, 2, 3>, std::layout_left> col_major(
            data.data());
        print_mdspan("Column-major (Fortran-style) layout", col_major);

        // 自定义跨步
        std::array strides{2, 1}; // 第一维跨步2，第二维跨步1
        std::mdspan<int, std::extents<int, 2, 3>, std::layout_stride>
            custom_stride(data.data(), strides);
        print_mdspan("Custom stride layout", custom_stride);
    }

    // 3. 静态与动态维度混合
    {
        std::vector<double> data(8);
        std::iota(data.begin(), data.end(), 1.0);

        // 完全动态维度
        std::mdspan<double, std::dextents<int, 2>> fully_dynamic(data.data(), 2,
                                                                 4);
        print_mdspan("Fully dynamic (2x4)", fully_dynamic);

        // 静态行数(2)，动态列数
        std::mdspan<double, std::extents<int, 2, std::dynamic_extent>>
            mixed_static_dynamic(data.data(), 4);
        print_mdspan("Mixed static/dynamic (static 2 rows, dynamic columns)",
                     mixed_static_dynamic);

        // 完全静态维度
        std::mdspan<double, std::extents<int, 2, 4>> fully_static(data.data());
        print_mdspan("Fully static (2x4)", fully_static);
    }

    // 4. 3D数组示例
    {
        std::vector<int> data(24);
        std::iota(data.begin(), data.end(), 1);

        // 创建2x3x4的3D视图
        std::mdspan mat3d(data.data(), 2, 3, 4);

        std::cout << "3D array (2x3x4):\n";
        for (int i = 0; i < mat3d.extent(0); ++i) {
            std::cout << "Slice " << i << ":\n";
            for (int j = 0; j < mat3d.extent(1); ++j) {
                for (int k = 0; k < mat3d.extent(2); ++k) {
                    std::cout << mat3d(i, j, k) << "\t";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }

    // 5. 子视图和切片
    {
        std::vector<int> data(16);
        std::iota(data.begin(), data.end(), 1);
        std::mdspan mat(data.data(), 4, 4);

        // 获取第2行的子视图
        auto row2 = std::submdspan(mat, 1, std::full_extent);
        std::cout << "\nRow 2: ";
        for (size_t i = 0; i < row2.extent(0); ++i) {
            std::cout << row2[i] << " ";
        }
        std::cout << "\n";

        // 获取第3列的子视图
        auto col3 = std::submdspan(mat, std::full_extent, 2);
        std::cout << "Column 3: ";
        for (size_t i = 0; i < col3.extent(0); ++i) {
            std::cout << col3[i] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}