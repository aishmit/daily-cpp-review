// Day 003 demo: vector growth copies unless the move constructor is noexcept.
// g++ -std=c++20 scratch/day003_vector_noexcept.cpp -o /tmp/vn && /tmp/vn
#include <cstdio>
#include <vector>

template <bool NoExcept>
struct T {
    static inline int copies = 0, moves = 0;
    T() = default;
    T(const T&) { ++copies; }
    T(T&&) noexcept(NoExcept) { ++moves; }
};

int main() {
    std::vector<T<true>> a;
    std::vector<T<false>> b;
    for (int i = 0; i < 1000; ++i) { a.emplace_back(); b.emplace_back(); }
    std::printf("noexcept move:  copies=%d moves=%d\n", T<true>::copies, T<true>::moves);
    std::printf("throwing move:  copies=%d moves=%d\n", T<false>::copies, T<false>::moves);
}
