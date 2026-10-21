// std::exchange in a move constructor, on a two-member class (same shape as Buffer).
// Build: c++ -std=c++20 -Wall -Wextra -Werror -fsanitize=address,undefined -g scratch/exchange_demo.cpp -o build/exchange_demo && ./build/exchange_demo
#include <cstddef>
#include <cstdio>
#include <utility>   // std::exchange, std::move

class Ints {
public:
    explicit Ints(std::size_t n) : data_(n ? new int[n]{} : nullptr), size_(n) {}
    ~Ints() { delete[] data_; }

    // Move: each member takes other's value, and other's member is reset in the same step.
    Ints(Ints&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)) {}

    std::size_t size() const { return size_; }
    const int* data() const { return data_; }

private:
    int* data_;
    std::size_t size_;
};

int main() {
    int old = 5;
    int got = std::exchange(old, 9);   // old becomes 9, and you get back 5
    std::printf("exchange: got=%d old=%d\n", got, old);

    Ints a(3);
    const int* before = a.data();
    Ints b = std::move(a);
    std::printf("after move: a.size=%zu a.data=%p | b.size=%zu b.data is a's old array: %s\n",
                a.size(), static_cast<const void*>(a.data()), b.size(), b.data() == before ? "yes" : "no");
}
