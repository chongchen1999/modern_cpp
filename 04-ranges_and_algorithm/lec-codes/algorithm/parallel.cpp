#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <mutex>
#include <random>
#include <vector>

// Helper function to print execution time
template <typename Func>
void measure_time(const std::string& name, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << name << " took " << elapsed.count() << " seconds\n";
}

int main() {
    // Create a large vector of random numbers
    const size_t size = 10'000'000;
    std::vector<int> data(size);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    // Fill with random numbers (sequential)
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

    // Make copies for different sorting methods
    auto data_seq = data;
    auto data_par = data;
    auto data_par_unseq = data;

    // 1. Sequential sort
    measure_time("Sequential sort", [&]() {
        std::sort(std::execution::seq, data_seq.begin(), data_seq.end());
    });

    // 2. Parallel sort
    measure_time("Parallel sort", [&]() {
        std::sort(std::execution::par, data_par.begin(), data_par.end());
    });

    // 3. Parallel + vectorized sort
    measure_time("Parallel + vectorized sort", [&]() {
        std::sort(std::execution::par_unseq, data_par_unseq.begin(),
                  data_par_unseq.end());
    });

    // Verify all sorts produced the same result
    if (data_seq != data_par || data_seq != data_par_unseq) {
        std::cerr << "Sort results differ!\n";
        return 1;
    }

    // Example of parallel transform with mutex (parallel-safe but not
    // vectorization-safe)
    std::mutex mtx;
    std::vector<int> output(size);

    measure_time("Parallel transform with mutex", [&]() {
        std::transform(std::execution::par, data.begin(), data.end(),
                       output.begin(), [&](int x) {
                           std::lock_guard<std::mutex> lock(mtx);
                           return x * 2; // Simple operation protected by mutex
                       });
    });

    // Example of data dependencies
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // RAW (read after write) dependency - can't parallelize
    // for (size_t j = 1; j < vec.size(); ++j) {
    //     vec[j] = vec[j - 1] + 1; // Each element depends on previous
    // }

    // WAR (write after read) dependency - can vectorize but not parallelize
    // for (size_t j = 1; j < vec.size(); ++j) {
    //     vec[j - 1] = vec[j] + 1; // Each write depends on next read
    // }

    // RAR (read after read) - can parallelize and vectorize
    measure_time("Parallel adjacent_find (RAR)", [&]() {
        auto it =
            std::adjacent_find(std::execution::par, vec.begin(), vec.end(),
                               [](int a, int b) { return a == b; });
    });

    return 0;
}