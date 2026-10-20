// TODO(5): rule of zero. Needs TODOs 1-4. Run: ./run.sh 003 sys
#include "challenge.hpp"
#include "check.hpp"
#include "counting_new.hpp"

using namespace day003;

TEST(t5_copy_copies_every_member) {
    Level a(101, 2, "NASDAQ");
    Level b = a;
    CHECK_EQ(b.price, 101);
    CHECK_EQ(b.venue, std::string("NASDAQ"));
    CHECK(b.qtys.data() != a.qtys.data());
}

TEST(t5_move_moves_the_buffer) {
    Level a(101, 2, "NASDAQ");
    const int* original = a.qtys.data();
    Level b = std::move(a);
    CHECK(b.qtys.data() == original);   // moved, not copied
    CHECK_EQ(b.venue, std::string("NASDAQ"));
}

int main() { return run_all_tests(); }
