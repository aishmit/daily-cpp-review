# Progress — the loop's memory

Updated by the daily run (and by Claude Code sessions when you struggle). Newest first in the log.

## Status
- **Plan restarted 2026-10-15:** target is now **Citadel Securities SWE** (recruiter outreach). The
  earlier HRT/PDT C++-depth plan and the C++-only switch are superseded; see `curriculum.md`.
- Screen date: **not yet known**. When it's known, compress the plan so a mock lands 3–4 sessions before it.
- Cadence: Mon–Thu, 60 min (5 recall · 30 DSA · 25 track). No Fri–Sun. Skip US holidays (Thanksgiving Thu Nov 26).
- Interview language: **Python**. C++ for the debugging round and systems knowledge.
- Tracks alternate: even days = system design (Python), odd days = C++ & systems.
- Current session: **003** (Tue 2026-10-20): sliding window (643, 2958) / C++ object lifetime (rule of 0/3/5).
  Written by the 2026-10-20 run. Stubs fail 14/22 (drill 0/6), a private reference (not committed) passes 22/22
  with g++ ASan+UBSan and clang++ -O0/-O1/-O2. Links verified via search index (leetcode.com and cppreference
  can't be fetched directly from the routine). `run.sh` now builds `systems/drill.cpp` too and adds
  `-fno-builtin` on sanitizer builds (clang otherwise optimizes away new[]/delete[] pairs and breaks the
  allocation counter in `counting_new.hpp`).
- Day 002 reviewed 2026-10-20 (`days/002/review.md`): DSA 3/4, design 2/4. Remediation = Day 004 (order book part 2),
  which must start with the review's fix #1 (validate before mutating).
- Routine push check: OK (2026-10-15, new Claude Code routine with repo source).
- Day 001 (Oct 1, vtables) is done. Note from his notes: "this is hard… so far behind"; confidence 1/5.

## Schedule
| Day | Date | DSA pattern | Track |
|---|---|---|---|
| 001 | Thu Oct 1 | — | C++: virtual dispatch & vtables (done) |
| 002 | Mon Oct 19 | Arrays/hashing, "stock" pattern | Design: framework + order book |
| 003 | Tue Oct 20 | Sliding window | C++: object lifetime by hand, rule of 0/3/5 (re-test Day 001 gaps) |
| 004 | Wed Oct 21 | Sliding window (deque) | Design: **finish the order book** (part 2: cancel, modify, depth, queue → 12/12). Matching engine moves to wk 2. |
| 005 | Thu Oct 22 | Mixed wk-1 review | C++: move semantics + behavioral #1 |
| 006–009 | Oct 26–29 | Stacks, monotonic, heaps | curriculum wk 2; matching engine = two design sessions (006 + 008) |
| 010–013 | Nov 2–5 | Intervals, binary search, BFS | wk 3 |
| 014–017 | Nov 9–12 | Graphs | wk 4 · **017 mock screen (Thu Nov 12)** |
| 018–021 | Nov 16–19 | Bellman-Ford, union-find, tries | wk 5 |
| 022–024 | Nov 23–25 | DP | wk 6 (Thanksgiving week, 3 sessions) |
| 025–028 | Nov 30–Dec 3 | DP / design-style | wk 6–7 · **028 mock design (Thu Dec 3)** |
| 029–032 | Dec 7–10 | Design-style, mixed | wk 7–8 · **030 mock superday design (Tue Dec 8)** |
| 033 | Mon Dec 14 | Mixed | **Mock superday** |

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
| C++ syntax fluency: casts, lambda bodies, struct vs class | Day 001 B1: `return Circle* c = reinterpret_cast<Circle>(s); ...` (declaration after return, cast to value not pointer, dropped const, wrong cast) (cpp-om-012); 2026-10-15: changed struct→class and didn't know why it broke (cpp-om-013); 2026-10-15 LeetCode 121: size_t for a value that goes negative (cpp-om-014) | 2026-10-01 | open |
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
| 002 | 2026-10-19 | Arrays/hashing (121, 49) | Order book (design) | yes, partial (live session) | DSA 3 · design 2 | Reviewed 2026-10-20. Hidden bug: rejected order keeps its id. | DSA: 121 (C++, 1 hint, Oct 15), 49 (Python, ~9 min, no hints). Design: ~40 min, paused at 1/12 tests; only add() + best_bid/best_ask started. Repeated misses: asks/bids swapped in 3 places, (price, Order) heap tie (3 rounds), reject = return False not raise. Data-model idea was right (price heap + per-price FIFO + id map). Unfinished: fix best_*, cancel, modify, depth, queue. |
| 001 | 2026-10-01 | Virtual functions & vtables | Order book: requirements & core ops | systems: yes (live session) | — | Live session: wrote Part A, B1 tables, B3 dispatch, clone, copy ctor himself (many hints). Tutor wrote move ctor (asked twice), copy-and-swap operator=, destroy slots + ~Shape (asked twice). Re-test him on destroy/~Shape/operator= by hand on Day 003 (plan restarted; Day 002 is a design day). |
