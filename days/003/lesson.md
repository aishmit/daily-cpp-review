# Day 003 — Sliding window · C++: object lifetime by hand (rule of 0/3/5)
**Tue Oct 20 · 60 min** · Warm-up 5 · DSA 30 · C++ 25

> **Why today.** *Sliding window* is the first move for "longest/shortest contiguous stretch where
> X holds", which is how streaming questions come: rolling stats over trades, request throttling,
> "max over the last N" (question bank A6, A12; LeetCode 1438 matches a reported OA shape).
> *Object lifetime* is what the C++ debugging round is about: double frees, leaks, use-after-move.
> You also re-write by hand the destructor, `operator=` and move ctor the tutor wrote for you on Day 001.

Yesterday's review is in `days/002/review.md`. Headline: 49 at interview speed. The order book has the
right model but is at 1/12, with one bug the tests don't catch. You'll fix it tomorrow.

---

## 0. Warm-up (5 min)
Answer from memory in `notes.md`, then check the answers in `qa/`.
1. `Derived` overrides `Base`'s virtual destructor. When you delete a `Derived`, does `~Base` still run?
   So what does `virtual` on a destructor actually buy you? (cpp-om-011)
2. Write a move constructor for a class that owns a heap object through `void* obj_`.
   Why not just clone and delete the source? (cpp-ml-001)
3. You push `(price, order)` tuples onto a Python heap. Two orders share a price. What happens,
   and how do you fix it? (dsa-006)

---

## 1. DSA (30 min): sliding window
Python, on LeetCode, timer on. No hints or solutions on the site; `/hint` in Claude Code at minute 20 if stuck.

**How to practice it**
1. Timer: 10 min for #1 and 20 min for #2 (25 min hard stop on any one problem).
2. Before coding, write in `notes.md`: one-sentence restatement, input contract (bounds, empty, k vs n,
   negatives, duplicates), the brute force and its complexity.
3. After it passes, walk one edge case by hand and say the final complexity out loud.

| # | Problem | Timer | Why it's here |
|---|---|---|---|
| 1 | [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) (Easy) | 10 min | Fixed-size window: the "average price over the last k trades" shape |
| 2 | [2958. Length of Longest Subarray With at Most K Frequency](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/) (Medium) | 20 min | Variable-size window plus a hash map. On the question bank's sliding-window list (§D) |

**Stretch:** [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) (Medium).

Save your solutions as `days/003/dsa/p643.py` and `days/003/dsa/p2958.py` so the review can read them.

---

## 2. C++ & systems (25 min): object lifetime, rule of 0/3/5

### 2.1 The concept (5 min read)
**What the compiler writes for you.** If you don't declare them, a class gets up to five *special members*:
destructor, copy ctor, copy assignment, move ctor, move assignment. Each generated one works **member by
member**. For an `int* p_`, the generated copy copies the *pointer*, not the int it points at.

**Rule of three/five.** If your class *owns* a resource through a raw pointer, you need a destructor, so the
generated copies are wrong (shallow) and you must write them too. Real sanitizer output from
`scratch/day003_rule_of_three.cpp` (a class with `~Bad() { delete p; }` and no copy ctor):
```
==2092==ERROR: AddressSanitizer: attempting double-free on 0x502000000010 in thread T0:
    #1 in Bad::~Bad() scratch/day003_rule_of_three.cpp:8
    #2 in main scratch/day003_rule_of_three.cpp:19      ← ~a, the second delete
freed by thread T0 here:
    #1 in Bad::~Bad() scratch/day003_rule_of_three.cpp:8
    #2 in main scratch/day003_rule_of_three.cpp:17      ← ~b, the copy, deleted it first
previously allocated by thread T0 here:
    #1 in Bad::Bad(int) scratch/day003_rule_of_three.cpp:7
```
How to read it: **ERROR line** = what happened. **First stack** = where it happened now. **"freed by"** =
who freed it before. **"previously allocated"** = who made it. Two destructors freed one allocation →
two objects thought they owned it → shallow copy.

**The trap that bites in reviews.** Declaring *any* of copy ctor, copy assignment or destructor stops the
compiler from generating the **move** operations. `std::move(x)` then silently **copies**. No error, no warning.

**Rule of zero (the goal).** Hold resources in members that already manage themselves (`std::string`,
`std::vector`, `std::unique_ptr`, or *one* small class like today's `Buffer`) and write **no** special
members at all. The generated ones are then correct and moves stay moves.

**Why the move ctor must be `noexcept` (correcting your Day 001 answer).** You wrote "it's undefined behaviour
if move were to throw". It's not UB. When `std::vector` grows, it relocates elements with
`std::move_if_noexcept`: if the move ctor might throw, it **copies** instead, to keep the strong exception
guarantee. Measured with `scratch/day003_vector_noexcept.cpp` (1000 `emplace_back`s):
```
noexcept move:  copies=0 moves=1023
throwing move:  copies=1023 moves=0
```
Same code, one keyword: a thousand deep copies.

**Destruction order:** members are destroyed in **reverse** declaration order, after the destructor body.
Base classes go last (you saw this on Day 001).

### 2.2 "C++ by hand" drill (5 min): `days/003/systems/drill.cpp`
Six one-line TODOs: D1–D6. Worked examples (same syntax, different names; from `scratch/day003_worked.cpp`,
which compiles and runs). Type them, don't copy.
```cpp
double* xs = new double[5]{};       // D1: n zeroed elements. new T[n]{}  pairs with  delete[]
delete[] xs;                        // D2: [] because it came from new[]. (new T → delete, no [])
std::copy(src, src + 2, xs);        // D3: copy the range [src, src+2) to xs. Needs <algorithm>
std::swap(l, r);                    // D4: l, r are char*: swaps the pointers, not the chars
Pair(double a, double b) : a_(a), b_(b) {}   // D5: member initializer list, after the ')' and a ':'
const Square* back = static_cast<const Square*>(vp);  // D6: const void* → const T*. Keep const.
```
`./run.sh 003 sys` runs the drill first. Get it to 6/6 before the challenge.

### 2.3 Challenge (15 min): `days/003/systems/challenge.hpp`
`Buffer` owns a heap array of `size_` ints, like a `std::vector<int>` that can't grow. It is the only owner of
`data_`, and the invariant is `size_ == 0 ⇔ data_ == nullptr`. Do the TODOs **in order**. Each has its own
test file, so a failure points at one concept.

**Predict first** (write it in `notes.md` before TODO 2): if your copy ctor were
`Buffer(const Buffer& o) : data_(o.data_), size_(o.size_) {}`, which tests in `test_2_copy.cpp` fail, and
what does ASan print when the test ends?

**Worked example: `IntBox` owns one heap int** (the same five members; `Buffer` owns an *array* and a size):
```cpp
class IntBox {
public:
    explicit IntBox(int v) : p_(new int(v)) {}
    ~IntBox() { delete p_; }                                         // TODO 1's shape
    IntBox(const IntBox& o) : p_(o.p_ ? new int(*o.p_) : nullptr) {} // TODO 2: allocate your own, copy the value
    IntBox(IntBox&& o) noexcept : p_(o.p_) { o.p_ = nullptr; }       // TODO 3: steal, then empty the source
    //   one-line version:          p_(std::exchange(o.p_, nullptr))   (returns old value, stores the new one)
    IntBox& operator=(IntBox o) noexcept {                           // TODO 4: `o` is already a copy or a move
        std::swap(p_, o.p_);                                         //   take its pointer, give it ours
        return *this;
    }                                                                //   ~o frees our OLD int right here
private:
    int* p_;
};
```
What changes for `Buffer`: `delete[]` not `delete`; the copy allocates `new int[n]` and then needs D3's
`std::copy`; there are **two** members to steal / reset / swap (`data_` and `size_`); and size 0 must stay
`nullptr`.

| TODO | Concept | Test file | Done when |
|---|---|---|---|
| 1 | Destructor releases what the ctor acquired (RAII) | `test_1_destructor.cpp` | 3/3 |
| 2 | Copy = deep copy | `test_2_copy.cpp` | 3/3 |
| 3 | Move = steal + empty the source, `noexcept` | `test_3_move.cpp` | 4/4 |
| 4 | Copy-and-swap: one `operator=` for copy and move | `test_4_assign.cpp` | 4/4 |
| 5 | Rule of zero: fix `Level` by **deleting** code | `test_5_rule_of_zero.cpp` | 2/2 |

`test_5` fails two ways: the copy loses `venue`, and the *move* test fails even though you never touched
moves. Explain why in `notes.md` (it's the trap in 2.1).

### What interviewers push on
- "This class has a destructor. What else does it need?" → copy ctor + copy assignment (rule of 3),
  and the moves if it should be cheap to move (5). Or none of them: use a RAII member (0).
- "Why is your move ctor `noexcept`?" → vector relocation copies otherwise (numbers above).
- "Is your `operator=` safe for `a = a`?" → copy-and-swap: yes, with no special case. The copy is made first.
- "What's the cost of copy-and-swap?" → it always allocates a fresh copy, even when `*this` already has
  room. `std::vector` skips copy-and-swap for that reason.

---

## 3. Optional deep dive
- Stretch: add `Buffer::resize(n)` that keeps the first `min(n, size_)` values, using only the members you wrote.
- [cppreference: The rule of three/five/zero](https://cppreference.com/cpp/language/rule_of_three)
- [cppreference: `std::move_if_noexcept`](https://cppreference.com/cpp/utility/move_if_noexcept)
- [C++ Core Guidelines C.20–C.22: default operations](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero)

---

## 4. Notes: create `days/003/notes.md`
```markdown
## Warm-up recall (from memory)
1.
2.
3.
## DSA log
| Problem | Time | Solved without hints? | Brute force → optimal | Edge cases I listed | What tripped me up |
|---|---|---|---|---|---|
| 643  | | | | | |
| 2958 | | | | | |
## C++
- Predict (shallow copy in TODO 2): which tests fail, what ASan prints:
- Why did test_5's move test fail before the fix?
- Tests: drill _/6 · t1 _/3 · t2 _/3 · t3 _/4 · t4 _/4 · t5 _/2
## Confidence (1–5): DSA __ · C++ __
## Questions
```
Then `git add -A && git commit -m "day 003" && git push`.
