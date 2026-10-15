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
