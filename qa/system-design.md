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
`id: sd-005` · `from: day 002` · `confidence: low` · `last: 2026-10-19 (thought the book was sorted on price only; didn't know what "back of a level" meant); asked in Day 004 warm-up` · `next: day 004`

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

### Q: A heap of prices backs `best_bid()`. Cancel empties the best level. How do you keep `best_bid()` right without deleting from the middle of the heap, and what does it cost?
`id: sd-007` · `from: day 004` · `confidence: low` · `last: —` · `next: day 005`

<details><summary>Answer</summary>

Lazy deletion: leave the stale price in the heap; in `best_bid()`, pop while the top price has no live level
(`while heap and -heap[0] not in levels: heappop(heap)`), then read the top. Each price is pushed once per time
its level is created and popped at most once, so it's amortized O(log L). Trap: stale or duplicate prices stay in
the heap, so never read depth from the heap; read levels from the dict.
</details>

### Q: Give the complexity of add, cancel, modify, best and depth in a book built from a heap of prices + a dict of price → FIFO dict + an id map. Which op matters most?
`id: sd-008` · `from: day 004` · `confidence: low` · `last: —` · `next: day 005`

<details><summary>Answer</summary>

add: O(1) average, plus O(log L) if it creates a new level · cancel: O(1) average (two dict deletes; the heap is
untouched) · modify down: O(1); up: O(1) (pop + re-insert the key at the back) · best: amortized O(log L) ·
depth(m): O(L log L) if you sort the level keys, + O(m·k) to sum quantities (keep a per-level total to make it O(m)).
Cancel dominates real feeds (most orders never trade), and it's O(1) here.
</details>

### Q: Using a Python dict as the FIFO for one price level: how do you send an order to the back, and why is that the right behavior for a quantity increase?
`id: sd-009` · `from: day 004` · `confidence: low` · `last: —` · `next: day 005`

<details><summary>Answer</summary>

Dicts keep insertion order, so `order = level.pop(oid); level[oid] = order` moves it to the back in O(1).
A quantity increase loses time priority (otherwise you could park a tiny order at the front and size it up
later); a decrease keeps its place, so it's just `order.qty = new_qty`.
</details>
