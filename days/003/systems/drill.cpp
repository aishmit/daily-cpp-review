// Day 003 — "C++ by hand" drill (5 min). One line per TODO. Run: ./run.sh 003 sys
// The worked examples are in lesson.md §3.2. Type them; don't copy-paste.
#include <algorithm>
#include <utility>

#include "check.hpp"
#include "counting_new.hpp"

TEST(d1_new_array_zeroed) {
    int n = 4;
    int* p = new int[n]{};
    CHECK(p != nullptr);
    if (p) {
        CHECK_EQ(p[n - 1], 0);
        delete[] p;
    }
}

TEST(d2_delete_array) {
    int before = g_live_arrays;
    int* p = new int[3]{};
    CHECK(p != nullptr);
    CHECK_EQ(g_live_arrays - before, 1);
    // TODO(D2): free p (one line)
    delete[] p;

    CHECK_EQ(g_live_arrays - before, 0);
}

TEST(d3_copy_n_ints) {
    int src[3] = {1, 2, 3};
    int dst[3] = {0, 0, 0};
    CHECK_EQ(src[0], 1);
    // TODO(D3): copy the 3 ints from src into dst with std::copy (one line)
    std::copy(src, src+3, dst);

    CHECK_EQ(dst[0], 1);
    CHECK_EQ(dst[2], 3);
}

TEST(d4_swap_two_pointers) {
    int x = 1, y = 2;
    int* a = &x;
    int* b = &y;
    // TODO(D4): swap the pointers a and b (not the ints) with std::swap (one line)
    std::swap(a,b);

    CHECK(a == &y);
    CHECK(b == &x);
    CHECK_EQ(x, 1);  // the ints didn't move
}

struct Point {
    int x_, y_;
    // TODO(D5): rewrite this constructor so it sets x_ and y_ from the arguments
    // using a member initializer list. Give the parameters names.
    Point(int x, int y) : x_(x), y_(y) {}
};

TEST(d5_member_init_list) {
    Point p(3, 4);
    CHECK_EQ(p.x_, 3);
    CHECK_EQ(p.y_, 4);
}

struct Circle { double r; };

TEST(d6_cast_back_from_void) {
    Circle c{2.0};
    const void* vp = &c;
    CHECK(vp != nullptr);
    const Circle* back = static_cast<const Circle*>(vp);  // TODO(D6): replace nullptr: cast vp back to a Circle pointer
    CHECK(back == &c);
    if (back) CHECK_NEAR(back->r, 2.0, 1e-12);
}

int main() { return run_all_tests(); }
