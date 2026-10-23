# Day 004 review: order book part 2 (A1)
*Reviewed by the daily run, Fri 2026-10-23, from commit 7a88d5a.*

**Verdict:** The order book is built. 16/16, every line yours, no debug prints, and the Day 002 bug
(a rejected order kept its id) is found, explained in your own words and fixed. Two hidden problems remain,
both from the same habit: the tests pass, but you didn't ask "what happens at scale?" `best_bid()` crashes
after ~1,000 cancels, and `modify` makes the heap grow forever.

| Block | Score (1–4) | Why |
|---|---|---|
| Design | **3** | Correct on all 16 tests, unaided apart from the wording issues (the spec's fault, now fixed in the calibration notes). −1: ~75 min of coding vs 35 planned, the complexity and error-log sections of `notes.md` are empty, and two scale bugs (below) that an interviewer would find with one question. |

How I checked: `./run.sh 004` → 16/16. Then three extra scripts against your `orderbook.py` (output pasted below).

## What's right
- **Validate, then mutate** (`add`, lines 54–74): every check runs before `self.orders[order_id] = order`.
  That is the rule from Monday's review, applied without being reminded where.
- **One copy of the quantity:** the level stores the `Order` itself, so `modify` down is one assignment.
- **`depth()` reads prices from the dict keys, not the heap.** The heap is unordered and holds stale and
  duplicate prices; you worked that out live. This is the step most people get wrong.
- `cancel` deletes the emptied level, so `depth` never shows a 0-quantity level.
- Lazy deletion in `best_*`: drop heap prices whose level is gone. Right idea.
- Modify up = move to the back; modify down keeps the place. Matches the spec and real exchanges.

## What's wrong (cite lines; minimal fix each)
1. **`best_bid()` / `best_ask()` recurse once per stale price (lines 141–162).** Python stops a recursion at
   about 1,000 calls. 3,000 bid levels, all cancelled, then `best_bid()`:
   ```
   RecursionError maximum recursion depth exceeded in comparison
   ```
   A real book sees thousands of cancels per second, so the top of the heap can hold thousands of stale
   prices. Fix: the loop from Thursday's worked example, `while self.bids and -self.bids[0] not in self.bids_by_price: heapq.heappop(self.bids)`,
   then return the top or `None`. Rule: **in Python, never recurse to skip items; loop.**
2. **`modify` up = `cancel` + `add` (lines 133–134) pushes the price into the heap again every time.**
   One bid at 99, increased 1,000 times:
   ```
   heap len 1001 best 99 [1] [(99, 1001)]
   ```
   The answers stay right, but the heap holds 1,001 copies of 99 and never shrinks while the level is
   alive: memory grows with every modify. Fix: don't leave the level. Use the "move a key to the back" idiom
   from Thursday's worked example: `level.pop(order_id)`, set `order.qty`, `level[order_id] = order`. No heap
   touch, O(1).
3. **Line 134 ignores `add()`'s return value.** Today `add` can't fail there, but with matching (next
   Wednesday) the re-add path changes, and a False would mean the order vanished while `modify` returns True.
   Fix 2 removes the call. General rule: if a call can fail, check it or prove it can't.

**Clean-ups (not bugs):** unused `from functools import reduce`; the `pass` in `__init__`; the unreachable
`else: return False` at line 88 (the side was already checked); `if not self.asks_by_price.get(price)` →
`if price not in self.asks_by_price`; `queue` is `list(book[price])`; `depth` treats any side that isn't
`"B"` as asks (fine for the spec, but say so).

## Missed edge cases
- Many cancels in a row (bug 1) and repeated modify-ups (bug 2). Both are "real traffic" cases: ask
  "what does a million of these do?" before calling a design done.

## Recall (Thursday warm-up and recap)
| Q | Verdict | Correction |
|---|---|---|
| sd-005 price level | partial | Definition right; example mixed two prices, and a *reduce* keeps priority. |
| dsa-006 heap tie | partial | Fix right; cause is tuple comparison falling through to `Order < Order` → `TypeError`. |
| cpp-ml-004 rules of 3/5/0 | partial | Missing: declaring a copy ctor, copy assignment or destructor suppresses the moves. |
| sd-006 rejected order keeps its id (recap 1) | **right** | Line, trace, return values and the fix, all correct. |
| Recap 3: `best_ask()` after cancelling the best level | partial | Said what it *should* return; the code at that point returned 101 (a stale price). |

## Error log
`notes.md` has no error log or complexity section for the build (you were tired; noted, not a penalty
beyond the −1 above). From the session record:
- Read the depth prices from the heap (unordered, stale) — **repeats** the order-book weak area
- Read "rejected (use cancel)" as "call cancel" — spec wording, fixed in calibration
- Fixed this time: validate-before-mutate (closes the evidence for sd-006)

## Interviewer follow-ups
<details><summary>1. "Now trades happen: a buy for 10 at 102 arrives; the book has asks of 4 @ 101 and 8 @ 102. Walk me through which structures change, in order."</summary>

Loop while the order has quantity and `best_ask() <= 102`: take the **first** order in the best level (FIFO:
`next(iter(level))`), trade `min(remaining, resting.qty)`. Fill 4 @ 101: remove that order from the level and
from the id map; the level is empty → delete it (the heap entry goes stale and is skipped later). Then 6 @ 102:
the resting order drops to 2, keeps its place. Remaining 0 → nothing rests. If quantity were left, rest it at
102 on the bid side. That is A2 next Wednesday.
</details>

<details><summary>2. "A UI calls depth('B', 5) on every update. Yours sorts every price level each call. Make it cheaper."</summary>

Now it's O(L log L) per call. Options: (a) a sorted container of prices (C++ `std::map`, iterate 5 from
`begin()`: O(5) after O(log L) inserts; Python needs `sortedcontainers`, not stdlib); (b) `heapq.nsmallest(5, keys)`
is O(L log 5), better but still O(L); (c) prices are ticks in a narrow band near the touch, so an array
indexed by `price − base` makes the next level a short scan. Real books use (a) or (c).
</details>
