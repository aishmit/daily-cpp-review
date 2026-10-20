// Redo (Fri Oct 16): write the three parts of Shape the tutor wrote for you on Day 001.
// Run from the repo root:
//   c++ -std=c++20 -Wall -Wextra -Werror -fsanitize=address,undefined -g -I common -I scratch/redo_shape \
//       scratch/redo_shape/test_b_vtable.cpp -o build/redo && ./build/redo
// Done = 6/6 tests passed, no sanitizer reports. Write it from memory first; peek at Day 001 only if stuck.
#pragma once
#include <numbers>
#include <utility>

namespace day001 {

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

// R1 (destroy slots): each table's 4th entry must destroy *self AND free its memory.
//     Signature: void (*destroy)(void* self). Note: void*, not const void* (you're destroying it).
//     Hint: cast back to the real type (which cast?), then one keyword does both jobs.
inline constexpr ShapeVTable kCircleVTable = {
    [](const void* s) { const Circle* c = static_cast<const Circle*>(s); return std::numbers::pi * c->r * c->r; },
    [](const void*) { return "circle"; },
    [](const void* s) -> void* { return new Circle(*static_cast<const Circle*>(s)); },
    nullptr  // TODO(R1)
};
inline constexpr ShapeVTable kRectVTable = {
    [](const void* s) { const Rect* r = static_cast<const Rect*>(s); return r->w * r->h; },
    [](const void*) { return "rect"; },
    [](const void* s) -> void* { return new Rect(*static_cast<const Rect*>(s)); },
    nullptr  // TODO(R1)
};

class Shape {
public:
    explicit Shape(const Circle& c) : vptr_(&kCircleVTable), obj_(new Circle(c)) {}
    explicit Shape(const Rect& r)   : vptr_(&kRectVTable),   obj_(new Rect(r)) {}

    Shape(const Shape& other) : vptr_(other.vptr_), obj_(other.vptr_->clone(other.obj_)) {}
    Shape(Shape&& other) noexcept : vptr_(other.vptr_), obj_(other.obj_) { other.obj_ = nullptr; }

    // TODO(R3): copy-and-swap. `other` is already a copy (or a moved-in Shape).
    //   Swap both of your pointers with other's, return *this. other's destructor cleans up.
    Shape& operator=(Shape other) noexcept { (void)other; return *this; }

    // TODO(R2): destroy the object through the table. A moved-from Shape (obj_ == nullptr) owns nothing.
    ~Shape() {}

    double area() const { return vptr_->area(obj_); }
    const char* name() const { return vptr_->name(obj_); }
    bool empty() const { return obj_ == nullptr; }

private:
    const ShapeVTable* vptr_;
    void* obj_;
};

static_assert(sizeof(Shape) == 2 * sizeof(void*));

}  // namespace day001
