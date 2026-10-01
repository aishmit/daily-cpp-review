# System design — Q&A

### Q: What's your framework for a system design interview? Say it in 6 steps.
`id: sd-001` · `from: day 001` · `confidence: low` · `last: —` · `next: day 002`

<details><summary>Answer</summary>

Requirements (functional + non-functional; ask about scale) → API (ops, events in/out) → data model
(+ complexity per op) → hot path (walk one message end to end) → scale & failure (sharding,
replication, recovery) → trade-offs (what you chose and what you gave up).
</details>

### Q: Why are prices stored as integer ticks in an order book, not floats?
`id: sd-002` · `from: day 001` · `confidence: low` · `last: —` · `next: day 002`

<details><summary>Answer</summary>

Exact equality is needed to find a price level, and floating-point rounding breaks it
(0.1 + 0.2 ≠ 0.3). Instruments have a tick size, so price = integer × tick. Integer math is also
faster and deterministic across machines, which matters for replay.
</details>

### Q: In a limit order book, which operation dominates the message stream, and what does that imply for the design?
`id: sd-003` · `from: day 001` · `confidence: low` · `last: —` · `next: day 002`

<details><summary>Answer</summary>

Adds and cancels; most orders never trade. So cancel must be O(1): a hash map from order id to the
order's location (e.g. a node in an intrusive doubly linked list per level), plus O(1) removal of
empty levels. Executions are rarer but latency-critical.
</details>

### Q: Why does increasing an order's quantity lose time priority, while decreasing keeps it?
`id: sd-004` · `from: day 001` · `confidence: low` · `last: —` · `next: day 003`

<details><summary>Answer</summary>

Fairness. Otherwise a trader could hold a tiny order at the front of a level and size it up later,
jumping everyone who committed size earlier. Decreasing only gives up claim, so it keeps its place.
In an implementation, an increase = remove + append to the tail of the level.
</details>
