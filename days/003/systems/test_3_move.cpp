// TODO(3): the move constructor steals; no allocation. Run: ./run.sh 003 sys
#include <type_traits>
#include <vector>

#include "challenge.hpp"
#include "check.hpp"
#include "counting_new.hpp"

using namespace day003;

TEST(t3_move_steals_the_array) {
    Buffer a(3);
    a[1] = 7;
    const int* original = a.data();
    Buffer b = std::move(a);       // move constructor
    CHECK(b.data() == original);   // same array, not a copy of it
    CHECK_EQ(b.size(), std::size_t{3});
    if (b.size() == 3) CHECK_EQ(b[1], 7);
}

TEST(t3_moved_from_is_empty) {
    Buffer a(3);
    Buffer b = std::move(a);
    CHECK(a.data() == nullptr);    // otherwise a's destructor frees b's array
    CHECK_EQ(a.size(), std::size_t{0});
}

TEST(t3_move_does_not_allocate) {
    Buffer a(5);
    int before = g_live_arrays;
    Buffer b = std::move(a);
    CHECK_EQ(g_live_arrays, before);
}

TEST(t3_vector_growth_moves_instead_of_copying) {
    // When a vector grows it relocates its elements. It moves them only if the move
    // constructor is noexcept; otherwise it copies (std::move_if_noexcept).
    static_assert(std::is_nothrow_move_constructible_v<Buffer>);
    int before = g_live_arrays;
    std::vector<Buffer> v;
    for (int i = 0; i < 20; ++i) v.emplace_back(4);
    CHECK_EQ(g_live_arrays - before, 20);  // copies during growth would be counted here too...
    for (const auto& b : v) CHECK(b.data() != nullptr);  // ...and moves must not lose data
}

int main() { return run_all_tests(); }
