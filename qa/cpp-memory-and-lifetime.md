# C++ memory & lifetime — Q&A

### Q: Write a move constructor for a class that owns a heap object through `void* obj_`. Why not just clone and delete the source?
`id: cpp-ml-001` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (proposed clone+delete; didn't null the source)` · `next: day 002`

<details><summary>Answer</summary>

`Shape(Shape&& other) noexcept : vptr_(other.vptr_), obj_(other.obj_) { other.obj_ = nullptr; }`.
Take the pointer, then empty the source, so its destructor frees nothing (otherwise you get a double free).
Clone+delete is a copy plus a free: it allocates (slow), and `new` can throw, which breaks the
`noexcept` promise (a throw inside `noexcept` calls `std::terminate`). `std::vector` only moves on
reallocation if the move ctor is `noexcept`; otherwise it copies.
</details>

### Q: Why should a move constructor be `noexcept`? What does `std::vector` do if it isn't?
`id: cpp-ml-002` · `from: day 003` · `confidence: low` · `last: 2026-10-01 (Day 001 notes: said "it's undefined behaviour if move were to throw"; wrong)` · `next: day 004`

<details><summary>Answer</summary>

When a vector grows it relocates elements with `std::move_if_noexcept`. If `T`'s move ctor isn't `noexcept`
(and `T` is copyable), it **copies** instead, so that a throw halfway through can't leave the old buffer
half-moved (the strong exception guarantee). Not UB, just slow: in `scratch/day003_vector_noexcept.cpp`,
1000 `emplace_back`s gave 1023 moves vs 1023 copies, from one keyword. If a `noexcept` function does
throw, `std::terminate` is called.
</details>

### Q: A class owns a raw `int*` and has a destructor that deletes it. You didn't write a copy constructor. What happens on `B b = a;`, and what does ASan print?
`id: cpp-ml-003` · `from: day 003` · `confidence: low` · `last: —` · `next: day 004`

<details><summary>Answer</summary>

The generated copy ctor copies member by member, so `b.p == a.p` (a shallow copy). The first destructor frees
the int; the second frees it again: `AddressSanitizer: attempting double-free`, with three stacks: where
(the 2nd `~`), "freed by" (the 1st `~`), "previously allocated" (the ctor). Fix: the rule of three (a deep copy
ctor plus copy assignment), or own the int through a RAII member and write nothing (rule of zero).
</details>

### Q: State the rules of 3, 5 and 0. Which declarations stop the compiler from generating the move operations?
`id: cpp-ml-004` · `from: day 003` · `confidence: low` · `last: —` · `next: day 004`

<details><summary>Answer</summary>

**3:** if you need a destructor, copy ctor or copy assignment, you almost certainly need all three (you own
something). **5:** add the move ctor and move assignment so moves are cheap. **0:** best: put each resource in
a member that manages itself (`vector`, `string`, `unique_ptr`, one RAII class) and declare none of them.
A user-declared **destructor, copy ctor or copy assignment** suppresses the implicit moves, so `std::move(x)`
silently copies. (Declaring a move operation deletes the implicit copies.)
</details>

### Q: Write copy-and-swap `operator=` for a class with members `int* data_; size_t size_;`. Why is it safe for `a = a`, and what does it cost?
`id: cpp-ml-005` · `from: day 003` · `confidence: low` · `last: 2026-10-01 (Day 001: tutor wrote it after he asked twice)` · `next: day 004`

<details><summary>Answer</summary>

```cpp
Buffer& operator=(Buffer other) noexcept {      // by value: copy-constructed or move-constructed
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    return *this;
}                                               // other's dtor frees the old array
```
Self-assignment is safe because the copy is made *before* anything of ours is touched. It's also exception-safe:
if the copy throws, `*this` is unchanged. Cost: it always allocates a new copy, even when `*this` already has enough
room to copy into. That's why `std::vector`'s copy assignment doesn't use it.
</details>
