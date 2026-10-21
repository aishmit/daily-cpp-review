# Progress — the loop's memory

Updated by the daily run (and by Claude Code sessions when you struggle). Newest first in the log.

## Status
- **Target:** Citadel Securities SWE (recruiter outreach). **He schedules the interview when ready** — the plan is paced
  by checkpoints, not a deadline (see `curriculum.md`). He may ask for *speed-up mode* if a date gets set.
- **Cadence (from 2026-10-21):** Mon–Fri, 60 min, one heavy block per session: Mon DSA learn · Tue C++ · Wed design ·
  Thu DSA practice (timed) · Fri quiz (every 4th = mock screen). He works full-time; never stack two heavy blocks.
- Interview language: **Python**. C++ for the debugging round and systems knowledge.
- **Current session: 003 (C++ block, Wed Oct 21)**, then 004 order book part 2 (Thu Oct 22), 005 baseline quiz (Fri Oct 23).
  The new weekly rhythm starts Mon Oct 26 (Day 006).
- Oct 21 run: no new commits since Oct 20; Day 003 C++ stubs verified (compile, drill 0/6, tests fail). 3 Wed warm-up
  questions added to `days/003/lesson.md` §2 (cpp-om-014, cpp-om-013, dsa-004). Review of 003 follows once he pushes the C++ block.
- Day 002 reviewed (`days/002/review.md`): DSA 3/4, design 2/4. Day 004 must start with the review's fix #1 (validate before mutating).
- Routine: "Citadel Securities Prep Daily" (Claude Code routine with the repo as source), 5:54 PM ET, Mon–Fri.

## Checkpoints (updated by the daily run after each quiz/mock)
**① Screen-ready:** not met.
- Graded quizzes (Medium ≤ 25 min, unaided, contract + complexity stated): — (none yet; baseline Fri Oct 23 doesn't count)
- Mock screen passed (≥ 3/4): —
- Core patterns learned + practiced: hashing ✔ (49, 121) · sliding window ✔ learned (643, 2958), practice pending ·
  stack · heap · intervals/binary search · BFS · graphs · DP 1-D

**② Superday-ready:** not met.
- A1 order book: part 1 done (1/12), part 2 Thu Oct 22 · A2 matching engine: — · rebuilt in 45-min mock: —
- §C talk-throughs ≥ 3/4: 0/3 · C++ debugging drills ≥ 3/4: 0/2 · behavioral stories rehearsed: 0/4

## Quiz & mock log
| Day | Date | Type | Problem | Time | Unaided? | Contract + complexity before coding? | Score | Notes |
|---|---|---|---|---|---|---|---|---|

## Schedule
Redesigned 2026-10-21 (Mon–Fri weekly rhythm, see `curriculum.md`). The run extends it a week at a time.
Thanksgiving Thu–Fri Nov 26–27 off (that week's Thu practice folds into Dec 3's interleaving). Dec 24–25 off.

| Day | Date | Type | Topic |
|---|---|---|---|
| 001 | Thu Oct 1 | C++ | Virtual dispatch & vtables (done) |
| 002 | Mon Oct 19 | DSA + Design | 121, 49 · order book part 1 (done, reviewed) |
| 003 | Tue Oct 20 | DSA | Sliding window: 643, 2958 (done) |
| 003 | Wed Oct 21 | C++ | **Day 003 §2 (already written):** object lifetime, rule of 0/3/5. No DSA. Don't write a new day; send a short reminder. |
| 004 | Thu Oct 22 | Design | **Order book part 2** (cancel, modify, depth, queue → 12/12). Fix the review's bug #1 first (validate before mutating). |
| 005 | Fri Oct 23 | Quiz | **Baseline quiz** (optional, ungraded for checkpoints): 1 timed Medium (25 min, mixed: hashing/sliding window) + 10 rapid recall. |
| 006 | Mon Oct 26 | DSA learn | Stack & monotonic stack/deque — worked example, 1–2 problems untimed |
| 007 | Tue Oct 27 | C++ | Move semantics & value categories (re-test Day 003) |
| 008 | Wed Oct 28 | Design | **A2 matching engine — part 1** |
| 009 | Thu Oct 29 | DSA practice | Stack & monotonic stack/deque — timed 25 min + 1 interleaved older pattern |
| 010 | Fri Oct 30 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall |
| 011 | Mon Nov 2 | DSA learn | Heaps: top-K, k-way merge, running median — worked example, 1–2 problems untimed |
| 012 | Tue Nov 3 | C++ | `unique_ptr` / `shared_ptr` internals (control block, refcount) |
| 013 | Wed Nov 4 | Design | **A2 matching engine — part 2** (5-min recap first) |
| 014 | Thu Nov 5 | DSA practice | Heaps: top-K, k-way merge, running median — timed 25 min + 1 interleaved older pattern |
| 015 | Fri Nov 6 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall + 1 behavioral story (2 min) |
| 016 | Mon Nov 9 | DSA learn | Intervals + binary search — worked example, 1–2 problems untimed |
| 017 | Tue Nov 10 | C++ | STL internals: `vector` growth, iterator invalidation, `unordered_map` |
| 018 | Wed Nov 11 | Design | Talk-through **C1**: market-data ingestion, gaps & recovery |
| 019 | Thu Nov 12 | DSA practice | Intervals + binary search — timed 25 min + 1 interleaved older pattern |
| 020 | Fri Nov 13 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall |
| 021 | Mon Nov 16 | DSA learn | BFS: grids, Word Ladder (BFS not DFS), knight moves — worked example, 1–2 problems untimed |
| 022 | Tue Nov 17 | C++ | **C++ debugging drill #1** (dangling refs, UB, missing virtual dtor, signed/unsigned) |
| 023 | Wed Nov 18 | Design | **A5** conflating quote queue (one session) |
| 024 | Thu Nov 19 | DSA practice | BFS: grids, Word Ladder (BFS not DFS), knight moves — timed 25 min + 1 interleaved older pattern |
| 025 | Fri Nov 20 | **Mock screen** | 45-min CoderPad-style screen (timed, no hints) + debrief. Counts toward the screen checkpoint. |
| 026 | Mon Nov 23 | DSA learn | Graphs: topological sort, union-find — worked example, 1–2 problems untimed |
| 027 | Tue Nov 24 | C++ | Threads, mutex + condvar → producer-consumer queue (B2 part 1) |
| 028 | Wed Nov 25 | Design | **A6** streaming stats (VWAP, rolling max) — part 1 |
| 029 | Mon Nov 30 | DSA learn | Weighted graphs: Dijkstra, Bellman-Ford, currency conversion (399, 787) — worked example, 1–2 problems untimed |
| 030 | Tue Dec 1 | C++ | Atomics & memory ordering, spinlock (B2 part 2) |
| 031 | Wed Dec 2 | Design | **A6** streaming stats — part 2 |
| 032 | Thu Dec 3 | DSA practice | Weighted graphs: Dijkstra, Bellman-Ford, currency conversion (399, 787) — timed 25 min + 1 interleaved older pattern |
| 033 | Fri Dec 4 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall |
| 034 | Mon Dec 7 | DSA learn | DP 1-D (stock family, house robber, delete-and-earn) — worked example, 1–2 problems untimed |
| 035 | Tue Dec 8 | C++ | Lock-free SPSC ring buffer (B2 part 3, TSan) |
| 036 | Wed Dec 9 | Design | Talk-through **C2**: order book service at ~1M updates/s |
| 037 | Thu Dec 10 | DSA practice | DP 1-D (stock family, house robber, delete-and-earn) — timed 25 min + 1 interleaved older pattern |
| 038 | Fri Dec 11 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall + 1 behavioral story (2 min) |
| 039 | Mon Dec 14 | DSA learn | DP 2-D + tries (1268 search suggestions) — worked example, 1–2 problems untimed |
| 040 | Tue Dec 15 | C++ | Caches, false sharing, branch prediction + "make this function fast" (B3) |
| 041 | Wed Dec 16 | Design | **A10** trade reconciliation — part 1 |
| 042 | Thu Dec 17 | DSA practice | DP 2-D + tries (1268 search suggestions) — timed 25 min + 1 interleaved older pattern |
| 043 | Fri Dec 18 | Quiz | Timed: 1 mixed-pattern Medium (25 min) + 10 rapid recall |

## Calibration notes for the daily run (read before writing the next day)
- **2026-10-01, Day 001 live session:** level is below what Day 001 assumed. Concepts (vtable/vptr,
  ctor sets vptr, destructor chaining) needed explaining from scratch; hand-writing C++ syntax is
  the bigger gap: lambda bodies, `return` placement, casts (`static_cast<const T*>`), calling a
  function pointer through a struct (`vptr_->area(obj_)`). Part B took ~8 attempts for 3 one-liners.
- **Adjust:** smaller steps per challenge (one TODO = one concept), a tiny worked example of every
  syntax form the challenge needs (cast, function-pointer call, lambda→fn ptr), and tests that fail
  one concept at a time (don't fold leak checks into a "dispatch" test). Keep the next C++ day (now Day 003) on lifetime/
  move but add a 5-min "C++ syntax by hand" drill before the challenge until this row closes.
- **Tutor pace:** he asked to be "pushed through": escalate hints faster (pseudocode by the 2nd miss,
  the missing line by the 3rd) instead of long Socratic loops. Still no full solutions unless asked twice.
- **2026-10-19, coding bar (researched):** Citadel Securities grades code that *runs and is correct on real input*, not near-complete code. The onsite is one problem: design → implement → review → extend (official page); the OA has hidden tests with little partial credit. So design days that are reported coding questions (order book, matching engine) end in runnable code with tests; other design days are talk-through (framework + diagram + trade-offs). Day 002 showed the gap: right data model, 40 min, 1/12 tests.

- **2026-10-19, time boxes (his call, agreed):** a runnable design problem (order book, matching engine, LRU-style) is a 45–60 min job, the length of one Citadel Securities onsite round. Never fit one into a single 25-min slot. Split it across two design sessions (part 1 / part 2, each ending at a test-count milestone), and say in the lesson which tests part 1 should turn green. Talk-through design days stay at 25 min. Once a problem has been built in parts, a later mock redoes it end to end in 45 min.
- **2026-10-20, session length (his words: "these exercises are too long. i work a full time job"):** the 60-min DSA + track session ran ~90 min in practice (DSA 643 + 2958 alone took ~40 min). Keep each session to what fits ~60 min of *his* real pace: when the track block is a multi-step C++ challenge or a runnable design part, give it its own session (no DSA that day), or cut DSA to one problem. Never stack two heavy blocks.
## Calibration notes added 2026-10-15
- Interview reports flag missed edge cases, BFS vs DFS for shortest paths, and input contracts:
  drill these in every DSA review.
- Prior Python interview practice: rate limiter, LRU cache, webhook delivery with retries.

## DSA log (LeetCode); the run fills this from notes.md
| Day | Problem | Pattern | Time | Solved without hints? | Notes |
|---|---|---|---|---|---|
| 002 (early, Oct 15) | 121. Best Time to Buy and Sell Stock | one pass, running min | — | hint level 1 (/hint) | solved (C++; chose to keep C++ for now rather than redo in Python); size_t profit → -6 wrapped to 1.8e19 (cpp-om-014) |
| 002 | 49. Group Anagrams | hash map, canonical key | ~9 min | yes, no hints (Python); passes 6 cases incl. [], [""], dupes | Pre-code: picked the sorted-key approach (good) but called it brute force; complexity n²logn (wrong: n·k log k) (dsa-004); contract missed empty list + duplicates |
| 003 | 643. Maximum Average Subarray I | fixed sliding window, running sum | ~20 min (timer 10) | yes, no hints; correct (edge cases + 500 random vs brute) | Pre-code: brute force right (recompute each window, O(n·k)); dismissed the running sum as "weak" because of division cost (wrong: it removes the k factor, and you divide once at the end) |
| 003 | 2958. Longest Subarray With at Most K Frequency | variable sliding window + count map | ~20 min (timer 20) | yes, no hints; correct (examples + 1000 random vs brute; n=1e5 in 0.03s) | Approach + amortized O(n) stated before coding; wording needed tightening (max of r−l+1) |

## Weak areas (drives remediation + recall)
| Topic | Evidence | First seen | Status |
|---|---|---|---|
| Virtual functions / vtables | self-reported; Day 001 predict.cpp 0/4: thought `virtual` adds no size, missed ctor/dtor dispatch and didn't know the vptr is written by the ctor — guessed "when called" (cpp-om-003), thought an overridden virtual dtor skips ~Base (cpp-om-011), unsure how dispatch finds the derived fn — said "the vtable of the Sink" is looked up (cpp-om-001), slicing (cpp-om-004), MI pointer adjust (cpp-om-006) ; 2026-10-15 recall (2 wks later): 1 partial, 2 wrong — ctor dispatch and the void* cast didn't stick; thinks `override` is what makes a function override | 2026-10-01 | open |
| Object layout: sizeof, padding, alignment | Day 001 Q1: thought member functions occupy object storage (cpp-om-009); no padding model (cpp-om-010) | 2026-10-01 | open |
| C++ syntax fluency: casts, lambda bodies, struct vs class | Day 001 B1: `return Circle* c = reinterpret_cast<Circle>(s); ...` (declaration after return, cast to value not pointer, dropped const, wrong cast) (cpp-om-012); 2026-10-15: changed struct→class and didn't know why it broke (cpp-om-013); 2026-10-15 LeetCode 121: size_t for a value that goes negative (cpp-om-014); 2026-10-21: wrote `data_(x);` inside a ctor body (init-list syntax in the body → "called object type int* is not a function"); std::copy args reversed (wrote into the const source) | 2026-10-01 | open |
| Type erasure: wrapper vs erased object | Day 001 B3: wrote `obj_->area()`, then `vptr_->area(this)` (passed the Shape, not the object); unsure what a deep copy needs (cpp-om-008) | 2026-10-01 | open |
| Move semantics: what a move does | Day 001 B2: proposed clone+delete as a move; didn't null the source (cpp-ml-001); Day 001 notes: thought a throwing move is UB in vector (it copies instead: cpp-ml-002) | 2026-10-01 | open |
| Complexity analysis with two sizes | Day 002 (49): said "n log n * n = n² log n" for sort-each-word; mixed word count n with word length k (dsa-004); proposed a dict as a dict key — unhashable (dsa-005) | 2026-10-19 | open |
| Order book: price levels & time priority | Day 002: thought orders are sorted on price only (one heap per side); didn't know what a price level/"back of the level" is; read the diagram as best ask = highest (sd-005) | 2026-10-19 | open |
| Reading the spec / API contract | Day 002 order book add(): raised exceptions where spec says return False; `< 0` where spec says `<= 0`; never returned True; dupe check only within one price level; looked up the string "order_id" instead of the variable; B branch copy-pasted into asks; 2026-10-20 review: stores the order in the id map *before* the crossing/side checks, so a rejected id can't be reused (sd-006) | 2026-10-19 | open |
| Advanced templates | self-reported | 2026-10-01 | open |

## Day log
| Day | Date | Systems / C++ topic | Design topic | Attempted? | Score | Notes |
|---|---|---|---|---|---|---|
| 003 | 2026-10-20 | Sliding window (643, 2958) · C++ object lifetime, rule of 0/3/5 (Buffer + Level) | — | pending | — | Re-tests Day 001's dtor / operator= / move ctor by hand. 5-min syntax drill (new[]/delete[], std::copy, std::swap, init list, static_cast). |
| 003 | 2026-10-21 | C++ block: object lifetime, rule of 0/3/5 | — | yes (live session) | — | ~70 min (18:00–19:10 ET) vs 45 planned. All green: drill 6/6, TODOs 1–5 (3/3, 3/3, 4/4, 4/4, 2/2) under ASan+UBSan, all written by him (Day 001's destroy/~Shape/operator= gap closed). Slow spots: D1 missing `{}`, D3 end pointer src+2, std::copy args reversed, init-list syntax inside the ctor body, unfinished line breaking every test build. Test 5 needed concept hints (missing member + user-declared copy suppresses move). Warm-up (Wed) skipped. |
| 002 | 2026-10-19 | Arrays/hashing (121, 49) | Order book (design) | yes, partial (live session) | DSA 3 · design 2 | Reviewed 2026-10-20. Hidden bug: rejected order keeps its id. | DSA: 121 (C++, 1 hint, Oct 15), 49 (Python, ~9 min, no hints). Design: ~40 min, paused at 1/12 tests; only add() + best_bid/best_ask started. Repeated misses: asks/bids swapped in 3 places, (price, Order) heap tie (3 rounds), reject = return False not raise. Data-model idea was right (price heap + per-price FIFO + id map). Unfinished: fix best_*, cancel, modify, depth, queue. |
| 001 | 2026-10-01 | Virtual functions & vtables | Order book: requirements & core ops | systems: yes (live session) | — | Live session: wrote Part A, B1 tables, B3 dispatch, clone, copy ctor himself (many hints). Tutor wrote move ctor (asked twice), copy-and-swap operator=, destroy slots + ~Shape (asked twice). Re-test him on destroy/~Shape/operator= by hand on Day 003 (plan restarted; Day 002 is a design day). |
