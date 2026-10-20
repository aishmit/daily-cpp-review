# Curriculum — Citadel Securities SWE prep · 8 weeks · Mon–Thu · 60 min/session

**Target:** pass Citadel Securities technical screens and superday (experienced SWE, ~6 YOE).
Built from public 2025–2026 interview reports (see `research/citadel-securities.md`).
**Problems come from `research/question-bank.md`** (A = runnable design+code, B = C++/systems,
C = talk-through design, D = LeetCode list). Runnable design problems get **two** design sessions.
**Coding language for interviews: Python.** C++ is studied for the debugging round and
systems questions, not for writing interview solutions.

## Every session (60 min)

| Block | Min | What |
|---|---|---|
| Warm-up recall | 5 | 3 questions from `qa/` (spaced repetition) |
| **DSA** | 30 | 1–2 LeetCode problems (Python, timed), picked from this week's pattern. Log them in `notes.md`. |
| **Track block** | 25 | **Even sessions → System design** (`design/`, Python). **Odd sessions → C++ & systems** (`systems/`, C++). Normally that's Mon/Wed vs Tue/Thu. |

Split ≈ DSA 50% · Design 25% · C++/systems 25%. Every 4th session adds a 5-min behavioral story (in `notes.md`).
When the screen date is known, the daily run compresses this plan so a mock lands 3–4 days before it.

## Week by week

Day 001 (Oct 1, done): virtual dispatch & vtables, from the earlier HRT-focused plan. The new plan starts at Day 002 on Mon Oct 19.

| Wk | Sessions | DSA pattern (LeetCode) | Design (even) | C++ & systems (odd) |
|---|---|---|---|---|
| 1 | 002–005 | Arrays/hashing, sliding window, "stock" patterns | 002 Interview framework + order book (price-time, cancel) · 004 Order book part 2 (finish to 12/12). Matching engine with heaps moved to wk 2 (two sessions) | 003 Object lifetime by hand: ctors/dtors, RAII, rule of 0/3/5 (re-test Day 001's destroy / `~Shape` / `operator=`) · 005 Move semantics, value categories |
| 2 | 006–009 | Stacks, monotonic stack/deque, heaps (top-K, k-way merge, median of stream) | 006 + 008 **Matching engine** (A2), part 1 / part 2 | 007 `unique_ptr` vs `shared_ptr` internals (control block, atomic refcount) · 009 STL internals: `vector` growth, iterator invalidation, `unordered_map` |
| 3 | 010–013 | Intervals, binary search, BFS/shortest path (Word Ladder family) | 010 Conflating quote queue (A5) · 012 Streaming stats: VWAP + rolling window max/mean (A6) | 011 **C++ debugging drill #1** (dangling refs, UB, overflow, missing virtual dtor) · 013 Threads vs processes, context switches, IPC |
| 4 | 014–017 | Graphs: weighted BFS/DFS (currency conversion), topo sort, Dijkstra | 014 Talk-through: market-data ingestion + feed handler, gaps & recovery (C1) · 016 Remediation (weakest design topic so far) | 015 Mutex + condvar → bounded producer-consumer queue · **017 MOCK SCREEN** (45-min CoderPad DSA + resume deep-dive) |
| 5 | 018–021 | Bellman-Ford (arbitrage cycle), union-find, tries (autocomplete, trie+heap) | 018 Trade reconciliation library (A10) · 020 Talk-through: real-time risk aggregation + order gateway rate limiting (C3, C6) | 019 Atomics & memory ordering, spinlock · 021 Lock-free SPSC ring buffer |
| 6 | 022–025 | Dynamic programming: stock buy/sell family, 1-D/2-D DP | 022 K-way merge of tick files (A9) · 024 Talk-through: messaging + log aggregation across colos (C5) | 023 Caches, cache lines, false sharing, branch prediction · 025 Virtual memory: cache miss vs page fault |
| 7 | 026–029 | Design-style problems: LRU/LFU, time-based KV, hit counter, order book | 026 Talk-through: order book service at ~1M updates/s, failover (C2) · 028 **MOCK DESIGN** (rebuild A1 or A2 end to end in 45 min) | 027 Networking: TCP vs UDP, multicast packet loss, latency spikes · 029 **C++ debugging drill #2** (data races with TSan) |
| 8 | 030–033 | Mixed timed sets (2 problems / 45 min) | 030 **MOCK SUPERDAY** design round · 032 Remediation (weakest design topic) | 031 Templates essentials, `std::variant`/`std::any` internals, rapid-fire trivia · **033 MOCK SUPERDAY** (coding + systems + behavioral) |

## Behavioral bank (sessions 005, 009, 013…, one story each — STAR, ≤ 2 min spoken)
1. Most complex system you built in the past year: architecture and trade-offs
2. A production mistake you made and how you resolved it
3. Isolating the root cause of an ambiguous bug in a critical system
4. A technical compromise made to meet a deadline
5. Handling ambiguous requirements
6. Why market making / Citadel Securities rather than big tech, or staying at Bloomberg
7. Disagreeing with a senior engineer or PM
8. Your questions for them (team, on-call, bonus structure, how success is measured)
