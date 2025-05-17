#include <array>
#include <ranges>
#include <vector>
#include <iostream>

template <typename Container>
Container quickSort(const Container& container) {
    // 如果是空，返回空容器；否则...
    return std::ranges::empty(container)
            ? container
            : std::array<Container, 3>{
                    quickSort(container | std::views::drop(1) | std::views::filter([&](const auto &elem) {
                        return elem < *std::ranges::begin(container);
                    }) | std::ranges::to<Container>()),
                    std::views::single(*std::ranges::begin(container)) | std::ranges::to<Container>(),
                    quickSort(container | std::views::drop(1) | std::views::filter([&](const auto &elem) {
                        return elem >= *std::ranges::begin(container);
                    }) | std::ranges::to<Container>()),
                } | std::views::join | std::ranges::to<Container>();
}

int main() {
    std::vector<int> arr = {1, 4, 5, 9, 6, 7, 2, 8, 3, 0};
    arr = quickSort(arr);
    for (const auto& n : arr) {
        std::cout<< n << ' ';
    }
    std::cout << std::endl;
}