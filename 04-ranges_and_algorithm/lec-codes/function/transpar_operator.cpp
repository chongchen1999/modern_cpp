#include <algorithm>  // for std::lexicographical_compare
#include <cctype>     // for std::tolower
#include <cstring>    // for std::strlen
#include <functional> // for std::less<>
#include <iostream>
#include <set>
#include <string>

// 自定义透明比较器
struct CaseInsensitiveCompare {
    // 标记为透明操作符
    using is_transparent = void;

    template <typename T1, typename T2>
    bool operator()(const T1& a, const T2& b) const {
        // 获取字符串的起始和结束迭代器
        auto get_range = [](const auto& s) {
            if constexpr (std::is_same_v<std::decay_t<decltype(s)>,
                                         std::string>) {
                return std::pair(s.begin(), s.end());
            } else if constexpr (std::is_same_v<std::decay_t<decltype(s)>,
                                                const char*>) {
                return std::pair(s, s + std::strlen(s));
            } else {
                static_assert(false, "Unsupported type");
            }
        };

        auto [a_begin, a_end] = get_range(a);
        auto [b_begin, b_end] = get_range(b);

        // 不区分大小写的比较
        return std::lexicographical_compare(
            a_begin, a_end, b_begin, b_end, [](char c1, char c2) {
                return std::tolower(c1) < std::tolower(c2);
            });
    }
};

int main() {
    // 使用自定义透明比较器的 set
    std::set<std::string, CaseInsensitiveCompare> words = {"Apple", "Banana",
                                                           "Cherry"};

    // 直接使用 const char* 查找（无需构造临时 std::string）
    const char* searchWord = "apple";
    auto it = words.find(searchWord);

    if (it != words.end()) {
        std::cout << "Found: " << *it << std::endl; // 输出 "Found: Apple"
    } else {
        std::cout << "Not found!" << std::endl;
    }

    // 使用标准库的透明操作符 std::less<>
    std::set<std::string, std::less<>> transparentSet = {"Hello", "World"};
    auto it2 = transparentSet.find("hello"); // 直接传递 const char*

    if (it2 != transparentSet.end()) {
        std::cout << "Found in transparentSet: " << *it2 << std::endl;
    } else {
        std::cout << "Not found in transparentSet!" << std::endl;
    }

    return 0;
}