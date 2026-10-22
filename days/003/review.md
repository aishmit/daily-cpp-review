# Day 003 review: sliding window (643, 2958) · C++ object lifetime, rule of 0/3/5
*Reviewed by the daily run, Thu 2026-10-22, from commit 9546807.*

**Verdict:** Real progress. Both sliding-window problems are correct and unaided, and every line of `Buffer`
is yours: the destructor, deep copy, move and copy-and-swap the tutor wrote for you on Day 001. The gaps are
speed (643 is an Easy that took 20 min), a debug `print` left in, and recall of complexity (dsa-004 slipped back).

| Block | Score (1–4) | Why |
|---|---|---|
| DSA | **3** | Both correct and unaided. 2958: approach + amortized O(n) stated before coding, inside its 20-min timer. 643: 20 min on a 10-min timer, and the pre-code analysis dismissed the running sum (the actual answer) as "weak". |
| C++ | **3** | 21/21 green (drill 6/6, TODOs 3/3, 3/3, 4/4, 4/4, 2/2) under ASan+UBSan, all written by you. −1: ~65 min vs 45 planned, syntax slips, and TODO 5 needed concept hints. |

How I checked: re-ran `./run.sh 003 sys` (g++, ASan+UBSan; clang's ASan runtime is missing on the review box):
all green, no warnings under `-Wall -Wextra -Wpedantic`. Ran both DSA files on the LeetCode examples, edge
cases, and 2,000 random inputs each against a brute force: all match.

## DSA

### 643. Maximum Average Subarray I (`dsa/p643.py`)
**Right:** running sum, one pass, divide once at the end. `max_sum = float('-inf')` handles all-negative input
(checked `[-5,-5,-5], k=2` → −5.0). Correct on `n = 1`, `k = n`, all-equal.

**Wrong / fix:**
1. **Line 22: `print(curr_sum)` left in.** On n = 10⁵ it prints 99,997 lines. LeetCode tolerates it (slowly);
   in a CoderPad screen it reads as unfinished code, and on a HackerRank OA stdout noise can fail an
   output-graded problem. Delete before you submit. Make it a habit: scan for `print` before "run".
2. Lines 6–9: `if k > n: k = n` then `k = min(n, k)` do the same thing twice, and the contract says
   `1 ≤ k ≤ n`, so neither is needed. Pinning the contract first tells you what *not* to write.
3. Lines 19–21: the `for i in range(1, n)` + `break` is `for i in range(1, n - k + 1)`. Same result, no break.
4. **Process:** before coding you said the running sum was weak "because of division cost". Wrong: it removes
   the k factor (O(n·k) → O(n)), and you divide once at the end, not per window. (New qa: dsa-008.)

### 2958. Longest Subarray With at Most K Frequency (`dsa/p2958.py`)
**Right:** a correct variable window. Each loop iteration moves either `left` or `right`, so there are at most
2n iterations: O(n), and you said so before coding. n = 10⁵ runs in 0.03 s.

**Clarity (an interviewer reads it):**
- `curr_good` always equals `right - left`; drop it and use `max_good = max(max_good, right - left)`.
- Lines 25–30: `curr_state[x] = curr_state.get(x, 0) + 1` (or `collections.Counter`) replaces the if/else.
- The shape most interviewers expect is `for right` + inner `while count[x] > k: shrink`. Yours (one step per
  loop) is equivalent, but the standard shape is easier to defend under questioning.

**Missed edge cases:** none that break it. You didn't *list* `k ≥ n` (answer = n) or n = 1 before coding.

## C++: `Buffer` and `Level` (`systems/challenge.hpp`)
**Right:**
- `~Buffer() { delete[] data_; }`: the `[]` matches `new int[n]`.
- Copy ctor: handles size 0 (keeps the invariant), allocates its own array, `std::copy(first, last, dest)` in
  the right order this time.
- Move ctor: `noexcept`, no allocation, leaves the source empty. Null-then-swap is correct.
- `operator=`: textbook copy-and-swap, both members swapped.
- `Level`: you fixed it by **deleting** the hand-written copy ctor. That is the rule of zero.

**Style, not bugs:**
- Copy ctor and move ctor assign in the body. Members are first default-initialized, then assigned. For
  `int*`/`size_t` that costs nothing, but for a `std::string` member it would construct twice, and a `const` or
  reference member can't be assigned at all. The init-list form you drilled in D5:
  `Buffer(Buffer&& o) noexcept : data_(std::exchange(o.data_, nullptr)), size_(std::exchange(o.size_, 0)) {}`.

**Your test_5 answer** ("not sure if std::move() would do anything") was the concept gap: the hand-written
copy ctor *suppressed* the implicit move ctor, so `std::move(level)` picked the copy ctor (an rvalue binds to
`const Level&`), which then copied `qtys` instead of stealing it. Delete the copy ctor → all five generated →
moves are moves again. This is retested in the Day 004 warm-up (cpp-ml-004).

## Recall
| Q | When | Verdict | Correction |
|---|---|---|---|
| cpp-om-011 virtual dtor | Tue | partial | Chaining right. Missing: `virtual` makes `delete base_ptr` start at `~Derived`; without it only `~Base` runs (UB). |
| cpp-ml-001 move ctor via `void*` | Tue | partial | Idea right. `this.obj_` → `this->obj_`; add `noexcept`. Clone+delete allocates and can throw. |
| dsa-006 `(price, Order)` heap tie | Tue | wrong | Tuples compare element-wise → compares `Order`s → `TypeError`. Fix: `(price, seq, order)`, or push only the price. Retested today. |
| cpp-om-014 `-6 > size_t(0)` | Wed | partial | It's **true**: −6 converts to 2⁶⁴ − 6. Fix: keep it signed; `-Wsign-compare` flags it. |
| cpp-om-013 struct vs class | Wed | mostly right | Also default **public inheritance** for struct, private for class. |
| dsa-004 Group Anagrams complexity | Wed | wrong (repeat) | O(n · k log k). The k log k is one sort; you do n of them. Monday you said it right; it hasn't stuck yet. |

## Error log (from the session; `notes.md` had no error-log section)
- D1: missing `{}` → `new int[n]` not zeroed
- D3: end pointer `src + 2` for 3 elements (off by one: `last` is one *past* the end)
- TODO 2: `std::copy` arguments reversed (wrote into the const source) — **repeats** the open C++ syntax weak area
- TODO 2/3: `data_(x);` inside the ctor body (init-list syntax in the body) — **repeats** C++ syntax
- Unfinished line broke every test build (all tests include the one header) → finish a line before running
- TODO 5: didn't know a user-declared copy ctor suppresses the move ctor — **repeats** "move semantics" weak area
- 643: dismissed the running sum because of division; left a debug print
- dsa-004: complexity slipped back to O(n log k) — **repeats** "complexity with two sizes"

## Interviewer follow-ups
<details><summary>1. "2958, but now return the subarray itself, and k may be 0." What changes?</summary>

Track `best_left` whenever `right - left` beats the max; return `nums[best_left:best_left + best]`. With k = 0
no element may appear at all, so the answer is 0: ask whether that's allowed or whether the
contract says `k ≥ 1` (LeetCode's does). Your code returns the wrong answer there: `good()` treats a missing
count as "fine", so every new element gets in once. I ran it: `[1,2,3], k=0` → 3 and `[1,1], k=0` → 1 (both
should be 0). Pinning `k ≥ 1` in the contract is what makes your version correct.
</details>

<details><summary>2. "In your Buffer, what does <code>a = std::move(b)</code> cost? And <code>a = b</code>?"</summary>

`a = std::move(b)`: `other` is move-constructed from `b` (two pointer/size copies, no allocation), then two
swaps, then `~other` frees `a`'s old array: one `delete[]`, no `new`. `a = b`: `other` is copy-constructed
(one `new int[n]` + an O(n) copy), swap, then `~other` frees the old array. Copy-and-swap always allocates on
copy, even if `a` already had room; `std::vector`'s copy assignment reuses capacity for that reason.
</details>
