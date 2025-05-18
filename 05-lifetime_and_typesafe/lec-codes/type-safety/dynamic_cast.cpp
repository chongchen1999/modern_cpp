#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

// Base polymorphic class
class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const = 0;
};

// Derived classes
class Elephant : virtual public Animal {
public:
    void makeSound() const override { std::cout << "Elephant: Trumpet!\n"; }

    void stomp() const { std::cout << "Elephant stomping!\n"; }
};

class Seal : virtual public Animal {
public:
    void makeSound() const override { std::cout << "Seal: Bark!\n"; }

    void swim() const { std::cout << "Seal swimming!\n"; }
};

// Multiple inheritance example
class ElephantSeal : public Elephant, public Seal {
public:
    void makeSound() const override {
        std::cout << "ElephantSeal: Weird noise!\n";
    }

    void doBoth() const { std::cout << "ElephantSeal doing both!\n"; }
};

// Function demonstrating basic dynamic_cast with pointers
void demoPointerDynamicCast() {
    std::cout << "\n=== Pointer Dynamic Cast Demo ===\n";

    Elephant elephant;
    Animal* animalPtr = &elephant;

    // Successful downcast
    Elephant* elephantPtr = dynamic_cast<Elephant*>(animalPtr);
    if (elephantPtr) {
        std::cout << "Downcast to Elephant successful\n";
        elephantPtr->stomp();
    } else {
        std::cout << "Downcast to Elephant failed\n";
    }

    // Failed downcast attempt
    Seal* sealPtr = dynamic_cast<Seal*>(animalPtr);
    if (sealPtr) {
        std::cout << "Downcast to Seal successful (unexpected!)\n";
    } else {
        std::cout << "Downcast to Seal failed (expected)\n";
    }
}

// Function demonstrating dynamic_cast with references
void demoReferenceDynamicCast() {
    std::cout << "\n=== Reference Dynamic Cast Demo ===\n";

    Elephant elephant;
    Animal& animalRef = elephant;

    try {
        Elephant& elephantRef = dynamic_cast<Elephant&>(animalRef);
        std::cout << "Downcast to Elephant reference successful\n";
        elephantRef.stomp();
    } catch (const std::bad_cast& e) {
        std::cout << "Downcast to Elephant reference failed: " << e.what()
                  << "\n";
    }

    try {
        Seal& sealRef = dynamic_cast<Seal&>(animalRef);
        std::cout << "Downcast to Seal reference successful (unexpected!)\n";
    } catch (const std::bad_cast& e) {
        std::cout << "Downcast to Seal reference failed (expected): "
                  << e.what() << "\n";
    }
}

// Function demonstrating sidecasting with multiple inheritance
void demoSideCast() {
    std::cout << "\n=== Side Cast Demo (Multiple Inheritance) ===\n";

    ElephantSeal elephantSeal;
    Elephant& elephantRef = elephantSeal;

    // Attempt to cast from Elephant reference to Seal reference
    try {
        Seal& sealRef = dynamic_cast<Seal&>(elephantRef);
        std::cout << "Sidecast from Elephant to Seal successful\n";
        sealRef.swim();
    } catch (const std::bad_cast& e) {
        std::cout << "Sidecast failed: " << e.what() << "\n";
    }

    // Attempt the same with static_cast (wouldn't work)
    // Seal& sealRef = static_cast<Seal&>(elephantRef); // Compile error
}

// Function demonstrating void* cast to get most derived object
void demoVoidCast() {
    std::cout << "\n=== Void* Cast Demo ===\n";

    ElephantSeal elephantSeal;
    Animal* animalPtr = &elephantSeal;

    void* mostDerived = dynamic_cast<void*>(animalPtr);
    std::cout << "Most derived object address: " << mostDerived << "\n";

    // To actually use it, we'd need to know the exact type
    ElephantSeal* derivedPtr = static_cast<ElephantSeal*>(mostDerived);
    derivedPtr->doBoth();
}

// Function demonstrating basic RTTI with typeid
void demoBasicRTTI() {
    std::cout << "\n=== Basic RTTI Demo ===\n";

    Elephant elephant;
    Seal seal;
    Animal* animalPtr = &elephant;

    // Get type information
    const std::type_info& elephantType = typeid(elephant);
    const std::type_info& sealType = typeid(seal);
    const std::type_info& animalPtrType = typeid(*animalPtr);

    std::cout << "Elephant type name: " << elephantType.name() << "\n";
    std::cout << "Seal type name: " << sealType.name() << "\n";
    std::cout << "animalPtr points to: " << animalPtrType.name() << "\n";

    // Type comparison
    if (typeid(*animalPtr) == typeid(Elephant)) {
        std::cout << "animalPtr points to an Elephant\n";
    } else {
        std::cout << "animalPtr doesn't point to an Elephant\n";
    }

    if (typeid(*animalPtr) == typeid(Seal)) {
        std::cout << "animalPtr points to a Seal (unexpected!)\n";
    } else {
        std::cout << "animalPtr doesn't point to a Seal (expected)\n";
    }
}

// Function demonstrating type_index for associative containers
void demoTypeIndex() {
    std::cout << "\n=== Type Index Demo ===\n";

    std::unordered_map<std::type_index, std::string> typeNames;

    // Populate the map
    typeNames[std::type_index(typeid(int))] = "int";
    typeNames[std::type_index(typeid(double))] = "double";
    typeNames[std::type_index(typeid(Elephant))] = "Elephant";
    typeNames[std::type_index(typeid(Seal))] = "Seal";

    // Query the map
    std::cout << "Type of 42: " << typeNames[std::type_index(typeid(42))]
              << "\n";
    std::cout << "Type of 3.14: " << typeNames[std::type_index(typeid(3.14))]
              << "\n";

    Elephant e;
    std::cout << "Type of e: " << typeNames[std::type_index(typeid(e))] << "\n";
}

// Function demonstrating issues with RTTI across module boundaries
void demoRTIIssues() {
    std::cout << "\n=== RTTI Across Module Boundaries Demo ===\n";
    std::cout << "This is a conceptual demonstration - actual behavior would "
                 "depend on shared library loading.\n";

    // Imagine this is in a shared library
    class LibraryClass {
    public:
        virtual ~LibraryClass() = default;
    };

    // And this is in the main program
    class ProgramClass : public LibraryClass {};

    ProgramClass obj;
    LibraryClass* libPtr = &obj;

    // In a real cross-module scenario, this might fail if RTTI symbols aren't
    // properly shared
    ProgramClass* programPtr = dynamic_cast<ProgramClass*>(libPtr);

    if (programPtr) {
        std::cout
            << "Cross-module dynamic_cast succeeded (expected in this demo)\n";
    } else {
        std::cout << "Cross-module dynamic_cast failed (would happen with "
                     "RTLD_LOCAL)\n";
    }
}

int main() {
    demoPointerDynamicCast();
    demoReferenceDynamicCast();
    demoSideCast();
    demoVoidCast();
    demoBasicRTTI();
    demoTypeIndex();
    demoRTIIssues();

    return 0;
}