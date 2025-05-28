#include <iostream>
#include <string>

class Distance {
private:
    double meters; // 内部统一用米存储

public:
    // 构造函数
    explicit Distance(double m) : meters(m) {}

    // 获取米
    double toMeters() const { return meters; }

    // 获取千米
    double toKilometers() const { return meters / 1000; }

    // 获取英里
    double toMiles() const { return meters / 1609.34; }

    // 重载加法运算符
    Distance operator+(const Distance& other) const {
        return Distance(meters + other.meters);
    }

    // 打印距离
    friend std::ostream& operator<<(std::ostream& os, const Distance& d) {
        os << d.meters << " m (" << d.toKilometers() << " km, " << d.toMiles()
           << " mi)";
        return os;
    }
};

// 用户定义字面量：米
Distance operator"" _m(long double x) {
    return Distance(static_cast<double>(x));
}

// 用户定义字面量：千米
Distance operator"" _km(long double x) {
    return Distance(static_cast<double>(x * 1000));
}

// 用户定义字面量：英里
Distance operator"" _mi(long double x) {
    return Distance(static_cast<double>(x * 1609.34));
}

int main() {
    // 使用字面量初始化距离
    auto d1 = 100.0_m; // 100米
    auto d2 = 2.5_km;  // 2.5千米
    auto d3 = 0.5_mi;  // 0.5英里

    // 距离加法运算
    auto total = d1 + d2 + d3;

    // 输出结果
    std::cout << "d1 = " << d1 << std::endl;
    std::cout << "d2 = " << d2 << std::endl;
    std::cout << "d3 = " << d3 << std::endl;
    std::cout << "Total distance = " << total << std::endl;

    return 0;
}