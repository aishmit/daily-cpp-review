// Day 001 — Predict the output. Write your predictions in notes.md FIRST, then:
//   c++ -std=c++20 -O2 days/001/systems/predict.cpp -o build/predict && ./build/predict
// (Not graded by tests — your notes are reviewed.)
#include <cstdio>

struct Plain { int x; void f() {} };
struct Virt  { int x; virtual void f() {} };
struct Virt2 { int x; virtual void f() {} virtual void g() {} };
struct A { virtual ~A() = default; int a; };
struct B { virtual ~B() = default; int b; };
struct AB : A, B { int c; };

struct Base {
    Base() { std::printf("Base ctor -> "); hello(); }
    virtual ~Base() { std::printf("Base dtor -> "); hello(); }
    virtual void hello() const { std::printf("Base::hello\n"); }
};
struct Derived : Base {
    Derived() { std::printf("Derived ctor -> "); hello(); }
    ~Derived() override { std::printf("Derived dtor -> "); hello(); }
    void hello() const override { std::printf("Derived::hello\n"); }
};

struct Animal { virtual const char* speak() const { return "..."; } virtual ~Animal() = default; };
struct Dog : Animal { const char* speak() const override { return "woof"; } };
void by_value(Animal a) { std::printf("by value:     %s\n", a.speak()); }
void by_ref(const Animal& a) { std::printf("by reference: %s\n", a.speak()); }

int main() {
    // Q1: the four sizes on a 64-bit machine?
    std::printf("sizeof Plain=%zu Virt=%zu Virt2=%zu AB=%zu\n",
                sizeof(Plain), sizeof(Virt), sizeof(Virt2), sizeof(AB));

    // Q2: the four lines printed here?
    { Derived d; }

    // Q3: what does each line say?
    Dog dog;
    by_value(dog);
    by_ref(dog);

    // Q4: is the address of the B subobject the same as &ab? If not, by how much does it differ?
    AB ab;
    B* pb = &ab;
    std::printf("AB* -> B* pointer adjusted by %td bytes\n",
                reinterpret_cast<char*>(pb) - reinterpret_cast<char*>(&ab));
}
