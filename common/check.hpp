// common/check.hpp — tiny header-only test harness (no dependencies).
//
//   TEST(name) { CHECK(cond); CHECK_EQ(a, b); CHECK_NEAR(a, b, eps); }
//   int main() { return run_all_tests(); }
#pragma once
#include <cmath>
#include <cstdio>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace check_detail {
struct Test { const char* name; std::function<void()> fn; };
inline std::vector<Test>& registry() { static std::vector<Test> r; return r; }
inline int& failures() { static int f = 0; return f; }
struct Registrar { Registrar(const char* n, std::function<void()> f) { registry().push_back({n, std::move(f)}); } };

template <class T> std::string show(const T& v) {
    if constexpr (requires(std::ostream& o) { o << v; }) { std::ostringstream os; os << v; return os.str(); }
    else return "<unprintable>";
}
inline void fail(const char* file, int line, const std::string& msg) {
    ++failures();
    std::printf("    FAIL %s:%d: %s\n", file, line, msg.c_str());
    std::fflush(stdout);
}
}  // namespace check_detail

#define CHECK_CAT2(a, b) a##b
#define CHECK_CAT(a, b) CHECK_CAT2(a, b)
#define TEST(name)                                                                           \
    static void name();                                                                      \
    static ::check_detail::Registrar CHECK_CAT(reg_, name){#name, name};                     \
    static void name()

#define CHECK(cond) do { if (!(cond)) ::check_detail::fail(__FILE__, __LINE__, "CHECK(" #cond ")"); } while (0)
#define CHECK_EQ(a, b) do { auto&& _a = (a); auto&& _b = (b); if (!(_a == _b))                  \
    ::check_detail::fail(__FILE__, __LINE__, std::string(#a " == " #b "  (got ") +               \
        ::check_detail::show(_a) + " vs " + ::check_detail::show(_b) + ")"); } while (0)
#define CHECK_NEAR(a, b, eps) do { double _a = (a), _b = (b); if (std::fabs(_a - _b) > (eps))    \
    ::check_detail::fail(__FILE__, __LINE__, std::string(#a " ~= " #b "  (got ") +               \
        std::to_string(_a) + " vs " + std::to_string(_b) + ")"); } while (0)

inline int run_all_tests() {
    int passed = 0, total = 0;
    for (auto& t : check_detail::registry()) {
        int before = check_detail::failures();
        ++total;
        t.fn();
        bool ok = check_detail::failures() == before;
        passed += ok;
        std::printf("[%s] %s\n", ok ? " OK " : "FAIL", t.name);
        std::fflush(stdout);  // sanitizers may _exit() before stdio flushes
    }
    std::printf("\n%d/%d tests passed\n", passed, total);
    std::fflush(stdout);
    return passed == total ? 0 : 1;
}
