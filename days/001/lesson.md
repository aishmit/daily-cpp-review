# Day 001 — Virtual dispatch from the inside · Order book fundamentals

> **Why today:** "How does a virtual call work?" is the most common opener in C++ interviews at
> HRT/PDT-tier shops, and the follow-ups ("what does it cost?", "when can the compiler remove it?")
> separate application C++ from systems C++. On the design side, the limit order book is the
> data structure at the center of almost every trading system design question.

**Core time ≈ 30 min** · Systems 15 · Design 12 · Notes 3 · (+ optional deep dive)

---

## 0. Warm-up (3 min) — predict before you read

Open `systems/predict.cpp`. **Without compiling**, write answers to Q1–Q4 in `notes.md`.
Then read section 1, then compile and run it:

```bash
mkdir -p build && c++ -std=c++20 -O2 days/001/systems/predict.cpp -o build/predict && ./build/predict
```

(From Day 002 onward, the warm-up is 3 spaced-repetition questions from `qa/`.)

---

## 1. Systems: what `virtual` actually compiles to (7 min)

### The mental model
For each class with virtual functions the compiler emits one **vtable**: a static array of function
pointers, one slot per virtual function, in declaration order. Each *object* of that class gets a
hidden pointer, the **vptr**, normally at offset 0, pointing at its class's vtable. A derived class gets
its own vtable: overridden slots point at the derived function, the rest are inherited.

```
Derived object                      vtable for Derived (static, one per class)
┌──────────────┐                    ┌───────────────────────────┐
│ vptr ────────┼──────────────────▶ │ offset-to-top, typeinfo   │  (ABI bookkeeping, before the slots)
├──────────────┤                    │ [0] ~Derived (complete)   │
│ Base members │                    │ [1] ~Derived (deleting)   │
│ Derived mbrs │                    │ [2] Derived::hello        │
└──────────────┘                    └───────────────────────────┘
```

### What a call costs
```cpp
struct S { virtual int f() const; };
int call(const S& s) { return s.f(); }
```
GCC 13, `-O2`, x86-64:
```asm
call(S const&):
    mov  rax, QWORD PTR [rdi]     ; load vptr from the object
    jmp  [QWORD PTR [rax]]        ; load slot 0, indirect jump (tail call)
```
Two **dependent loads** and an **indirect branch**. The real costs, in the order interviewers care:
1. **No inlining.** The compiler can't see through the call, so it can't optimize across it.
   This usually matters far more than the loads.
2. **Branch prediction.** Indirect branches are predicted per call site. Same type every time →
   cheap. Mixed types in a hot loop → mispredicts (~15–20 cycles each).
3. **Cache misses.** The vtable or the object may not be in cache. Cold code, scattered objects.
4. **Size.** +8 bytes per object for the vptr, plus padding.

### When the compiler removes the virtual call (devirtualization)
- The dynamic type is known at the call site (`Derived d; d.hello();`).
- The class or function is `final`, so no override can exist.
- Whole-program/LTO analysis proves only one implementation exists.
- Speculative devirtualization: "if vptr == &Derived::vtable, inline Derived::hello; else call."

### The four traps interviewers probe
1. **Virtual destructors.** `delete base_ptr` on a class with a non-virtual destructor is
   **undefined behavior**. In practice the derived destructor is skipped, so its resources leak, and
   sized `delete` frees the wrong size. Rule: a polymorphic base has a public virtual destructor or a
   protected non-virtual one. *(That's Part A today.)*
2. **Virtual calls in constructors and destructors** dispatch to the class *currently being
   constructed or destroyed*, not the most-derived one. While `Base()` runs, the object's vptr
   points at Base's vtable; the derived part doesn't exist yet. Calling a *pure* virtual from there
   is UB.
3. **Slicing.** Passing a `Derived` by value as a `Base` copies only the `Base` subobject, and that
   copy's vptr is `Base`'s. Polymorphism needs a reference or pointer.
4. **Multiple inheritance.** Each polymorphic base subobject has its own vptr. Converting
   `AB*` to `B*` **adjusts the pointer** by the B subobject's offset, and calling a `B` virtual
   through it may go through a **thunk** that adjusts `this` back.

`override` makes the compiler check that you actually override something, catching signature typos
like a missing `const`. `final` forbids further overriding and enables devirtualization.

### Why prop shops care
Hot paths (market data → signal → order) often avoid virtual dispatch entirely. They use templates or
CRTP (Day 007) so everything inlines, or `std::variant` + `visit`. They *do* use virtual functions on
cold paths (config, plugins). Expect to be asked: *"How would you remove the virtual call from this
hot loop, and what do you give up?"*

---

## 2. Systems challenge (8 min) — `systems/challenge.hpp`

```bash
./run.sh 001 sys
```
- **Part A (1 min):** one keyword. Read the compiler warning and the ASan report before you fix it.
  The report is worth understanding: `new-delete-type-mismatch` means 16 bytes were allocated
  but 8 were freed.
- **Part B (10 min):** build a vtable by hand. `Shape` is a value type with runtime
  polymorphism and no inheritance: `{const ShapeVTable* vptr_, void* obj_}`. This is exactly
  what the compiler generates, and it's how `std::function` / `std::any` do type erasure.
  - **B1:** fill the two vtables (captureless lambdas convert to function pointers).
  - **B2:** rule of five through the vtable: deep copy via `clone`, `noexcept` move,
    copy-and-swap assignment, destroy via `destroy`. Today's tests touch Day 002 (lifetime) on
    purpose.
  - **B3:** dispatch `area()` / `name()`.

**Done =** `2 / 2 binaries green, 0 sanitizer reports.` Then answer in `notes.md`: *why does
`b2_vector_growth_moves_not_copies` care about `noexcept`?*

---

## 3. Design: the interview framework + limit order book (5 min)

### The framework (use it in every design answer from now on)
1. **Requirements:** functional (what ops), non-functional (latency target, throughput, durability,
   determinism). *Ask* about scale: messages/sec, symbols, order count.
2. **API:** the exact operations and events in and out.
3. **Data model:** the structures, and the complexity of each op.
4. **Hot path:** walk one message end to end. Where is time spent? What allocates?
5. **Scale & failure:** sharding, replication, recovery, what happens on a crash mid-operation.
6. **Trade-offs:** say what you chose *and what you gave up*.

### Limit order book: requirements
A book holds resting limit orders for one instrument, on two sides:
```
        ASKS (sell)  best = lowest
        102 │ 3            ← level: price → FIFO queue of orders
        101 │ 7  (#3)
  ──────────┼──────── spread = 101 − 99 = 2 ticks
         99 │ 10 (#1)
         98 │ 5  (#2)
        BIDS (buy)   best = highest
```
- **Ops:** add, cancel, modify (reduce keeps priority; increase loses it), best bid/ask, depth.
  Matching (an incoming order crossing the spread) comes on Day 003.
- **Priority:** price first, then time (FIFO within a level).
- **Prices are integer ticks**, never floats. Floating-point equality breaks level lookup, and
  exchanges define a tick size anyway.
- **Real scale:** a full US equities feed carries millions of messages per second at peak, and most
  of them are **adds and cancels**, not trades (most orders never execute). So cancel must be fast.
  That's Day 002.

### What interviewers push on
- "Which op is most frequent?" → cancel. Design for it.
- "How do you find an order by id?" → hash map id → order (or its location).
- "How do you find the best price?" → sorted structure, or an array indexed by price offset near
  the touch (cache-friendly; Day 028).
- "Why does increasing quantity lose priority?" → otherwise you could hold a small order at the
  front of the queue and size it up later: unfair to others waiting at that price.

---

## 4. Design challenge (7 min) — `design/orderbook.py`

```bash
./run.sh 001 design
```
Implement a passive (post-only) book against the spec in the docstring. Get it correct with
whatever structures you like. Then **write the time complexity of each operation in `notes.md`**.
Tomorrow we make it fast and you'll compare.

---

## 5. Deep dive (optional, 20–40 min)

**Stretch problem — small-buffer optimization for `Shape`:** Remove the heap allocation. Store the
object inline in `alignas(std::max_align_t) std::byte buf_[32]` when it fits, and fall back to the heap
otherwise. The vtable now needs `copy_construct(void* dst, const void* src)`,
`move_construct(void* dst, void* src)`, and `destroy_in_place(void*)`. Why does moving get
harder? (Hint: you can no longer steal a pointer.) This is how `std::function` avoids allocating
for small lambdas. Write your own tests.

**Read:**
- [cppreference — virtual function specifier](https://en.cppreference.com/w/cpp/language/virtual):
  the rules, especially "During construction and destruction".
- [Itanium C++ ABI §2.5 — Virtual Table Layout](https://itanium-cxx-abi.github.io/cxx-abi/abi.html#vtable):
  what GCC/Clang actually emit on Linux and macOS. Skim offset-to-top, RTTI, and the two destructor entries.
- [Compiler Explorer](https://godbolt.org): add `const char* f(const Dog& d) { return d.speak(); }`
  and compile at `-O2`. You'll see the indirect call. Now mark `Dog` `final`: the call is
  devirtualized and inlined to a constant. (Why doesn't `final` help `by_ref(const Animal&)`?)
- [How to Build a Fast Limit Order Book (WK Selph)](https://gist.github.com/halfelf/db1ae032dc34278968f8bf31ee999a25):
  the classic short write-up. Read it *after* finishing the design challenge; it's tomorrow's topic.

---

## 6. Notes (3 min) — create `days/001/notes.md`

```markdown
## Predictions (before running predict.cpp)
Q1: ...  Q2: ...  Q3: ...  Q4: ...
## After running: what surprised me
## Why noexcept matters for vector<Shape>
## Order book complexity (my version)
add: ... cancel: ... modify: ... best: ... depth: ...
## Confidence (1–5): virtual dispatch __ · order book __
## Anything confusing
```
Then `git add -A && git commit -m "day 001" && git push`. The next run reviews it.
