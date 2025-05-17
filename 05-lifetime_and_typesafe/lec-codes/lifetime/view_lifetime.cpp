#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// 示例：返回一个基于 lvalue 的 View（危险！悬空引用）
auto getDanglingView() {
    std::vector<int> local_vec = {1, 2, 3};
    return local_vec |
           std::views::reverse; // 返回 ref_view，但 local_vec 即将销毁！
}

// 示例：返回一个基于 rvalue 的 View（安全，owning_view 持有数据）
auto getSafeView() {
    return std::vector<int>{4, 5, 6} | std::views::reverse; // 返回 owning_view
}

// 示例：显式使用 stdv::all 观察不同范围的 View 类型
void demonstrateViewTypes() {
    std::vector<int> lvalue_vec = {7, 8, 9};

    // 1. 对 lvalue 使用 stdv::all -> 生成 ref_view（依赖外部生命周期）
    auto ref_view = lvalue_vec | std::views::all;
    std::cout << "ref_view type: " << typeid(ref_view).name() << "\n";

    // 2. 对 rvalue 使用 stdv::all -> 生成 owning_view（内部持有数据）
    auto owning_view = std::vector<int>{10, 11, 12} | std::views::all;
    std::cout << "owning_view type: " << typeid(owning_view).name() << "\n";

    // 3. 直接传递 View -> 无操作（原样返回）
    auto pass_view = ref_view | std::views::all;
    std::cout << "pass_view type: " << typeid(pass_view).name() << "\n";
}

int main() {
    // 案例 1：悬空的 View（未定义行为！）
    // auto bad_view = getDanglingView();
    // for (int x : bad_view) { std::cout << x << " "; } // UB：访问已销毁的
    // local_vec

    // 案例 2：安全的 View（owning_view 持有数据）
    auto safe_view = getSafeView();
    std::cout << "Safe view (rvalue): ";
    for (int x : safe_view) {
        std::cout << x << " ";
    } // 输出: 6 5 4
    std::cout << "\n";

    // 案例 3：显式观察 View 类型和生命周期
    demonstrateViewTypes();

    // 案例 4：std::move 转换 lvalue 为 rvalue，生成 owning_view
    std::vector<int> vec = {13, 14, 15};
    auto moved_view =
        std::move(vec) |
        std::views::reverse; // vec 被“掏空”，数据由 owning_view 持有
    std::cout << "Moved view: ";
    for (int x : moved_view) {
        std::cout << x << " ";
    } // 输出: 15 14 13
    std::cout << "\n";
    std::cout << "Original vec size after move: " << vec.size()
              << "\n"; // 输出: 0
}