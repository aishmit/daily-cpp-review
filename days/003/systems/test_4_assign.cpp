// TODO(4): copy-and-swap assignment. Needs TODOs 1-3. Run: ./run.sh 003 sys
#include "challenge.hpp"
#include "check.hpp"
#include "counting_new.hpp"

using namespace day003;

TEST(t4_copy_assign_is_deep) {
    Buffer a(2);
    a[0] = 5;
    Buffer b(7);
    b = a;                          // copy assignment
    CHECK_EQ(b.size(), std::size_t{2});
    CHECK(b.data() != a.data());
    if (b.size() == 2) CHECK_EQ(b[0], 5);
}

TEST(t4_copy_assign_frees_the_old_array) {
    int before = g_live_arrays;
    {
        Buffer a(2);
        Buffer b(7);
        b = a;                      // b's old 7-int array must be freed, not leaked
        CHECK_EQ(b.size(), std::size_t{2});
        CHECK_EQ(g_live_arrays - before, 2);
    }
    CHECK_EQ(g_live_arrays - before, 0);
}

TEST(t4_move_assign_steals) {
    int before = g_live_arrays;
    Buffer a(3);
    const int* original = a.data();
    Buffer b(7);
    b = std::move(a);               // the same operator= : `other` is move-constructed from a
    CHECK(b.data() == original);
    CHECK(a.data() == nullptr);
    CHECK_EQ(g_live_arrays - before, 1);  // b's old array is gone
}

TEST(t4_self_assignment_is_safe) {
    Buffer a(3);
    a[2] = 42;
    Buffer& alias = a;
    a = alias;                      // copy-and-swap handles this with no special case
    CHECK_EQ(a.size(), std::size_t{3});
    if (a.size() == 3) CHECK_EQ(a[2], 42);
}

int main() { return run_all_tests(); }
