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

### Q: What is a "price level" in an order book, and what does "moves to the back of its price level" mean?
`id: sd-005` · `from: day 002` · `confidence: low` · `last: 2026-10-19 (thought the book was sorted on price only; didn't know what "back of a level" meant)` · `next: day 003`

<details><summary>Answer</summary>

A price level is every resting order on one side at one price, kept in a FIFO queue (arrival order).
Priority is two-level: first by price (best level first: lowest ask, highest bid), then by time within
the level. "Back of the level" = the end of that queue. Example: bids at 99 = [#1 (10), #5 (1)];
modify #1 up to 20 → [#5, #1 (20)]. Data model: per side, price → FIFO of orders, plus a way to find the
best price; and a map order_id → (side, price, qty) for cancel/modify.
</details>

### Q: Your `add(order)` stores the order in the id map, then checks whether it crosses and rejects it. What breaks?
`id: sd-006` · `from: day 002 review` · `confidence: low` · `last: 2026-10-20 (review: orderbook.py line 51 runs before the checks at 54/65/74)` · `next: day 004`

<details><summary>Answer</summary>

The rejected order still occupies its id, so a later valid `add` with that id is rejected as a duplicate (and
`cancel(id)` would "find" an order that isn't resting). Rule: **validate everything, then mutate**. No state
change until every check has passed. Hidden-test graders (the Citadel OA) probe exactly this: reject, then reuse.
</details>
