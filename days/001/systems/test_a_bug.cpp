// Part A tests. Kept in its own binary: if the bug is still there, ASan aborts
// this program, and Part B's results stay readable.
#include <memory>

#include "challenge.hpp"
#include "check.hpp"

using namespace day001;

TEST(a_deleting_through_base_runs_derived_destructor) {
    {
        std::unique_ptr<Sink> s = std::make_unique<BufferedSink>();
        s->write("hello");
    }
    CHECK_EQ(g_buffered_destroyed, 1);
}

int main() { return run_all_tests(); }
