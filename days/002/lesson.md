# Day 002 — Arrays & hashing · Order book fundamentals
**Mon Oct 19 · 60 min** · Warm-up 5 · DSA 30 · Design 25

> **Why today:** Citadel Securities screens are LeetCode-style problems with a trading flavor.
> The design topic that comes up most in their reports is the **limit order book**: one candidate
> got an "order book" coding problem in the screen, and prep sites list "in-memory order book with
> price-time priority, level aggregation and cancel" as an onsite question.

---

## 0. Warm-up (5 min)
**Recall (answer from memory in `notes.md`, then check `qa/cpp-object-model.md`):**
1. Walk me through a virtual call through a base reference (cpp-om-001).
2. What does a virtual call inside a constructor dispatch to, and why? (cpp-om-003)
3. You have a `const void*` that points at a `Circle`. Which cast gets you a usable pointer? (cpp-om-012)

**Then read this once and use it on every problem from now on:** Reported Citadel rejections came from **missed edge cases**
(self-loops in a currency graph) and **the wrong traversal** (DFS where BFS was needed).

1. Restate the problem in one sentence.
2. Pin down the input contract: types, bounds, empty input, duplicates, negatives.
3. Say the brute force and its complexity out loud.
4. Optimize; say the new complexity.
5. Code it, then walk through 2 test cases by hand, including one edge case.

---

## 1. DSA (30 min): arrays & hashing, "stock" pattern
Set a timer for each problem. Solve in Python, on LeetCode. **No looking at hints or solutions.**
If you're stuck at minute 20, use `/hint` in Claude Code instead (it escalates one level at a time).

| # | Problem | Timer | Why it's here |
|---|---|---|---|
| 1 | [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) (Easy) | 10 min | The "stock" family is listed among Citadel's tested patterns |
| 2 | [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/) (Medium) | 20 min | Reported Citadel question: "unique words when characters can be rearranged" |

**Stretch:** [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)

Before coding each one, write in `notes.md`: the brute force, its complexity, and the edge cases.
Optional: save your solution as `days/002/dsa/p121.py` etc. so the review can read your code.

---

## 2. Design (25 min): the interview framework + limit order book

### The framework (use it in every design answer)
1. **Requirements:** functional (what ops) and non-functional (latency, throughput, durability,
   determinism). *Ask* about scale: messages/sec, symbols, order count.
2. **API:** the exact operations and events in and out.
3. **Data model:** the structures, and the complexity of each op.
4. **Hot path:** walk one message end to end. Where is time spent? What allocates?
5. **Scale & failure:** sharding, replication, recovery, a crash mid-operation.
6. **Trade-offs:** what you chose *and what you gave up*.

### Limit order book
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
- **Ops:** add, cancel, modify (reducing quantity keeps priority, increasing loses it),
  best bid/ask, depth. Matching against incoming orders comes on Day 004.
- **Priority:** price first, then time (FIFO within a level).
- **Prices are integer ticks**, never floats. Floating-point equality breaks level lookup, and
  "floats for prices" is a pitfall flagged in Citadel prep reports.
- **Scale:** a full US equities feed carries millions of messages per second at peak, and most
  are **adds and cancels**, not trades, because most orders never execute. So cancel must be fast.

### What interviewers push on
- "Which op is most frequent?" → cancel. Design for it.
- "How do you find an order by id?" → hash map from id to the order (or its location).
- "How do you find the best price?" → a sorted structure, or an array indexed by price offset near the touch.
- "Why does increasing quantity lose priority?" → otherwise you could park a tiny order at the front
  of the queue and size it up later, which is unfair to everyone waiting at that price.

### Challenge: `design/orderbook.py`
```bash
./run.sh 002
```
Implement the passive (post-only) book against the spec in the docstring. Get it correct with any
structures you like, then **write the time complexity of each operation in `notes.md`**.
Day 004 adds matching and makes it fast.

---

## 3. Deep dive (optional)
- [How to Build a Fast Limit Order Book (WK Selph)](https://gist.github.com/halfelf/db1ae032dc34278968f8bf31ee999a25):
  the classic short write-up. Read it **after** the challenge.

---

## 4. Notes: create `days/002/notes.md`
```markdown
## DSA log
| Problem | Time | Solved without hints? | Brute force → optimal | Edge cases I listed | What tripped me up |
|---|---|---|---|---|---|
| 121 | | | | | |
| 49  | | | | | |
## Order book: complexity of my version
add: ... cancel: ... modify: ... best: ... depth: ...
## Confidence (1–5): DSA __ · order book __
## Questions
```
Then `git add -A && git commit -m "day 002" && git push`.
