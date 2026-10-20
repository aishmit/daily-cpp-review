// Part B tests: hand-rolled vtable.
#include <cstring>
#include <type_traits>
#include <vector>

#include "challenge.hpp"
#include "check.hpp"

using namespace day001;
constexpr double kPi = std::numbers::pi;

TEST(b1_dispatch_area_and_name) {
    {
        Shape c{Circle{1.0}};
        Shape r{Rect{2.0, 3.0}};
        CHECK_NEAR(c.area(), kPi, 1e-12);
        CHECK_NEAR(r.area(), 6.0, 1e-12);
        CHECK(std::strcmp(c.name(), "circle") == 0);
        CHECK(std::strcmp(r.name(), "rect") == 0);
    }
    CHECK_EQ(Circle::live, 0);
    CHECK_EQ(Rect::live, 0);
}

TEST(b1_heterogeneous_container) {
    {
        std::vector<Shape> v;
        v.emplace_back(Circle{1.0});
        v.emplace_back(Rect{2.0, 3.0});
        v.emplace_back(Circle{2.0});
        double total = 0;
        for (const auto& s : v) total += s.area();
        CHECK_NEAR(total, kPi + 6.0 + 4 * kPi, 1e-9);
    }
    CHECK_EQ(Circle::live, 0);
    CHECK_EQ(Rect::live, 0);
}

TEST(b2_copy_is_deep) {
    {
        Shape a{Rect{1.0, 2.0}};
        Shape b = a;
        CHECK_EQ(Rect::live, 2);
        CHECK(!a.empty());
        CHECK(!b.empty());
        CHECK_NEAR(a.area(), 2.0, 1e-12);
        CHECK_NEAR(b.area(), 2.0, 1e-12);
    }
    CHECK_EQ(Rect::live, 0);
}

TEST(b2_move_steals) {
    {
        Shape a{Circle{1.0}};
        Shape b = std::move(a);
        CHECK(a.empty());
        CHECK(!b.empty());
        CHECK_EQ(Circle::live, 1);
        CHECK_NEAR(b.area(), kPi, 1e-12);
    }
    CHECK_EQ(Circle::live, 0);
}

TEST(b2_assignment_across_types) {
    {
        Shape a{Circle{1.0}};
        Shape b{Rect{2.0, 2.0}};
        a = b;  // copy-assign: a's circle must be destroyed, a becomes a rect
        CHECK_EQ(Circle::live, 0);
        CHECK_EQ(Rect::live, 2);
        CHECK(std::strcmp(a.name(), "rect") == 0);

        Shape c{Circle{3.0}};
        a = std::move(c);  // move-assign
        CHECK(c.empty());
        CHECK_EQ(Circle::live, 1);
        CHECK_EQ(Rect::live, 1);
        CHECK_NEAR(a.area(), 9 * kPi, 1e-9);

        Shape& alias = a;
        a = alias;  // self-assignment must be safe
        CHECK_NEAR(a.area(), 9 * kPi, 1e-9);
    }
    CHECK_EQ(Circle::live, 0);
    CHECK_EQ(Rect::live, 0);
}

TEST(b2_vector_growth_moves_not_copies) {
    // std::vector only moves elements on reallocation if the move ctor is noexcept
    // (otherwise it copies, to keep the strong exception guarantee).
    static_assert(std::is_nothrow_move_constructible_v<Shape>);
    {
        std::vector<Shape> v;
        for (int i = 0; i < 100; ++i) v.emplace_back(Circle{1.0});
        CHECK_EQ(Circle::live, 100);
    }
    CHECK_EQ(Circle::live, 0);
}

int main() { return run_all_tests(); }
