// TODO(1): the destructor frees the array. Run: ./run.sh 003 sys
#include "challenge.hpp"
#include "check.hpp"
#include "counting_new.hpp"

using namespace day003;

TEST(t1_buffer_is_zeroed) {
    {
        Buffer b(4);
        CHECK_EQ(b.size(), std::size_t{4});
        CHECK_EQ(b[0], 0);
        CHECK_EQ(b[3], 0);
    }
}

TEST(t1_destructor_frees_the_array) {
    int before = g_live_arrays;
    {
        Buffer b(8);
        CHECK_EQ(g_live_arrays - before, 1);  // the constructor allocated one array
    }                                         // <- b's destructor runs here
    CHECK_EQ(g_live_arrays - before, 0);      // ...and must have freed it
}

TEST(t1_empty_buffer_owns_nothing) {
    int before = g_live_arrays;
    {
        Buffer b(0);
        CHECK(b.data() == nullptr);
        CHECK_EQ(g_live_arrays - before, 0);
    }
    CHECK_EQ(g_live_arrays - before, 0);
}

int main() { return run_all_tests(); }
