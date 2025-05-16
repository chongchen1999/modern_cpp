#include <functional>
#include <iostream>
#include <memory>
#include <utility>

// A move-only functor
struct MoveOnlyFunctor {
    std::unique_ptr<int> ptr;

    MoveOnlyFunctor(int val) : ptr(std::make_unique<int>(val)) {}

    // Delete copy operations
    MoveOnlyFunctor(const MoveOnlyFunctor&) = delete;
    MoveOnlyFunctor& operator=(const MoveOnlyFunctor&) = delete;

    // Allow move operations
    MoveOnlyFunctor(MoveOnlyFunctor&&) = default;
    MoveOnlyFunctor& operator=(MoveOnlyFunctor&&) = default;

    int operator()(int x) const { return x + *ptr; }
};

// A const-correct functor
struct ConstCorrectFunctor {
    int operator()(int x) const { return x * 2; }

    // Non-const version
    int operator()(int x) { return x * 3; }
};

int main() {
    // ===== std::function limitations =====
    try {
        // Works with copyable functors
        std::function<int(int)> func1 = [](int x) { return x + 1; };
        std::cout << "std::function with lambda: " << func1(5) << std::endl;

        // Can't work with move-only functors (pre-C++23)
        // MoveOnlyFunctor mf(10);
        // std::function<int(int)> func2 = mf; // Won't compile - mf is not
        // copyable
    } catch (const std::bad_function_call& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // ===== std::move_only_function (C++23) =====
#ifdef __cpp_lib_move_only_function
    {
        // Works with move-only functors
        MoveOnlyFunctor mf(10);
        std::move_only_function<int(int)> mof1 = std::move(mf);
        std::cout << "move_only_function with move-only functor: " << mof1(5)
                  << std::endl;

        // Can't be copied
        // auto mof2 = mof1; // Won't compile - not copyable

        // Can be moved
        auto mof3 = std::move(mof1);

        // UB to call when null
        // std::move_only_function<int(int)> empty;
        // empty(5); // Undefined behavior

        // In-place construction
        std::move_only_function<int(int)> mof4(
            std::in_place_type<MoveOnlyFunctor>, 20);
        std::cout << "move_only_function in-place constructed: " << mof4(5)
                  << std::endl;
    }
#endif

    // ===== Qualifier respect in move_only_function =====
#ifdef __cpp_lib_move_only_function
    {
        ConstCorrectFunctor ccf;
        const ConstCorrectFunctor ccf_const;

        // Respects const qualifier
        std::move_only_function<int(int) const> mof_const = ccf;
        std::cout << "const move_only_function: " << mof_const(5) << std::endl;

        // Non-const version
        std::move_only_function<int(int)> mof_nonconst = ccf;
        std::cout << "non-const move_only_function: " << mof_nonconst(5)
                  << std::endl;

        // std::function doesn't respect const qualifier
        std::function<int(int)> func_const = ccf_const;
        std::cout << "const functor in std::function: " << func_const(5)
                  << std::endl;
    }
#endif

    // ===== std::copyable_function (C++26) =====
#ifdef __cpp_lib_copyable_function
    {
        // Similar to std::function but respects qualifiers
        ConstCorrectFunctor ccf;
        std::copyable_function<int(int) const> cf_const = ccf;
        std::cout << "copyable_function const: " << cf_const(5) << std::endl;

        // Won't compile if functor doesn't match qualifiers
        // std::copyable_function<int(int) const> cf_bad = [](int x) mutable {
        // return x; };
    }
#endif

    return 0;
}