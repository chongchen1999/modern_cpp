#include <iostream>
using namespace std;

// 基类：Animal
class Animal {
public:
    Animal() { cout << "Animal constructor" << endl; }
    void breathe() { cout << "Animal is breathing" << endl; }
};

// 第一级派生类：Mammal（虚继承Animal）
class Mammal : virtual public Animal {
public:
    Mammal() { cout << "Mammal constructor" << endl; }
    void feedMilk() { cout << "Mammal feeds milk" << endl; }
};

// 第一级派生类：Bird（虚继承Animal）
class Bird : virtual public Animal {
public:
    Bird() { cout << "Bird constructor" << endl; }
    void fly() { cout << "Bird can fly" << endl; }
};

// 最终派生类：Bat（多继承Mammal和Bird）
class Bat : public Mammal, public Bird {
public:
    Bat() { cout << "Bat constructor" << endl; }
    void echolocate() { cout << "Bat uses echolocation" << endl; }
};

int main() {
    Bat bat;
    bat.breathe();    // 直接调用Animal的方法（无二义性）
    bat.feedMilk();   // 调用Mammal的方法
    bat.fly();        // 调用Bird的方法
    bat.echolocate(); // 调用Bat自身的方法
    return 0;
}