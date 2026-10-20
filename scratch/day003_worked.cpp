// Day 003 worked syntax examples (every form the drill and challenge need).
// The lesson quotes this file. g++ -std=c++20 -Wall -Wextra -fsanitize=address,undefined scratch/day003_worked.cpp
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <utility>

// --- drill forms, on different names ---------------------------------------
struct Pair {
    double a_, b_;
    Pair(double a, double b) : a_(a), b_(b) {}       // member initializer list
};
struct Square { double side; };

// --- IntBox: owns ONE heap int. Same rule-of-five shape as Buffer, which owns an array.
class IntBox {
public:
    explicit IntBox(int v) : p_(new int(v)) {}
    ~IntBox() { delete p_; }                                   // new  ↔ delete
    IntBox(const IntBox& o) : p_(o.p_ ? new int(*o.p_) : nullptr) {}  // deep copy
    IntBox(IntBox&& o) noexcept : p_(o.p_) { o.p_ = nullptr; }  // steal, then empty the source
    // same move, one line: p_(std::exchange(o.p_, nullptr))
    IntBox& operator=(IntBox o) noexcept {                     // `o` is already a copy (or a move)
        std::swap(p_, o.p_);                                   // take its pointer, give it ours
        return *this;
    }                                                          // ~o frees our OLD int here
    int* get() const { return p_; }
private:
    int* p_;
};

int main() {
    double* xs = new double[5]{};         // n zeroed doubles   (new T[n]{} ↔ delete[])
    double src[2] = {1.5, 2.5};
    std::copy(src, src + 2, xs);          // copy [first, last) into xs
    assert(xs[1] == 2.5 && xs[4] == 0.0);
    delete[] xs;

    char c1 = 'a', c2 = 'b';
    char* l = &c1; char* r = &c2;
    std::swap(l, r);                      // swaps the pointers; c1/c2 untouched
    assert(l == &c2 && c1 == 'a');

    Pair pr(1.0, 2.0);
    assert(pr.b_ == 2.0);

    Square sq{3.0};
    const void* vp = &sq;
    const Square* back = static_cast<const Square*>(vp);  // void* → T*: static_cast, keep const
    assert(back->side == 3.0);

    IntBox a(7);
    IntBox b = a;                         // copy ctor
    assert(*b.get() == 7 && b.get() != a.get());
    IntBox c = std::move(a);              // move ctor
    assert(a.get() == nullptr && *c.get() == 7);
    b = c;                                // copy-assign via copy-and-swap
    b = std::move(c);                     // move-assign, same operator
    assert(c.get() == nullptr && *b.get() == 7);
    std::puts("all worked examples OK");
}
