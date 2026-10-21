# C++ object model — Q&A

### Q: Walk me through what happens at runtime when you call a virtual function through a base reference.
`id: cpp-om-001` · `from: day 001` · `confidence: low` · `last: 2026-10-19 recall: partial again — vptr in first 8 bytes right; said the slot points to the base reference's version (wrong: the object's real class)` · `next: day 003`

<details><summary>Answer</summary>

Load the object's vptr (normally at offset 0), index into the class's vtable at the function's slot,
load that function pointer, and make an indirect call with `this` = the object. On x86-64 at `-O2`:
`mov rax,[rdi]` then `call/jmp [rax+slot*8]`. That's two dependent loads plus an indirect branch.
*Follow-up:* the bigger cost is usually lost inlining, then branch mispredicts when call-site types vary.
</details>

### Q: Why must a polymorphic base class have a virtual destructor? What actually happens if it doesn't?
`id: cpp-om-002` · `from: day 001` · `confidence: low` · `last: —` · `next: day 002`

<details><summary>Answer</summary>

`delete base_ptr` where the dynamic type is Derived and `~Base` isn't virtual is **undefined
behavior**. In practice only `~Base` runs, so Derived's members leak, and sized `operator delete`
frees the wrong size (ASan: `new-delete-type-mismatch`). Rule: public + virtual, or protected +
non-virtual (then you can't delete through Base at all). `shared_ptr<Base>(new Derived)` happens to
work because its control block captures the deleter for Derived. `unique_ptr<Base>` doesn't do that.
</details>

### Q: What does a virtual call inside a constructor dispatch to, and why?
`id: cpp-om-003` · `from: day 001` · `confidence: med` · `last: 2026-10-19 recall: right (calls Base's), but no "why"` · `next: day 005`

<details><summary>Answer</summary>

To the version in the class whose constructor (or destructor) is currently running. During
`Base()`, the Derived part isn't constructed yet, and the vptr is set to Base's vtable. Each
constructor sets the vptr to its own class's vtable as it runs, and each destructor resets it on the
way down. Calling a pure virtual function this way is UB, often "pure virtual method called" + abort.
</details>

### Q: What is object slicing? Give a case where it silently changes behavior.
`id: cpp-om-004` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (predict.cpp miss)` · `next: day 002`

<details><summary>Answer</summary>

Copying a Derived into a Base *by value* copies only the Base subobject. The copy's vptr is Base's,
so virtual calls hit Base's implementations. Example: `void f(Animal a)` called with a `Dog`
prints `...` instead of `woof`. Fixes: pass by reference or pointer, make bases non-copyable or
abstract, or use type erasure / `clone()`.
</details>

### Q: sizeof a class with one int and one virtual function, on x86-64? With two virtual functions?
`id: cpp-om-005` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (predict.cpp miss)` · `next: day 002`

<details><summary>Answer</summary>

16 both times. 8 bytes for the vptr plus 4 for the int, padded to 8-byte alignment. The vptr is per
*object*; the number of virtual functions only changes the size of the per-*class* vtable.
</details>

### Q: In `struct AB : A, B`, both bases polymorphic: what happens when you convert `AB*` to `B*`? What's a thunk?
`id: cpp-om-006` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (predict.cpp miss)` · `next: day 002`

<details><summary>Answer</summary>

The pointer is **adjusted** by the B subobject's offset inside AB (e.g. +16), so `(void*)pb != (void*)&ab`.
Each polymorphic base subobject has its own vptr. If AB overrides a function declared in B, B's
vtable-in-AB points at a **thunk**: a tiny stub that adjusts `this` from the B subobject back to the
full AB object and then jumps to `AB::f`. (`static_cast` handles null correctly; `reinterpret_cast`
doesn't adjust at all, which is a bug.)
</details>

### Q: When can the compiler devirtualize a call? How do you help it?
`id: cpp-om-007` · `from: day 001` · `confidence: low` · `last: —` · `next: day 003`

<details><summary>Answer</summary>

When it can prove the dynamic type: the object is a local or value of known type; the class or
function is `final`; whole-program/LTO analysis sees one implementation; or speculatively (compare
the vptr, inline the likely target, fall back to an indirect call). Help it with `final`, internal
linkage, LTO, and, on hot paths, by using static polymorphism (templates/CRTP) or `std::variant`
instead of virtual functions.
</details>

### Q: How does type erasure (std::function, std::any) give you polymorphism without inheritance?
`id: cpp-om-008` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (B3: called obj_->area(), then vptr_->area(this) — confused the wrapper with the erased object)` · `next: day 002`

<details><summary>Answer</summary>

Store the concrete object type-erased (`void*` or an inline buffer) plus a pointer to a hand-built
table of function pointers (invoke/copy/move/destroy) generated per concrete type, usually from a
template. Value semantics, any type that fits the interface, no common base class. Small-buffer
optimization stores small objects inline to avoid heap allocation; moves then have to move-construct
rather than steal a pointer.
</details>

### Q: Does adding a (non-virtual) member function to a class change its sizeof? Where does the function's code live?
`id: cpp-om-009` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (predict.cpp miss)` · `next: day 002`

<details><summary>Answer</summary>

No. Member functions are ordinary functions compiled once into the program's code (text segment);
`p->f()` is just `f(p)` with `this = p`. Objects hold only data members (+ padding), plus one vptr
per polymorphic base subobject if there are virtual functions. So `struct { int x; void f(); }` is 4
bytes. *Follow-up:* an empty class still has sizeof 1 (distinct addresses), unless it's an empty base
(EBO) or a `[[no_unique_address]]` member.
</details>

### Q: Why is `sizeof` of `struct { void* vptr; int x; }` 16 and not 12?
`id: cpp-om-010` · `from: day 001` · `confidence: low` · `last: 2026-10-01 (predict.cpp miss)` · `next: day 002`

<details><summary>Answer</summary>

A struct's alignment is the max alignment of its members (8, for the pointer), and its size is
rounded up to a multiple of that alignment, so every element of an array of them stays aligned.
12 → 16, with 4 bytes of tail padding. In `AB : A, B` this is why B starts at offset 16, and why
`c` can sit in B's tail padding at offset 28 (Itanium ABI reuses tail padding of non-POD bases), so
sizeof(AB) is 32, not 40.
</details>

### Q: `Derived` overrides `Base`'s virtual destructor. When you delete a Derived, does `~Base` still run? So what does `virtual` on a destructor actually buy you?
`id: cpp-om-011` · `from: day 001` · `confidence: low` · `last: 2026-10-20 recall: chaining right; didn't say what virtual buys (where delete starts)` · `next: day 004`

<details><summary>Answer</summary>

Yes, `~Base` always runs. Destructors chain: `~Derived`'s body runs, then members, then `~Base`,
automatically. "Override" for a destructor doesn't replace the base one the way it does for
ordinary functions. What `virtual` buys you is the *starting point*: `delete base_ptr` looks up the
vtable and starts at `~Derived`. Without it, the compiler only sees `Base*` and starts (and stops) at
`~Base`, which is UB, and in practice Derived's resources leak.
</details>

### Q: You have a `const void*` that you know points at a `Circle`. Which cast gets you back a usable pointer, and why not the others?
`id: cpp-om-012` · `from: day 001` · `confidence: med` · `last: 2026-10-19 recall: static_cast right; didn't give the exact form static_cast<const Circle*>(s)` · `next: day 005`

<details><summary>Answer</summary>

`static_cast<const Circle*>(s)`. `static_cast` is the standard cast for `void*` → `T*`, and you're
promising the object really is a `Circle`. Target a *pointer* type (`Circle*`, not `Circle`) and keep
`const`, since `static_cast` can't drop it (only `const_cast` can). `reinterpret_cast` also compiles for
`void*` → `T*`, but it's the "reinterpret raw bits" cast, kept for unrelated pointer types and integers.
Using it here tells a reviewer you don't know which cast fits. *Follow-up:* `dynamic_cast` needs a
polymorphic type and checks at runtime; it can't start from `void*`.
</details>

### Q: What's the difference between `struct` and `class` in C++?
`id: cpp-om-013` · `from: day 001 (asked 2026-10-15)` · `confidence: low` · `last: 2026-10-15 (switched struct→class, hit "deleted function '~Dog'")` · `next: day 003`

<details><summary>Answer</summary>

Only the defaults. `struct`: members are `public` and inheritance is `public` by default. `class`: both are
`private` by default. Otherwise they're identical (both can have virtuals, ctors, private members).
Classic trap: `class Animal { virtual ~Animal() = default; };` makes the destructor private, so a derived
class can't call it, and its destructor becomes deleted. `class Dog : Animal` is private inheritance,
so `Animal* a = &dog;` won't compile. Convention: `struct` for plain data, `class` when there are invariants.
</details>

### Q: `int x = -6; size_t y = 0;` What does `x > y` evaluate to, and why? How do you avoid it?
`id: cpp-om-014` · `from: day 002 (LeetCode 121, 2026-10-15)` · `confidence: low` · `last: 2026-10-15 (used size_t for profit; -6 became 18446744073709551610)` · `next: day 003`

<details><summary>Answer</summary>

`true`. When you compare (or assign) a signed `int` with an unsigned `size_t`, the `int` is converted to
unsigned first. -6 wraps around to 2^64 − 6 = 18446744073709551610. That's well-defined, not UB, but
silently wrong. Use `size_t` only for sizes and indices; use signed types (`int`, `long long`) for
anything that can go negative (differences, profits). `-Wall -Wextra` warns: `-Wsign-compare`.
</details>
