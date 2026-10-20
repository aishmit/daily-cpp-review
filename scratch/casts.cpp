// The four C++ casts. Build: c++ -std=c++20 -Wall -Wextra -fsanitize=address,undefined -g casts.cpp -o casts && ./casts
#include <cstdint>
#include <cstdio>

struct Animal { virtual ~Animal() = default; };
struct Dog : Animal { const char* bark() const { return "woof"; } };
struct Cat : Animal {};

void legacy_print(char* s) { std::printf("%s\n", s); }  // old C API: forgot to write const

int main() {
    // 1. static_cast: conversions the compiler can check make sense.
    double d = 3.9;
    int i = static_cast<int>(d);                        // number → number (truncates)
    Dog dog;
    const void* erased = &dog;
    const Dog* back = static_cast<const Dog*>(erased);  // void* → the type you KNOW it is
    std::printf("static_cast:      %d, %s\n", i, back->bark());

    // 2. dynamic_cast: "is this Animal really a Dog?", checked at RUNTIME via the vtable.
    Cat cat;
    Animal* a1 = &dog;
    Animal* a2 = &cat;
    Dog* d1 = dynamic_cast<Dog*>(a1);                   // really a Dog → valid pointer
    Dog* d2 = dynamic_cast<Dog*>(a2);                   // really a Cat → nullptr
    std::printf("dynamic_cast:     d1=%s d2=%s\n", d1 ? "Dog" : "null", d2 ? "Dog" : "null");

    // 3. const_cast: removes const. Only safe when the object wasn't really const.
    char msg[] = "hello";
    const char* view = msg;
    legacy_print(const_cast<char*>(view));              // OK: legacy_print doesn't write

    // 4. reinterpret_cast: "treat these bits as a different type." Low-level only.
    auto addr = reinterpret_cast<std::uintptr_t>(&dog); // pointer → integer
    std::printf("reinterpret_cast: &dog as an integer = 0x%llx\n", (unsigned long long)addr);
}
