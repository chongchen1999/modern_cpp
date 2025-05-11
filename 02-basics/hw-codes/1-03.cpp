#include <bit>
#include <cmath>
#include <cstdint>
#include <iostream>

float Q_rsqrt(float number, int iterations = 3) {
    uint32_t i = std::bit_cast<uint32_t>(number);
    i = 0x5f3759df - (i >> 1);
    float y = std::bit_cast<float>(i);

    for (int n = 0; n < iterations; ++n) {
        y = y * (1.5f - (number * 0.5f * y * y));
    }

    return y;
}

int main() {
    // 测试几个数值
    float test_values[] = {1.0f, 2.0f,  3.0f,   4.0f,    10.0f,   100.0f,
                           0.5f, 0.25f, 233.0f, 1000.0f, 4096.0f, 65536.0f};

    for (float x : test_values) {
        float fast_inv_sqrt = Q_rsqrt(x);
        float precise_inv_sqrt = 1.0f / std::sqrt(x);
        float error = std::abs(fast_inv_sqrt - precise_inv_sqrt) /
                      precise_inv_sqrt * 100.0f;

        std::cout << "x = " << x << ":\n";
        std::cout << "  Fast inverse sqrt: " << fast_inv_sqrt << "\n";
        std::cout << "  Precise inverse sqrt: " << precise_inv_sqrt << "\n";
        std::cout << "  Relative error: " << error << "%\n\n";
    }

    return 0;
}