#include <cstdio>
#include <stdfloat>  // C++23 feature
#include <type_traits>

int main() {
    // Standardized fixed-width floating-point types
    std::float16_t f16 = 1.234f16;   // 16-bit floating point (binary16)
    std::float32_t f32 = 5.678f32;   // 32-bit floating point (binary32, like float)
    std::float64_t f64 = 9.1011f64;  // 64-bit floating point (binary64, like double)
    std::float128_t f128 = 1.23456789f128;  // 128-bit floating point (binary128)
    
    // Output the values using printf
    printf("float16_t: %f\n", (double)f16);
    printf("float32_t: %f\n", (double)f32);
    printf("float64_t: %f\n", (double)f64);
    printf("float128_t: %Lf\n", (long double)f128);  // Note: float128_t may need special handling
    
    // Output sizes
    printf("\nSizes in bytes:\n");
    printf("float16_t: %zu\n", sizeof(f16));
    printf("float32_t: %zu\n", sizeof(f32));
    printf("float64_t: %zu\n", sizeof(f64));
    printf("float128_t: %zu\n", sizeof(f128));

    if constexpr (std::is_same_v<std::float64_t, double>) {
        printf("std::float64_t is an alias for double on this platform.\n");
    } else {
        printf("std::float64_t is NOT an alias for double on this platform.\n");
    }
    
    return 0;
}