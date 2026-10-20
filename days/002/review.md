# Day 002 review: arrays/hashing (121, 49) · order book part 1
*Reviewed by the daily run, Tue 2026-10-20, from commit d82ad9f.*

**Verdict:** 49 was interview-speed (about 9 min, no hints). The order book has the right data model,
but the code passes 1/12 tests. It also has a bug the 12 tests don't catch, and a hidden-test OA would.

| Block | Score (1–4) | Why |
|---|---|---|
| DSA | **3** | 49: correct, about 9 min, no hints. Lost points before coding: complexity said as n² log n, and the input contract missed `[]` and duplicates until prompted. 121 (Oct 15, C++, 1 hint): `size_t` profit bug. |
| Design (order book) | **2** | Right structures (heap of prices, one FIFO per level, id map), but 1/12 green after ~40 min. Asks/bids were swapped in 3 places and errors were raised where the spec says `return False`. Complexity notes and confidence left blank. |

Score 2 on design means remediation, and that is tomorrow: **Day 004 is order book part 2 (finish to 12/12)**.
Start it by fixing the bug below. That's the first thing tomorrow's lesson will ask for.

## DSA

### 49. Group Anagrams (`dsa/p49.py`)
**Right:** a sorted word as the canonical key; a dict from key to group; one pass. Correct on `[]`, `[""]` and
duplicates (I re-ran your file on all three). Complexity in the file header is now right: O(n · k log k).

**Clarity fixes (an interviewer reads the code):**
- Line 13: `if not anagram_base in anagram_dict` → write `if anagram_base not in anagram_dict`. Both work, but
  `not in` is the idiom, and `not x in d` reads like `(not x) in d`.
- Lines 13–16: the if/else goes away with `collections.defaultdict(list)` and a plain `groups[key].append(word)`.
- Lines 18–21: the copy loop is `return list(anagram_dict.values())`.

**Process (the part Citadel grades):** you called the sorted-key approach "brute force". The brute force is
pairwise comparison, O(n² · k). Say that first: it's what makes the optimization visible (dsa-004).

### 121. Best Time to Buy and Sell Stock (Oct 15, C++)
Solved with one level-1 hint. The bug was `size_t` for a profit that goes negative: −6 became 18446744073709551610
(cpp-om-014). In Python this class of bug can't happen. In the C++ debugging round it's a favorite.

## Design: order book part 1 (`design/orderbook.py`)

**Right:**
- A per-level `dict` (order_id → qty) is a good FIFO choice. Python dicts keep insertion order, so the queue is
  `list(level)`, cancel is `del level[id]` in O(1), and "lose priority" is delete + re-insert. This is a
  better structure than a list or deque per level. Keep it.
- One heap entry per *level*, not per order, so there's no `(price, Order)` tie problem (dsa-006).
- Post-only crossing check in the right direction for both sides (`test_post_only_rejects_crossing` passes).

**Wrong (cite lines):**
1. **A rejected order still takes its id.** Line 51 (`self.orders[order_id] = order`) runs before the
   crossing check (lines 54, 65) and before the side check (line 74). Reproduced:
   ```
   add(20, "B", 101, 1)  → False  (crosses, correct)
   add(20, "B", 100, 1)  → False  (WRONG: id 20 is not resting; should be True)
   add(30, "X", 97, 1)   → False  (correct) ... then add(30, "B", 97, 1) → False (WRONG)
   ```
   None of the 12 tests catches this; a hidden-test grader would. **Minimal fix:** move that one line to just
   before `return True` (validate everything, then mutate). Rule: *no state change until every check has passed.*
2. **Two copies of the quantity.** `Order.qty` and `level[order_id]` both hold it, so modify has to update both,
   and the first time it doesn't, depth is wrong. Minimal fix: store the `Order` in the level
   (`level[order_id] = order`) and read `order.qty` everywhere.
3. **`best_bid()` / `best_ask()` will go stale after cancel** (lines 94–106). The heap still holds a price whose
   level emptied. Part 2 needs it: pop while the top price has no level (lazy deletion), *then* read the top.
4. Line 47: `if self.orders.get(order_id)` → `if order_id in self.orders`. `.get` works here only because an
   `Order` object is truthy. If you ever store a qty there, an id with value 0 looks absent.
5. Lines 54/65: `self.best_bid() and self.best_bid() >= price` works only because prices are > 0. Compare
   with `is not None`, and call it once.
6. Lines 84–90: the modify docstring sits *between* the methods, so it's not attached to `modify`. Line 40: stray `pass`.

**Missed edge cases:** an id reused after a rejection (above) · an id reused after a cancel (test exists, red) ·
a cancel that empties the best level, then `best_*` (stale heap) · `depth(side, 0)` and `levels` > number of levels.

## Recall (marked live on Oct 19)
| Q | Verdict | Correction |
|---|---|---|
| cpp-om-001 virtual call walk-through | partial | The slot holds the **object's real class's** function, not the base reference's. The lookup is generated code running at runtime (load vptr → load slot → indirect call). The compiler doesn't search anything at that point. |
| cpp-om-003 virtual call in a ctor | right, no "why" | During `Base()` the vptr points at **Base's** vtable (the Derived part isn't built yet), so dispatch finds Base's version. |
| cpp-om-012 cast from `const void*` | right cast | Exact form: `static_cast<const Circle*>(s)`. Pointer target, keep `const`. |

## Interviewer follow-ups
<details><summary>1. "Group Anagrams, but words are Unicode and up to 10⁵ chars. Which key now?"</summary>

The 26-count tuple assumes lowercase a–z, so it breaks. The sorted-string key works for any alphabet at
O(k log k). For O(k) on any alphabet: `frozenset(Counter(w).items())` (hashable, order-free). Say the
assumption ("lowercase English?") out loud *before* picking the key. That's the input-contract habit.
</details>

<details><summary>2. "Cancel just emptied the best bid level. Walk me through best_bid() in your design, with its complexity."</summary>

The heap still has −price at the top. `while heap and -heap[0] not in bids_by_price: heappop(heap)`, then
return `-heap[0]` or None. Each price is pushed once per time its level is created and popped at most once,
so it's amortized O(log L) (L = number of levels). Alternative: delete the empty level eagerly from a
sorted structure (`SortedDict` isn't stdlib), or index an array by price offset near the touch.
</details>
