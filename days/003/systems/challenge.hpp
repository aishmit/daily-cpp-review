// Day 003 — Systems challenge: object lifetime by hand (rule of 0 / 3 / 5).
// Run: ./run.sh 003 sys
//
// Do the TODOs in order: 1 → 5. Each test_N file checks one TODO.
// Read the worked example for each TODO in lesson.md first.
#pragma once
#include <algorithm>  // std::copy
#include <cstddef>
#include <string>
#include <utility>

namespace day003 {

// ============================================================================
// Buffer: owns a heap array of ints, like a tiny std::vector<int> that can't grow.
// It is the *only* owner of data_. Every special member must keep that true.
//   Invariant: size_ == 0  <=>  data_ == nullptr
// ============================================================================
class Buffer {
public:
    // Given: allocate n ints, all zero. (n == 0 → owns nothing.)
    explicit Buffer(std::size_t n) : data_(n ? new int[n]{} : nullptr), size_(n) {}

    // TODO(1) destructor: free the array. (One line. Which `delete`?)
    ~Buffer() {}

    // TODO(2) copy constructor: deep copy. Allocate your own array of other.size_
    // ints and copy the values. Afterwards the two Buffers share nothing.
    // Careful with other.size_ == 0 (keep the invariant).
    Buffer(const Buffer& other) : data_(nullptr), size_(0) { (void)other; }

    // TODO(3) move constructor: steal other's array, leave `other` empty
    // (data_ == nullptr, size_ == 0). No allocation. Keep it noexcept.
    Buffer(Buffer&& other) noexcept : data_(nullptr), size_(0) { (void)other; }

    // TODO(4) assignment, copy-and-swap: `other` arrives by value (already a copy,
    // or already moved-from the caller's object). Swap both members with it and
    // return *this. This one function is both copy- and move-assignment.
    Buffer& operator=(Buffer other) noexcept {
        (void)other;
        return *this;
    }

    // Given.
    std::size_t size() const { return size_; }
    const int* data() const { return data_; }
    int& operator[](std::size_t i) { return data_[i]; }
    const int& operator[](std::size_t i) const { return data_[i]; }

private:
    int* data_;
    std::size_t size_;
};

// ============================================================================
// TODO(5) rule of zero: Level is an order-book price level: a price, the
// quantities resting there, and a venue name. Someone hand-wrote its copy
// constructor, and it has two bugs (test_5 shows both). Fix it by writing LESS
// code. Then answer in notes.md: why did the *move* test fail too?
// ============================================================================
struct Level {
    int price;
    Buffer qtys;
    std::string venue;

    Level(int p, std::size_t n, std::string v) : price(p), qtys(n), venue(std::move(v)) {}

    Level(const Level& o) : price(o.price), qtys(o.qtys) {}
};

}  // namespace day003
