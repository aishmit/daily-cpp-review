// Day 003 demo: a class with a destructor but the compiler's copy constructor.
// g++ -std=c++20 -g -fsanitize=address scratch/day003_rule_of_three.cpp -o /tmp/r3 && /tmp/r3
#include <cstdio>

struct Bad {
    int* p;
    explicit Bad(int v) : p(new int(v)) {}
    ~Bad() { delete p; }
    // no copy constructor written → the compiler's copies the pointer (shallow)
};

int main() {
    Bad a(1);
    {
        Bad b = a;                      // b.p == a.p
        std::printf("a.p=%p b.p=%p\n", (void*)a.p, (void*)b.p);
    }                                   // ~b deletes the int
    std::printf("a.p still points at freed memory\n");
}                                       // ~a deletes it again → double free
