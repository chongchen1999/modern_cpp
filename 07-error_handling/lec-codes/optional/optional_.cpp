#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

// 模拟用户数据库
struct User {
    int id;
    std::string name;
    int age;
};

// 数据库查询函数：可能返回用户或找不到（std::nullopt）
std::optional<User> findUserById(const std::vector<User>& users, int id) {
    for (const auto& user : users) {
        if (user.id == id) {
            return user; // 找到用户，返回包含值的 optional
        }
    }
    return std::nullopt; // 未找到用户，返回无值的 optional
}

template <typename T>
void demonstrate_hash_consistency(const T& value) {
    std::optional<T> opt = value;

    // 计算哈希值
    size_t hash_optional = std::hash<std::optional<T>>{}(opt);
    size_t hash_direct = std::hash<T>{}(value);
    size_t hash_variant;

    if constexpr (std::is_same_v<T, std::string>) {
        std::variant<int, std::string> var = value;
        hash_variant = std::hash<std::variant<int, std::string>>{}(var);
    } else {
        std::variant<T, std::string> var = value;
        hash_variant = std::hash<std::variant<T, std::string>>{}(var);
    }

    // 打印结果
    std::cout << "Value: " << value << "\n";
    std::cout << "std::hash<std::optional<T>>: " << hash_optional << "\n";
    std::cout << "std::hash<T> (direct):       " << hash_direct << "\n";
    std::cout << "std::hash<std::variant<...>>: " << hash_variant << "\n";

    // 验证一致性
    if (hash_optional == hash_direct) {
        std::cout << "✅ std::optional hash matches std::hash<T>\n";
    } else {
        std::cout << "❌ std::optional hash does NOT match std::hash<T>\n";
    }

    if (hash_variant == hash_direct) {
        std::cout << "✅ std::variant hash matches std::hash<T> "
                     "(implementation-dependent)\n";
    } else {
        std::cout
            << "❌ std::variant hash does NOT match std::hash<T> (expected)\n";
    }
    std::cout << "---\n";
}

int main() {
    // 模拟数据库
    std::vector<User> users = {
        {1, "Alice", 25}, {2, "Bob", 30}, {3, "Charlie", 22}};

    // 场景1：查询存在的用户
    std::optional<User> result1 = findUserById(users, 2);
    if (result1) { // 检查是否有值
        std::cout << "Found user: " << result1->name
                  << ", Age: " << result1->age << std::endl;
    } else {
        std::cout << "User not found!" << std::endl;
    }

    // 场景2：查询不存在的用户
    auto result2 = findUserById(users, 99);
    if (result2.has_value()) { // 另一种检查方式
        std::cout << "Found user: " << result2->name << std::endl;
    } else {
        std::cout << "User 99 does not exist." << std::endl;
    }

    // 场景3：使用 value_or 提供默认值
    auto result3 = findUserById(users, 3);
    User defaultUser = {-1, "Unknown", 0};
    User user =
        result3.value_or(defaultUser); // 有值返回值，无值返回 defaultUser
    std::cout << "User 3 or default: " << user.name << std::endl;

    // 场景4：直接解引用（需确保有值，否则未定义行为）
    if (result1) {
        std::cout << "User 2's name (via *): " << (*result1).name << std::endl;
    }

    // 场景5：修改 optional 的值
    std::optional<int> optNumber = 42;
    std::cout << "Original number: " << *optNumber << std::endl;
    optNumber = 100;   // 重新赋值
    optNumber.reset(); // 重置为无值状态
    if (!optNumber) {
        std::cout << "Number is now empty." << std::endl;
    }

    demonstrate_hash_consistency(42);
    demonstrate_hash_consistency(3.14);
    demonstrate_hash_consistency(std::string("hello"));

    // 空 optional 的哈希
    std::optional<int> empty_opt;
    std::cout << "Hash of empty optional: "
              << std::hash<std::optional<int>>{}(empty_opt) << "\n";

    return 0;
}