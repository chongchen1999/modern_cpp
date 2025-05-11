#include <algorithm>
#include <iostream>
#include <vector>

// 定义结构体
struct DijkstraInfo {
    int vertexID;
    int distance; // 作为比较的标准
};

// C++23 支持 static operator() 的仿函数
template <typename T>
struct CompareDistanceStatic {
    static bool operator()(const T& a, const T& b) {
        return a.distance < b.distance;
    }
};

// 传统仿函数（无 static operator()）
template <typename T>
struct CompareDistance {
    bool operator()(const T& a, const T& b) const {
        return a.distance < b.distance;
    }
};

// 普通函数模板（不能直接用于 sort，需要实例化）
template <typename T>
bool Func(const T& a, const T& b) {
    return a.distance < b.distance;
}

int main() {
    std::vector<DijkstraInfo> vec = {{1, 5}, {2, 3}, {3, 7}, {4, 1}};

    // 1. 使用 lambda 表达式排序（推荐）
    std::ranges::sort(vec, [](const auto& a, const auto& b) {
        return a.distance < b.distance;
    });

    std::cout << "After lambda sort:\n";
    for (const auto& x : vec) {
        std::cout << "vertexID=" << x.vertexID << ", distance=" << x.distance
                  << "\n";
    }

    // 2. 使用 static operator() 仿函数（C++23）
    std::ranges::sort(vec, CompareDistanceStatic<DijkstraInfo>::operator());

    std::cout << "\nAfter static operator() sort:\n";
    for (const auto& x : vec) {
        std::cout << "vertexID=" << x.vertexID << ", distance=" << x.distance
                  << "\n";
    }

    // 3. 使用普通仿函数（传统方式）
    std::ranges::sort(vec, CompareDistance<DijkstraInfo>{});

    std::cout << "\nAfter functor sort:\n";
    for (const auto& x : vec) {
        std::cout << "vertexID=" << x.vertexID << ", distance=" << x.distance
                  << "\n";
    }

    // 4. 使用普通函数模板（需要显式实例化）
    std::ranges::sort(vec, Func<DijkstraInfo>); // 如果 Func 是模板函数

    return 0;
}