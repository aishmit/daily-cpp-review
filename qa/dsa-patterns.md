# DSA patterns — Q&A

### Q: Best Time to Buy and Sell Stock (one trade): what's the O(n) idea, and what's the edge case people miss?
`id: dsa-001` · `from: day 002` · `confidence: low` · `last: —` · `next: day 003`

<details><summary>Answer</summary>

One pass, tracking the minimum price so far; at each day, profit = price − min_so_far; keep the max.
O(n) time, O(1) space. Edge cases: prices only falling → answer 0 (don't return a negative); a single day → 0.
</details>

### Q: How do you group anagrams in O(n·k)? What's the key?
`id: dsa-002` · `from: day 002` · `confidence: low` · `last: —` · `next: day 003`

<details><summary>Answer</summary>

Hash map from a canonical key to a list of words. Key = a tuple of 26 letter counts (O(k) per word),
or `''.join(sorted(w))` (O(k log k)). Edge cases: empty strings (all group together), duplicate words.
</details>

### Q: Before writing any code in an interview, what 4 things do you say out loud?
`id: dsa-003` · `from: day 002` · `confidence: low` · `last: —` · `next: day 003`

<details><summary>Answer</summary>

(1) The problem restated in one sentence, (2) the input contract (types, bounds, empty, duplicates,
negatives, self-loops), (3) the brute force and its complexity, (4) the optimized approach and its
complexity. Then code it, then trace 2 cases by hand, including an edge case.
</details>

### Q: Group Anagrams with the sorted-word key: what's the complexity? Name your variables.
`id: dsa-004` · `from: day 002` · `confidence: low` · `last: 2026-10-21 recall: said O(n log k); dropped the k factor again` · `next: day 006`

<details><summary>Answer</summary>

Two sizes: n = number of words, k = max word length. Sorting one word is O(k log k); doing it for every
word is **O(n · k log k)**, plus O(n · k) for the map. A 26-count key makes it O(n · k). The habit: when an
input has two sizes, give them two letters. Mixing them into one "n" gives a wrong (and scary) answer.
</details>

### Q: In Python, can a dict (or list) be a dict key? What do you use for a "letter counts" key?
`id: dsa-005` · `from: day 002` · `confidence: low` · `last: 2026-10-19 (proposed a dict of counts as the key)` · `next: day 003`

<details><summary>Answer</summary>

No: keys must be hashable, and dicts/lists are mutable, so `d[{'a': 1}]` raises
`TypeError: unhashable type: 'dict'`. Use a tuple: `tuple(counts)` where `counts` is a 26-slot list
(`counts[ord(c) - ord('a')] += 1`). Building it is O(k); hashing a fixed 26-tuple is O(1).
Group Anagrams becomes O(n · k).
</details>

### Q: In Python, `heapq.heappush(heap, (price, order))` where `order` is an instance of your own `Order` class. You push two orders with the same price. What error do you get, why, and how do you fix it?
`id: dsa-006` · `from: day 002` · `confidence: low` · `last: 2026-10-22 recall: fix right; cause wrong (said 'key already used', not tuple comparison falling through to Order)` · `next: day 009`

<details><summary>Answer</summary>

Tuples compare element by element, so a tie on price falls through to comparing the `Order` objects:
`TypeError: '<' not supported between instances of 'Order' and 'Order'`. Fixes: push a unique
tie-breaker second, `(price, seq, order)` with an increasing `seq` (also gives FIFO), or for an order
book push only the *price*, once per new level, and keep the orders in a per-price FIFO.
</details>

### Q: When does a variable-size sliding window work, and why is it O(n) when there's a `while` loop inside the `for`?
`id: dsa-007` · `from: day 003` · `confidence: low` · `last: —` · `next: day 004`

<details><summary>Answer</summary>

It works when the condition is **monotone in the window**: if a window is valid, every sub-window is valid
too (e.g. "every count ≤ k", "sum ≤ S with non-negative numbers"). Then when adding `right` breaks the
condition, moving `left` forward is the only way to repair it, and you never need to move `left` back.
O(n): `right` moves n times and `left` moves at most n times *in total* across the whole run (amortized), so
each element enters and leaves the window once. It fails with negative numbers for sum conditions
(shrinking can make the sum bigger). Use prefix sums + a hash map there.
</details>

### Q: Maximum average of a length-k window (LeetCode 643): what's the brute force, and why is the running sum better? Where does the division go?
`id: dsa-008` · `from: day 003 review` · `confidence: low` · `last: 2026-10-20 (pre-code: called the running sum "weak" because of division cost)` · `next: day 005`

<details><summary>Answer</summary>

Brute force: re-sum every window, O(n·k). Running sum: add the element entering, subtract the one leaving,
O(1) per step → O(n) total, O(1) space. Track the max **sum** and divide once at the end (k is fixed, so the
max sum is the max average). Division was never the cost; the k factor was.
</details>
