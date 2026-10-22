# Day 004 — Design: order book, part 2 (finish to 16/16)
**Thu Oct 22 · 60 min** · Warm-up 5 · Recap + bug fix 10 · Build 35 · Error log 10

> **Why today.** "In-memory order book with price-time priority, level aggregation and cancel" is the
> design question reported most often for Citadel Securities, and their onsite grades code that **runs and
> is correct on real input**. Part 1 (Mon Oct 19) got the data model right and 1/12 tests green. Today you
> finish it. The matching engine (A2) builds on this book next Wednesday, so a correct book now saves you there.

Review of Day 003 is in `days/003/review.md`. Headline: **sliding window 643 + 2958 both correct and
unaided, Buffer 21/21 green with every line written by you.** The single biggest fix: leave no debug
`print` in submitted code (your 643 prints 99,997 lines on n = 10⁵).

---

## 0. Warm-up (5 min)
Answer from memory in `notes.md`, then check the answers in `qa/`.
1. What is a "price level" in an order book, and what does "moves to the back of its price level" mean?
   Give a 2-order example. (sd-005)
2. In Python, `heapq.heappush(heap, (price, order))` where `order` is an instance of your own `Order` class.
   You push two orders with the same price. What error do you get, why, and how do you fix it? (dsa-006)
3. State the rules of 3, 5 and 0. Which declarations stop the compiler from generating the move operations? (cpp-ml-004)

---

## 1. Recap + the bug first (10 min). This is the remediation for Monday's design score of 2.
`days/004/design/orderbook.py` is **your Day 002 code, copied verbatim** under an updated spec.
Read your `add()` (5 min) and write the answers in `notes.md` **before** changing anything:

1. A rejected order: which line in `add()` makes it keep its id? Trace `add(20, "B", 101, 1)` (rejected, crosses)
   followed by `add(20, "B", 100, 1)`. What does the second call return now, and what should it return?
2. Where is an order's quantity stored? Count the places. What has to stay in sync when `modify` runs?
3. **Predict:** after `cancel(3)` removes the only order at 101 (the best ask), what does your current
   `best_ask()` return, and why?

Then make these fixes (5 min). They are the review's #1, #2, #4 and #5; nothing else yet:
- **Validate everything, then mutate.** Move `self.orders[order_id] = order` so it runs only after every check
  has passed (side, crossing). Rule for the rest of your career: *no state change until every check has passed.*
- Store the `Order` itself in the level (`level[order_id] = order`), not `qty`. One copy of the quantity.
- `if order_id in self.orders`, not `.get(...)`; compare best prices with `is not None`, and call `best_*()` once.

The test for this bug (`test_rejected_add_does_not_take_the_id`) also uses `cancel` and `depth`, so it turns
green at step 2 below, not now.

---

## 2. Build (35 min): three steps, each ends at a test count
```bash
./run.sh 004
```
Work in this order. Don't start a step until the previous count is green.

| Step | Methods | Green when | Time box |
|---|---|---|---|
| A | `queue(side, price)`, `depth(side, levels)` (read-only, no state change) | **8/16** | 10 min |
| B | `cancel(order_id)` + `best_bid()`/`best_ask()` that skip emptied levels | **12/16** | 15 min |
| C | `modify(order_id, new_qty)` | **16/16** | 10 min |

The 16 = Monday's 12 + 4 new ones (bottom of `test_orderbook.py`): a rejected id must stay free; depth with 0 or
too many levels; a best level that empties and refills at the same price; modify then cancel.

**Before each step**, say in one line in `notes.md` what the method does to each structure (heap, levels dict,
id map). That's the "design survives implementation" part interviewers grade.

**Predict before step B:** a price level empties and a new order arrives at the same price before anyone calls
`best_bid()`. How many copies of that price are in your heap now? If `depth()` read its prices from the heap,
what would `test_best_level_emptied_then_refilled` see?

### Worked examples: every Python idiom today needs (a different problem: a restaurant waitlist)
From `scratch/day004_worked.py`, which runs (`python3 scratch/day004_worked.py`). Type them, don't copy.
```python
waitlist = {}                          # dict = FIFO: keys stay in insertion order
waitlist["ana"] = 2; waitlist["bo"] = 4; waitlist["cy"] = 3
list(waitlist)                         # ['ana', 'bo', 'cy']   keys, in arrival order
if "bo" in waitlist:                   # membership: `in`, never .get() for a yes/no
    del waitlist["bo"]                 # remove from the middle, O(1) average
size = waitlist.pop("ana")             # move a key to the back:
waitlist["ana"] = size + 1             #   pop it, insert it again → ['cy', 'ana']

del sections["patio"]["dee"]           # inner container empties...
if not sections["patio"]:              # ...empty dict is falsy...
    del sections["patio"]              # ...so delete it; nobody should ever see an empty one
sections.get("patio", {})              # {} when the key is missing

latest = []                            # lazy deletion on a max-heap (push the negative)
for h in booked: heapq.heappush(latest, -h)
booked.discard(20)                     # cancel: the heap still holds -20 (heaps can't delete from the middle)
while latest and -latest[0] not in booked:
    heapq.heappop(latest)              # drop stale entries only when they reach the top
-latest[0] if latest else None         # 19

top = sorted(tables, reverse=True)[:2]                      # top n keys, largest first
[(s, sum(tables[s].values())) for s in top]                 # (key, total) pairs
sorted(tables, reverse=True)[:0]                            # [] — slicing never raises
```

**Stop rule:** at 50 minutes, stop at the last green milestone and write where you are in `notes.md`.
Stuck 5+ min on one step → `/hint` in Claude Code (it escalates fast: pseudocode by the 2nd ask).

### After it's green (5 min, in `notes.md`)
Write the complexity of each op in *your* version. L = levels on a side, k = orders at one level, n = orders.
`add · cancel · modify (down / up) · best_bid · depth(m) · queue`. Then answer: which op dominates a real feed,
and is it fast in your design?

### What interviewers push on
- "Cancel is most of the traffic. What does yours cost?" → dict deletes are O(1) average; the heap isn't
  touched at all (the stale price is paid for later, once).
- "Why is `best_bid()` with a `while` loop not O(L) per call?" → each price is pushed once per time its level is
  created and popped at most once: amortized O(log L). Same argument as the sliding window's inner loop.
- "Your `depth` sorts every call: O(L log L). Make it faster." → a sorted container of prices (not stdlib in
  Python; `std::map` in C++), or an array indexed by `price − base` near the touch: O(1) to step to the next level.
- "Same order id on the other side?" → it's a duplicate: ids are unique across the whole book, not per side.

---

## 3. Optional deep dive
- [How to Build a Fast Limit Order Book (WK Selph)](https://gist.github.com/halfelf/db1ae032dc34278968f8bf31ee999a25):
  now that yours works, compare: a tree of levels + a doubly linked list per level + id map. What does each choice buy?
- [Python `heapq` docs](https://docs.python.org/3/library/heapq.html), section *Priority Queue Implementation
  Notes*: the official version of today's lazy deletion (mark removed, skip on pop).

---

## 4. Notes: create `days/004/notes.md`
```markdown
## Warm-up recall (from memory)
1.
2.
3.
## Recap (before changing code)
1. Line that keeps a rejected id: ... · second add returns now: ... should: ...
2. Places qty is stored: ...
3. Predict best_ask() after cancel(3): ...
## Build
- Predict (before step B): copies of the price in the heap: ... · depth-from-heap would show: ...
- Step A: what each method does to heap / levels / id map: ...
- Step B: ...
- Step C: ...
- Tests: A _/16 at __ min · B _/16 at __ min · C _/16 at __ min
## Complexity of my version
add: ... cancel: ... modify down/up: ... best_bid: ... depth(m): ... queue: ...
Dominant op on a real feed, and its cost here: ...
## Error log (one line per mistake)
-
## Confidence (1–5): order book __
## Questions
```
Then `git add -A && git commit -m "day 004" && git push`.
