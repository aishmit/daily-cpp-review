// TODO(2): the copy constructor makes a deep copy. Run: ./run.sh 003 sys
#include "challenge.hpp"
#include "check.hpp"
#include "counting_new.hpp"

using namespace day003;

TEST(t2_copy_has_same_values) {
    Buffer a(3);
    a[0] = 10; a[1] = 20; a[2] = 30;
    Buffer b = a;  // copy constructor
    CHECK_EQ(b.size(), std::size_t{3});
    if (b.size() == 3) {
        CHECK_EQ(b[0], 10);
        CHECK_EQ(b[2], 30);
    }
}

TEST(t2_copy_owns_its_own_array) {
    int before = g_live_arrays;
    Buffer a(3);
    a[0] = 10;
    Buffer b = a;
    CHECK_EQ(b.size(), std::size_t{3});
    CHECK(b.data() != nullptr);
    CHECK(b.data() != a.data());           // a shallow copy would share (then double-free)
    CHECK_EQ(g_live_arrays - before, 2);   // one array each
    if (b.size() == 3) {
        b[0] = 99;
        CHECK_EQ(a[0], 10);       // writing to the copy must not change the original
    }
}

TEST(t2_copy_of_empty_is_empty) {
    Buffer a(0);
    Buffer b = a;
    CHECK_EQ(b.size(), std::size_t{0});
    CHECK(b.data() == nullptr);   // the invariant: size 0 <=> nullptr
}

int main() { return run_all_tests(); }
