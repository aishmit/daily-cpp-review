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
