// Day 001 — Systems challenge: virtual dispatch from the inside.
// Run: ./run.sh 001 sys
#pragma once
#include <numbers>
#include <utility>

namespace day001 {

// ============================================================================
// Part A — find the bug (one keyword). ~1 min.
// A BufferedSink is owned through a pointer to its base. Something leaks /
// is undefined. Read the compiler warnings — they're telling you.
// ============================================================================
inline int g_buffered_destroyed = 0;

struct Sink {
    ~Sink() = default;  // TODO(A)
    virtual void write(const char* msg) = 0;
};

struct BufferedSink : Sink {
    char* buf = new char[256];
    ~BufferedSink() { delete[] buf; ++g_buffered_destroyed; }
    void write(const char*) override {}
};

// ============================================================================
// Part B — build a vtable by hand. ~10 min.
//
// A C++ polymorphic object is {vptr -> table of function pointers, data}.
// Here you build exactly that, with no inheritance and no `virtual`:
// `Shape` holds a pointer to a table of function pointers plus a type-erased
// pointer to the concrete object. (std::function and std::any work this way.)
// ============================================================================

// Concrete types. The `live` counters let the tests catch leaks and shallow copies.
struct Circle {
    double r;
    explicit Circle(double r_) : r(r_) { ++live; }
    Circle(const Circle& o) : r(o.r) { ++live; }
    ~Circle() { --live; }
    static inline int live = 0;
};

struct Rect {
    double w, h;
    Rect(double w_, double h_) : w(w_), h(h_) { ++live; }
    Rect(const Rect& o) : w(o.w), h(o.h) { ++live; }
    ~Rect() { --live; }
    static inline int live = 0;
};

struct ShapeVTable {
    double      (*area)(const void* self);
    const char* (*name)(const void* self);     // "circle" or "rect"
    void*       (*clone)(const void* self);    // heap-allocate a copy of *self, return it
    void        (*destroy)(void* self);        // destroy *self and free its memory
};

// TODO(B1): fill in both tables. Each entry can be a captureless lambda
// (it converts to a plain function pointer) that casts `self` back to the
// concrete type, e.g. [](const void* s) { return static_cast<const Circle*>(s)->...; }
// Use std::numbers::pi for the circle.
inline constexpr ShapeVTable kCircleVTable = {nullptr, nullptr, nullptr, nullptr};
inline constexpr ShapeVTable kRectVTable   = {nullptr, nullptr, nullptr, nullptr};

class Shape {
public:
    explicit Shape(const Circle& c) : vptr_(&kCircleVTable), obj_(new Circle(c)) {}
    explicit Shape(const Rect& r)   : vptr_(&kRectVTable),   obj_(new Rect(r)) {}

    // TODO(B2): the rule of five, implemented through the vtable.
    //  - copy ctor: deep copy (clone). A shallow copy double-frees — ASan will tell you.
    //  - move ctor: steal the object; leave `other` empty (obj_ == nullptr). Must be noexcept.
    //  - assignment: one copy-and-swap operator handles both copy and move assignment.
    //  - dtor: destroy through the vtable; a moved-from Shape owns nothing.
    Shape(const Shape& other) : vptr_(other.vptr_), obj_(nullptr) {}
    Shape(Shape&& other) noexcept : vptr_(other.vptr_), obj_(nullptr) {}
    Shape& operator=(Shape other) noexcept { (void)other; return *this; }
    ~Shape() {}

    // TODO(B3): dispatch through vptr_.
    double area() const { return 0.0; }
    const char* name() const { return ""; }

    bool empty() const { return obj_ == nullptr; }

private:
    const ShapeVTable* vptr_;
    void* obj_;
};

// Same footprint as a C++ object with a vptr plus one pointer member.
static_assert(sizeof(Shape) == 2 * sizeof(void*));

}  // namespace day001
