#include <iostream>
#include <numeric> // For std::views::iota
#include <ranges>
#include <vector>

int main() {
    std::cout << "--- std::views::filter example ---" << std::endl;
    std::vector<int> numbers_filter = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto even_numbers_view =
        numbers_filter | std::views::filter([](int n) { return n % 2 == 0; });

    std::cout << "Even numbers: ";
    for (int n : even_numbers_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    std::cout << "--- std::views::transform example ---" << std::endl;
    std::vector<int> numbers_transform = {1, 2, 3, 4, 5};

    auto squared_numbers_view =
        numbers_transform | std::views::transform([](int n) { return n * n; });

    std::cout << "Squared numbers: ";
    for (int n : squared_numbers_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------" << std::endl
              << std::endl;

    std::cout << "--- std::views::take example ---" << std::endl;
    std::vector<int> numbers_take = {10, 20, 30, 40, 50, 60};

    auto first_three_view = numbers_take | std::views::take(3);

    std::cout << "First three numbers: ";
    for (int n : first_three_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "--------------------------------" << std::endl << std::endl;

    std::cout << "--- std::views::drop example ---" << std::endl;
    std::vector<int> numbers_drop = {10, 20, 30, 40, 50, 60};

    auto after_three_view = numbers_drop | std::views::drop(3);

    std::cout << "Numbers after dropping first three: ";
    for (int n : after_three_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl << std::endl;

    std::cout << "--- std::views::reverse example ---" << std::endl;
    std::vector<int> numbers_reverse = {1, 2, 3, 4, 5};

    auto reversed_view = numbers_reverse | std::views::reverse;

    std::cout << "Reversed numbers: ";
    for (int n : reversed_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl
              << std::endl;

    std::cout << "--- std::views::iota example ---" << std::endl;
    auto sequence_view = std::views::iota(1, 6); // 生成 1, 2, 3, 4, 5

    std::cout << "Sequence from 1 to 5: ";
    for (int n : sequence_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 与其他适配器组合使用
    auto processed_sequence =
        std::views::iota(1) // 无限序列 1, 2, 3, ...
        | std::views::filter([](int n) { return n % 3 == 0; }) // 只保留3的倍数
        | std::views::take(4);                                 // 取前4个

    std::cout << "First 4 multiples of 3: ";
    for (int n : processed_sequence) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "--------------------------------" << std::endl << std::endl;

    std::cout << "--- Range Adaptors Combination example ---" << std::endl;
    std::vector<int> numbers_combination = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 过滤出偶数，将偶数平方，跳过前两个结果，然后取出接下来的两个结果
    auto pipeline_view = numbers_combination |
                         std::views::filter([](int n) { return n % 2 == 0; }) |
                         std::views::transform([](int n) { return n * n; }) |
                         std::views::drop(2) | std::views::take(2);

    std::cout << "Pipeline results: ";
    for (int n : pipeline_view) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------" << std::endl
              << std::endl;

    return 0;
}