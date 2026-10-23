# Day 005 — Baseline quiz
**Fri Oct 23 · ~40 min** · Warm-up 5 · Timed problem 25 · Rapid recall 10

> **Why today.** The Citadel Securities screen is one problem in ~45 min on CoderPad, and the code has to run
> and pass edge cases; the online test grades hidden tests with almost no partial credit. This quiz measures
> where you are *today*, under a timer, with no help. It's a **baseline**: it gets a score and a log row, but it
> doesn't count toward the screen-ready checkpoint. Low scores here are useful, not bad news.

Review of Day 004 is in `days/004/review.md`. Headline: **the order book is built: 16/16, every line yours,
and Monday's bug (a rejected order kept its id) found and fixed.** The single biggest fix: `best_bid()` calls
itself once per stale price, so ~1,000 cancels in a row crash it with `RecursionError`. Loop instead.

**Rules for the whole quiz:** no hints, no `/hint`, no notes, no searching. Write down the real times.

---

## 0. Warm-up (5 min)
Answer from memory in `notes.md`.
1. You're about to start coding in an interview. Which four things do you say out loud first? (dsa-003)
2. An order has priority at its price. The trader **increases** its quantity and it goes to the back of the line;
   if they **decrease** it, it keeps its place. Why does the exchange treat the two differently? (sd-004)
3. Why should a C++ move constructor be marked `noexcept`? What does `std::vector` do when it grows if the move
   constructor isn't `noexcept`? (cpp-ml-002)

---

## 1. Timed problem (25 min, no hints)
**LeetCode 438. Find All Anagrams in a String** (Medium):
<https://leetcode.com/problems/find-all-anagrams-in-a-string/>

Given two strings `s` and `p`, return the start index of every substring of `s` that is an anagram of `p`
(the same letters, the same number of times, in any order). Any order of the indices is fine.

```
s = "cbaebabacd", p = "abc"  →  [0, 6]     ("cba" at 0, "bac" at 6)
s = "abab",       p = "ab"   →  [0, 1, 2]
```

Work in `days/005/dsa/p438.py`. Run it with `python3 days/005/dsa/p438.py`.

1. Write your **start time** at the top of the file. Start the 25-min timer.
2. Before any code, as comments: restate the problem, the input contract (what can `s` and `p` contain, how long
   can they be, what if `p` is longer than `s`?), the brute force and its complexity, then your plan and its
   complexity. Name every size you use.
3. Code it. Test it on the two examples **plus at least three edge cases you pick**, by hand or with `print`.
4. Remove debug prints. Write your **end time**. If the timer ran out, stop and write where you are.

You may submit it on LeetCode after you stop the timer. It's graded on: correct, ≤ 25 min, unaided, contract
and complexity written before coding, edge cases tested.

---

## 2. Rapid recall (10 min, one line each)
No looking anything up. Answers are in `qa/` (ids in brackets); check them **after** you've written all ten.

1. A sliding window has a `while` loop inside its `for` loop. Why is it still O(n) and not O(n²)? (dsa-007)
2. Max average of any length-k window in an array of n numbers: brute-force complexity, the better idea, and
   where the division goes. (dsa-008)
3. Group Anagrams by sorting each word: n words, each up to k letters. Total time? (dsa-004)
4. Can a Python dict or list be a dict key? What do you use as the key for "this word's letter counts"? (dsa-005)
5. `heapq.heappush(h, (price, order))` with your own `Order` class, two orders at the same price: what error,
   and why exactly? (dsa-006)
6. A heap of prices backs `best_bid()`. A cancel empties the best price level. How does `best_bid()` stay right
   without deleting from the middle of the heap? (sd-007)
7. A Python dict holds one price level's orders in arrival order. How do you move one order to the back? (sd-009)
8. Why does an order book store prices as integer ticks, not floats? (sd-002)
9. In C++, which declarations stop the compiler from generating a class's move constructor and move
   assignment? (cpp-ml-004)
10. `int x = -6; size_t y = 0;` Is `x > y` true or false, and why? (cpp-om-014)

---

## 3. Notes: create `days/005/notes.md`
```markdown
## Warm-up recall (from memory)
1.
2.
3.
## Timed problem: 438
- Start: __:__  End: __:__  (minutes: __)
- Unaided? yes / no
- Contract + complexity written before coding? yes / no
- Edge cases I tested:
- Final complexity (time, space):
## Rapid recall (one line each)
1.
2.
3.
4.
5.
6.
7.
8.
9.
10.
Self-check against qa/: __/10
## Error log (one line per mistake)
-
## Confidence (1–5): this kind of problem __ · recall __
## Questions
```
Then `git add -A && git commit -m "day 005" && git push`.
