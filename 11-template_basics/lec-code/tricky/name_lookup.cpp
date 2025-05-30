#include <functional>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 示例1: 依赖基类成员访问 - this-> 的必要性
// ============================================================================

template <typename T>
class Base {
protected:
    T data;
    std::string name;

public:
    Base() : data{}, name("base") {}

    void show() { std::cout << "Base::show() - name: " << name << std::endl; }

    void setData(const T& value) { data = value; }

    T getData() const { return data; }
};

template <typename T>
class Derived : public Base<T> {
public:
    void demonstrateLookup() {
        std::cout << "\n=== 示例1: 依赖基类成员访问 ===\n";

        // 错误写法 (编译失败):
        // show();        // Error! 编译器找不到show
        // name = "test"; // Error! 编译器找不到name

        // 正确写法1: 使用 this->
        this->show();
        this->name = "derived_this";
        this->setData(T{});

        // 正确写法2: 使用基类限定符
        Base<T>::show();

        // 正确写法3: 直接调用基类函数
        T value = this->getData();

        std::cout << "成功访问基类成员!\n";
    }

    // using声明需要在类作用域，不能在函数内
    using Base<T>::getData;
};

// ============================================================================
// 示例2: typename关键字 - 消除类型歧义
// ============================================================================

template <typename Container>
class ContainerHelper {
public:
    // 错误写法:
    // Container::iterator it;  // Error! 编译器不知道iterator是类型还是成员

    // 正确写法: 使用typename声明这是类型
    using iterator_type = typename Container::iterator;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;

    void processContainer(Container& container) {
        std::cout << "\n=== 示例2: typename关键字 ===\n";
        std::cout << "容器大小: " << container.size() << std::endl;

        // 在函数内使用dependent type
        typename Container::iterator it = container.begin();
        typename Container::iterator end = container.end();

        std::cout << "容器元素: ";
        for (; it != end; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    // 返回类型使用typename
    typename Container::value_type getFirst(const Container& container) {
        if (!container.empty()) {
            return container.front();
        }
        return typename Container::value_type{};
    }

    // 模板参数中使用typename
    template <typename Predicate>
    size_type countIf(const Container& container, Predicate pred) {
        typename Container::size_type count = 0;
        for (const auto& elem : container) {
            if (pred(elem)) {
                ++count;
            }
        }
        return count;
    }
};

// ============================================================================
// 示例3: template关键字 - 消除模板调用歧义
// ============================================================================

template <typename T>
class TemplateClass {
public:
    // 成员模板函数
    template <int N>
    void repeat(const T& value) {
        std::cout << "重复 " << N << " 次: ";
        for (int i = 0; i < N; ++i) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    template <typename U>
    void convert(const U& input) {
        // 只对兼容类型进行转换
        if constexpr (std::is_arithmetic_v<U> && std::is_arithmetic_v<T>) {
            T result = static_cast<T>(input);
            std::cout << "数值转换: " << input << " -> " << result << std::endl;
        } else if constexpr (std::is_same_v<U, T>) {
            std::cout << "相同类型: " << input << std::endl;
        } else {
            std::cout << "类型转换演示 (输入类型与目标类型不兼容)" << std::endl;
        }
    }

    // 嵌套模板结构
    template <typename U>
    struct Helper {
        static void process(const T& t, const U& u) {
            std::cout << "Helper处理: " << t << ", " << u << std::endl;
        }

        template <int Count>
        static void repeatProcess(const T& value) {
            for (int i = 0; i < Count; ++i) {
                std::cout << "[" << i << "] " << value << std::endl;
            }
        }
    };
};

template <typename T>
class TemplateManager {
public:
    void demonstrateTemplate(TemplateClass<T>& obj, const T& value) {
        std::cout << "\n=== 示例3: template关键字 ===\n";

        // 直接调用可能有歧义 (某些编译器可能解析为比较操作):
        // obj.repeat<3>(value);  // 可能被解析为: (obj.repeat < 3) > (value)

        // 正确写法: 使用template关键字
        obj.template repeat<3>(value);
        obj.template convert<int>(42); // 使用int而不是double避免string转换问题

        // 通过指针访问
        TemplateClass<T>* ptr = &obj;
        ptr->template repeat<2>(value);

        // 访问嵌套模板的静态成员
        TemplateClass<T>::template Helper<std::string>::process(value,
                                                                "helper");

        // 调用嵌套模板的模板方法
        TemplateClass<T>::template Helper<int>::template repeatProcess<2>(
            value);
    }
};

// ============================================================================
// 主函数 - 演示所有示例
// ============================================================================

int main() {
    std::cout << "=== C++ 两阶段名称查找机制演示 ===\n";

    // 示例1: 依赖基类成员访问
    Derived<int> derived;
    derived.demonstrateLookup();

    // 示例2: typename关键字
    std::vector<int> vec = {1, 2, 3, 4, 5};
    ContainerHelper<std::vector<int>> helper;
    helper.processContainer(vec);

    auto first = helper.getFirst(vec);
    std::cout << "第一个元素: " << first << std::endl;

    auto count = helper.countIf(vec, [](int x) { return x > 3; });
    std::cout << "大于3的元素个数: " << count << std::endl;

    // 示例3: template关键字
    TemplateClass<std::string> templateObj;
    TemplateManager<std::string> manager;
    manager.demonstrateTemplate(templateObj, std::string("Hello"));

    std::cout << "\n=== 演示完成 ===\n";
    return 0;
}