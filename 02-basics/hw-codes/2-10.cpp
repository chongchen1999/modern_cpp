#include <functional>
#include <iostream>
#include <memory>

// Mock Device (CPU version doesn't need device management)
struct Device {
    int index = 0; // CPU is always device 0 in this context
};

struct DataPtr {
    void* ptr;
    Device device;
};

// Mock NDArrayStorage
class NDArrayStorage {
public:
    NDArrayStorage(DataPtr data_ptr, size_t size)
        : data_ptr_(data_ptr), size_(size) {
        std::cout << "NDArrayStorage created with size " << size << std::endl;
    }

    ~NDArrayStorage() { std::cout << "NDArrayStorage destroyed" << std::endl; }

private:
    DataPtr data_ptr_;
    size_t size_;
};

// CPU version doesn't need device guard
class DeviceGuard {
public:
    DeviceGuard(int /*device_index*/) {
        // No-op for CPU
    }
};

// Function to borrow memory to pool
DataPtr BorrowToMemoryPool(Device device, void* raw_ptr, size_t size,
                           std::function<void(DataPtr)> deleter) {
    // In a real implementation, this would manage memory pooling
    return DataPtr{raw_ptr, device};
}

int main() {
    Device local_device{0};    // CPU device
    size_t buffer_size = 1024; // 1KB for example

    // 1. Allocate CPU memory (using new/delete for demonstration)
    void* raw_ptr = new char[buffer_size];
    std::cout << "Allocated CPU memory at: " << raw_ptr << std::endl;

    // 2. Create shared_ptr with custom deleter
    auto storage = std::make_shared<NDArrayStorage>(
        BorrowToMemoryPool(local_device, raw_ptr, buffer_size,
                           [&](DataPtr data_ptr) {
                               DeviceGuard guard(data_ptr.device.index);
                               delete[] static_cast<char*>(data_ptr.ptr);
                               std::cout
                                   << "Freed CPU memory at: " << data_ptr.ptr
                                   << std::endl;
                           }),
        buffer_size);

    // 3. Demonstrate the memory is automatically freed when last reference is
    // dropped
    std::cout << "Resetting shared_ptr..." << std::endl;
    storage.reset(); // This will trigger the deleter

    return 0;
}