#include <bit>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <algorithm>

// 将二进制数据转换为网络字节序（大端序）
std::vector<uint8_t> convert_to_http_byte_order(const void* data, size_t size) {
    // 检查当前系统的字节序
    if constexpr (std::endian::native == std::endian::big) {
        // 大端系统，直接拷贝数据
        const uint8_t* byte_data = static_cast<const uint8_t*>(data);
        return std::vector<uint8_t>(byte_data, byte_data + size);
    } else if constexpr (std::endian::native == std::endian::little) {
        // 小端系统，需要反转多字节数据的字节序
        const uint8_t* byte_data = static_cast<const uint8_t*>(data);
        std::vector<uint8_t> result(byte_data, byte_data + size);

        // 对于多字节数据类型，反转字节序
        if (size > 1) {
            std::reverse(result.begin(), result.end());
        }

        return result;
    } else {
        // 未知字节序，打印警告并尝试处理
        std::cerr << "警告：未知的字节序，转换结果可能不正确！" << std::endl;

        // 保守处理：直接拷贝数据
        const uint8_t* byte_data = static_cast<const uint8_t*>(data);
        return std::vector<uint8_t>(byte_data, byte_data + size);
    }
}

// 模板版本，支持不同类型的数据
template <typename T>
std::vector<uint8_t> convert_to_http_byte_order(const T& value) {
    static_assert(std::is_trivially_copyable_v<T>, "类型必须是平凡可复制的");
    return convert_to_http_byte_order(&value, sizeof(T));
}

// 示例用法
int main() {
    uint32_t number = 0x12345678;

    auto http_bytes = convert_to_http_byte_order(number);

    std::cout << "转换后的字节序列（十六进制）：";
    for (auto byte : http_bytes) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    return 0;
}