# Question bank: what Citadel Securities has asked → what we practice

Researched 2026-10-19 from public reports. **The daily run picks problems from here** (see `prompts/daily-run.md`).
Each practice prompt is *ours*: a close stand-in that tests the same skills as the reported question, not a copy.

**Source key:** **[1st]** = a candidate's own write-up (Glassdoor, LeetCode Discuss, Medium) ·
**[agg]** = a prep site compiling reports (PracHub, OA VO Service, InterviewFox, QuantT, techinterview.org) ·
**[off]** = Citadel Securities' own careers page · **[tag]** = LeetCode problems tagged "Citadel".
Caution: many sites mix **Citadel** (hedge fund) and **Citadel Securities** (market maker). Items marked
*(CitSec)* were reported for Citadel Securities specifically.

## What the reports say gets tested (the skills every problem below drills)
1. **Working, runnable code under time** [off][agg]. One problem per onsite round: requirements and design →
   implement → code review → extend under new constraints. The OA uses hidden tests with little partial credit.
2. **Edge cases and the input contract** [1st][agg]: self-loops, empty input, n=1, duplicates, all-equal arrays.
3. **The right complexity**: O(n²) gets cut by hidden tests when O(n log n) or O(n) exists [agg].
4. **The right traversal**: BFS vs DFS for shortest paths, and weighted vs unweighted (plain BFS on weighted edges fails) [1st][agg].
5. **Trading-shaped simulation**: order books, market data streams, event logs, with bid/ask vocabulary [agg] *(CitSec-heavy)*.
6. **Code someone else could read and extend**, and design choices that survive real input [off].
7. **C++ for systems**: debugging, concurrency, memory, performance [1st][agg].

---

## A. Runnable implementation problems (design + code; 2 sessions each, then once timed in a mock)

| # | Our practice prompt | Mirrors (reported) | Skills |
|---|---|---|---|
| A1 | **Passive order book**: add / cancel / modify / best / depth / queue, price-time priority (Day 002/004) | In-memory order book, price-time, level aggregation, cancel *(CitSec)* [agg] | Data model, two-level priority, O(1) cancel, spec reading |
| A2 | **Matching engine**: read `side id price qty` lines; match at the resting price with partial fills; print `TRADE buy_id sell_id price qty`; up to 2·10⁵ orders, O(N log N) | CoderPad matching engine (ran on samples) [agg]; OA "Citadel NXT" order matching [agg] | Heaps + FIFO, partial fills, output format, complexity |
| A3 | **Order-book event replay**: a log of `ADD/CANCEL/MODIFY/TRADE` lines (some malformed or out of order) → final book + best bid/ask after each event | OA implementation/simulation: order-book event replay *(CitSec, 6 of 9 reports)* [agg] | Parsing, validation, state machine, edge cases |
| A4 | **Top-ten trades query**: parse a trade CSV (symbol, side, price, qty); return the top 10 buys and sells by notional, with **exact** amounts (no floats) | "Design a top-ten trade query with exact amounts" (screen) *(CitSec)* [agg] | Parsing, `Decimal`/integer ticks, heap top-K, a clean library API |
| A5 | **Conflating quote queue**: producers push `(symbol, price)`; the consumer pops symbols in arrival order but always gets the **latest** price; a symbol is never queued twice | Conflating quote queue *(CitSec)* [agg] | Dict + ordered queue, O(1) ops, then a thread-safe version (C++ track) |
| A6 | **Streaming stats**: on each trade `(ts, price, qty)`, report VWAP and the max/mean price over the last T seconds | Market-data stats: VWAP, time-weighted price, rolling vol *(CitSec)* [agg]; sliding-window mean [agg]; max price in last N seconds [agg] | Monotonic deque, running sums, time-based eviction |
| A7 | **Rolling median of trades**: median trade price over the last K trades, updated per trade | Rolling median of trades [agg]; median price across feeds [agg] | Two heaps + lazy deletion |
| A8 | **Currency conversion**: given rates `A/B = r`, return the best rate from X to Y, then find a profitable cycle if one exists | Best exchange rate A→B; candidate missed **self-loops** [1st]; arbitrage cycle *(CitSec)* [agg] | Graph modelling, BFS/DFS on products, Bellman-Ford on −log(rate), edge cases |
| A9 | **K-way merge of tick files**: N files of timestamped ticks, each sorted; output one merged stream without loading everything | K-way merge of files from disk with a min-heap (experienced, Apr 2026) [agg] | Heap of iterators, streaming I/O, ties |
| A10 | **Trade reconciliation**: our fills vs the exchange's fills → matched / missing / mismatched (qty or price), with a clear module boundary for parsing vs matching | "Define a reliable trade-reconciliation library contract" (screen) *(CitSec)* [agg] | API design, keys, parsing boundary, testability |
| A11 | **LRU cache** + write 3 tests that would catch an off-by-one in eviction; stretch: LFU | LRU with eviction tests [agg]; LRU / LFU [tag] | Hash map + doubly linked list, writing your own tests |
| A12 | **Request throttle**: allow at most R requests per W seconds per client; count/allow incoming requests | OA "Request Throttling" (sliding window) [agg]; rate limiter [agg] | Sliding window over timestamps, deque |
| A13 | **Symbol autocomplete**: prefix → top-k symbols by traded volume, volumes updating live | Trie + heap hybrid (intern, Mar 2026) [agg]; Search Suggestions / Autocomplete [tag] | Trie, per-node top-k, update cost |
| A14 | **Job pipeline**: tasks with durations and dependencies → earliest finish time; detect cycles | Harder "parallel courses" variant (Nov 2025) [agg]; Parallel Courses III [tag] | Topological sort, DP on a DAG |
| A15 | **Queue on a fixed array** (circular), then **validate a worker's push/pop sequence** | Queue using a vector; "reconstruct a stack processed by a worker" *(CitSec, 2026)* [1st] | Index arithmetic, stack simulation |

## B. C++ & systems track (Python interviews, but these come up in the debugging/systems rounds)

| # | Practice | Mirrors |
|---|---|---|
| B1 | **Find-the-bug drills**: dangling reference, iterator invalidation, missing virtual destructor, signed/unsigned, slicing, use-after-move, data race | "Heavy C++ debugging" round *(CitSec, 2026)* [1st] |
| B2 | **Thread-safe producer-consumer queue**: mutex + condvar → spinlock → lock-free SPSC ring buffer | Producer-consumer: mutex, then spinlock, then lock-free *(CitSec)* [agg]; thread-safe circular buffer [agg] |
| B3 | **Make this function fast**: remove allocations, swap `std::map` for a flat array, take branches off the hot path; measure | "Optimize a slow function for low-latency execution" [agg]; hash map vs flat array of structs [agg] |
| B4 | **Explain it** (2-min answers): vtables · `shared_ptr` · atomics · `std::variant`/`std::any` · `vector` / `unordered_map` internals · iterators · cache miss vs page fault · cost of an `if` (branch prediction) · thread vs process · TCP vs UDP · multicast loss | Agg. topic lists *(CitSec)*; "cost of an if" [1st] |

## C. Talk-through design (25 min, framework + diagram + trade-offs, no code)

| # | Prompt | Mirrors |
|---|---|---|
| C1 | Market-data ingestion from ~50 exchanges: normalize, fan out to strategies, gap/packet-loss recovery | Market-data ingestion design [agg]; feed → strategy in microseconds *(CitSec)* [agg] |
| C2 | Order book service at ~1M updates/s | Order book at scale *(CitSec)* [agg] |
| C3 | Real-time risk aggregation: per-symbol exposure across thousands of strategies | Risk aggregation design [agg] |
| C4 | Smart order router: which venue gets each order (liquidity, latency, fees) | Order routing design [agg] |
| C5 | High-throughput messaging between trading components; log aggregation across colos | Messaging / log aggregation *(CitSec)* [agg] |
| C6 | Rate limiter: then drill into failure modes | Rate limiter design [agg] |
| C7 | Globally distributed market data with historical queries and recovery | Experienced-engineer design prompt [agg] |

## D. LeetCode practice list (Python, timed), grouped by the curriculum's weekly patterns
Tagged "Citadel" on LeetCode (most frequent first where known) **[tag]**, plus close matches to reported questions.
Premium-only problems are marked †.

| Pattern (curriculum week) | Problems |
|---|---|
| Arrays/hashing, stock (wk 1) | 121, 49 ✔, 122, 123, 380 Insert Delete GetRandom, 2771 Longest Non-decreasing Subarray From Two Arrays |
| Sliding window (wk 1) | 239 Sliding Window Maximum, 1438 Longest Subarray with max − min ≤ limit (matches a reported OA shape), 2958 At Most K Frequency |
| Stacks / heaps (wk 2) | 150 Evaluate RPN, 946 Validate Stack Sequences (→ A15), 295 Find Median from Data Stream, 23 Merge k Sorted Lists, 1606 Servers That Handled Most Requests, 622 Design Circular Queue |
| Intervals / binary search / BFS (wk 3) | 56 Merge Intervals, 759 Employee Free Time†, 1229 Meeting Scheduler†, 1197 Minimum Knight Moves†, 200 Number of Islands, 126/127 Word Ladder (BFS, not DFS) |
| Graphs (wk 4) | 399 Evaluate Division (= currency conversion), 787 Cheapest Flights Within K Stops (weighted, not plain BFS), 2050 Parallel Courses III, 1203 Sort Items by Groups, 310 Minimum Height Trees |
| Tries / union-find (wk 5) | 208 Implement Trie, 1268 Search Suggestions System, 642 Design Search Autocomplete† |
| DP (wk 6) | 740 Delete and Earn, 718 Max Length of Repeated Subarray, 1048 Longest String Chain, 279 Perfect Squares, 221 Maximal Square, 2466 Count Ways to Build Good Strings |
| Design-style (wk 7) | 146 LRU Cache, 460 LFU Cache, 297 Serialize/Deserialize Tree, 42 Trapping Rain Water |

## Sources
- https://www.citadelsecurities.com/careers/career-perspectives/our-engineering-interview-process/ [off]
- https://www.glassdoor.com/Interview/Citadel-Securities-Software-Engineer-Interview-Questions-EI_IE1443495.0,18_KO19,36.htm [1st]
- https://leetcode.com/discuss/interview-experience/5565531/Citadel-or-Senior-Software-Engineer-or-Reject/ [1st]
- https://prachub.com/interview-guide/citadel-securities-software-engineer-interview-questions-guide-2026 [agg]
- https://interviewfox.ai/interview-questions/citadel-coderpad-oa-guide/ [agg]
- https://www.linkjob.ai/interview-questions/citadel-hackerrank-questions/ [agg]
- https://oavoservice.com/en/articles/citadel-oa-question-types-experiences-2026 [agg]
- https://www.quantt.co.uk/resources/citadel-interview [agg]
- https://www.techinterview.org/companies/citadel-securities/ [agg]
- https://www.techinterview.org/post/3233475483/citadel-vs-citadel-securities-interview/ [agg]
- https://codejeet.com/company/citadel [tag]
