// Day 003 — test helper (don't edit). Counts live `new T[n]` arrays so the tests can
// see leaks and extra copies on any platform (LeakSanitizer doesn't run on macOS).
// It replaces the global array operator new[] / delete[]; plain `new T` is untouched.
// Include it in exactly one .cpp per program (each test_*.cpp is its own program).
// run.sh builds with -fno-builtin: otherwise clang may optimize away a new[]/delete[]
// pair (the standard allows it) and the count would be wrong.
#pragma once
#include <cstdlib>
#include <new>

inline int g_live_arrays = 0;  // +1 per new[], -1 per delete[]

[[gnu::noinline]] void* operator new[](std::size_t bytes) {
    ++g_live_arrays;
    if (void* p = std::malloc(bytes ? bytes : 1)) return p;
    throw std::bad_alloc{};
}
[[gnu::noinline]] void operator delete[](void* p) noexcept {
    if (!p) return;
    --g_live_arrays;
    std::free(p);
}
void operator delete[](void* p, std::size_t) noexcept { operator delete[](p); }
